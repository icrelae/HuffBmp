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
	unsigned iteration;
	double GetMdbVal(double, double);
	void GetMdbValMap(std::shared_ptr<double> mdbValMap,
			const unsigned width, const unsigned height,
			const unsigned hStart, const unsigned hEnd);
};

#endif // _MANDELBROT_H

