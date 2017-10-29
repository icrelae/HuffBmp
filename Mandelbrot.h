#ifndef _MANDELBROT_H
#define _MANDELBROT_H
// 2017.08.23 19:17

#include <memory>

class Mandelbrot {
public:
	Mandelbrot();
	std::shared_ptr<double> GetMdbValMap(const size_t, const size_t);
	size_t GetIteration();
private:
	double centerX;
	double centerY;
	double zoomFactor;
	double radius;
	size_t iteration;
	const unsigned char threadNum = 4;
	const unsigned blockSize = 1920 * 1080 / 4;

	static double GetMdbVal(double, double, double, size_t);
	static void GetMdbValMapThread(const Mandelbrot&,
			std::shared_ptr<double>, size_t width, size_t height,
			size_t hStart, size_t hEnd);
};

#endif // _MANDELBROT_H

