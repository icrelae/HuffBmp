#include <thread>
#include <cmath>
#include "Mandelbrot.h"

Mandelbrot::Mandelbrot():
	centerX(-0.5), centerY(0), zoomFactor(2), radius(4), iteration(50)
{
}

void Mandelbrot::GetMdbValMap(std::shared_ptr<double> mdbValMap,
		const size_t width, const size_t height)
{
	std::shared_ptr<std::thread> threadPtrArr[threadNum];

	for (size_t i = 0; i < threadNum; ++i) {
		size_t heightBegin = height / threadNum * i;
		size_t heightEnd = height / threadNum * (i+1);
		heightEnd = heightEnd > height ? height : heightEnd;

		threadPtrArr[i] = std::make_shared<std::thread>(
				GetMdbValMapThread, *this, mdbValMap,
				width, height, heightBegin, heightEnd);
	}
	for (size_t i = 0; i < threadNum; ++i)
		threadPtrArr[i]->join();
}

double Mandelbrot::GetMdbVal(double a, double b, double r, size_t iteration)
{
	size_t i, n;
	double result = iteration;
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
	if(i <= iteration)
		result = i + 1.0 - log(log(sqrt(x2 + y2)))/log(2.0);

	return result;
}

void Mandelbrot::GetMdbValMapThread(
		const Mandelbrot &mdb, std::shared_ptr<double> mdbValMap,
		size_t width, size_t height, size_t hStart, size_t hEnd)
{
	double xMin = mdb.centerX - 3 / mdb.zoomFactor;
	double xMax = mdb.centerX + 3 / mdb.zoomFactor;
	double yMin = mdb.centerY - 3 * height / width / mdb.zoomFactor;
	double yMax = mdb.centerY + 3 * height / width / mdb.zoomFactor;
	double xScale = (xMax - xMin) / width;
	double yScale = (yMax - yMin) / height;
	double *mdbValMapPtr = mdbValMap.get();

	for (size_t i = hStart;  i < hEnd; ++i) {
		double y = yMax - y * yScale;
		size_t lines = i * width;
		for (size_t j = 0; j < width; ++j) {
			double x = xMin + x * xScale;
			mdbValMapPtr[lines + j] = GetMdbVal(x, y, mdb.radius, mdb.iteration);
		}
	}
}
