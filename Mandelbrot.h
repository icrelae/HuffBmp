#ifndef _MANDELBROT_H
#define _MANDELBROT_H
// 2017.08.23 19:17

#include <memory>

class Mandelbrot {
public:
	Mandelbrot();
private:
	double centerX;
	double centerY;
	double zoomFactor;
	double radius;
	size_t iteration;
	const unsigned char threadNum = 4;
	const unsigned blockSize = 1920 * 1080 / 4;

	void GetMdbValMap(std::shared_ptr<double> mdbValMap,
			const size_t width, const size_t height);
	static double GetMdbVal(double, double, double, size_t);
	static void GetMdbValMapThread(const Mandelbrot&,
			std::shared_ptr<double>, size_t width, size_t height,
			size_t hStart, size_t hEnd);
};

#endif // _MANDELBROT_H

