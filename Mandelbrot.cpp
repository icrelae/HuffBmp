#include <thread>
#include <cmath>
#include "Mandelbrot.h"

Mandelbrot::Mandelbrot():
	centerX(-0.5), centerY(0), zoomFactor(2), radius(4), iteration(50)
{
}

size_t Mandelbrot::GetIteration()
{
	return iteration;
}

double Mandelbrot::GetZoomFactor()
{
	return zoomFactor;
}

void Mandelbrot::SetZoomFactor(double value)
{
	zoomFactor = value;
}

std::shared_ptr<double> Mandelbrot::GetMdbValMap(
		const size_t width, const size_t height)
{
	std::shared_ptr<double> mdbValMap(new double[width * height],
			std::default_delete<double[]>());
	std::shared_ptr<std::thread> threadPtrArr[threadNum];
	size_t heightBegin = 0, heightEnd = 0, blockSize = height/threadNum;
	blockSize += (height % threadNum) ? 1 : 0;

	for (size_t i = 0; i < threadNum && heightEnd < height ; ++i) {
		heightBegin = blockSize * i;
		heightEnd = blockSize * (i+1);
		heightEnd = heightEnd > height ? height : heightEnd;

		threadPtrArr[i] = std::make_shared<std::thread>(
				GetMdbValMapThread, *this, mdbValMap,
				width, height, heightBegin, heightEnd);
	}
	for (size_t i = 0; i < threadNum; ++i)
		threadPtrArr[i]->join();

	return mdbValMap;
}

double Mandelbrot::GetMdbVal(double a, double b, double r, size_t iteration)
{
	size_t i, n;
	double result = iteration - 1;	// limit result between 0 ~ iteration-1
	double x = a, y = b, x2 = a*a, y2 = b*b;

	for (i = 0; i < iteration && x2+y2 < r; ++i) {
		y = 2 * x * y + b;
		x = x2 - y2 + a;
		x2 = pow(x, 2);
		y2 = pow(y, 2);
	}
	for (n = i+2; i < n; ++i) {
		y = 2 * x * y + b;
		x = x2 - y2 + a;
		x2 = pow(x, 2);
		y2 = pow(y, 2);
	}
	if(i < iteration)
		result = i + 1.0 - log(log(sqrt(x2 + y2)))/log(2.0);

	return result;
}

void Mandelbrot::GetMdbValMapThread(
		const Mandelbrot &mdb, std::shared_ptr<double> mdbValMap,
		size_t width, size_t height, size_t hBeg, size_t hEnd)
{
	double xMin = mdb.centerX - 3.0 / mdb.zoomFactor;
	double xMax = mdb.centerX + 3.0 / mdb.zoomFactor;
	double yMin = mdb.centerY - 3.0 * height / width / mdb.zoomFactor;
	double yMax = mdb.centerY + 3.0 * height / width / mdb.zoomFactor;
	double xScale = (xMax - xMin) / width;
	double yScale = (yMax - yMin) / height;
	double *mdbValMapPtr = mdbValMap.get();

	for (size_t i = hBeg; i < hEnd; ++i) {
		double y = yMax - i * yScale;
		size_t offset = i * width;
		for (size_t j = 0; j < width; ++j) {
			double x = xMin + j * xScale;
			mdbValMapPtr[offset + j] = GetMdbVal(x, y, mdb.radius, mdb.iteration);
		}
	}
}
