#ifndef _BMPFACTORY_H
#define _BMPFACTORY_H
// 2017.08.13 23:10

#include "FileFactory.h"
#include "BmpCommon.h"
#include "Mandelbrot.h"

class BmpFactory: public FileFactory {
public:
	BmpFactory();
	virtual bool GetFile(const std::string, const std::ios_base::openmode) override;
	void SetBitPerPxl(const size_t);
	void SetResolution(const size_t, const size_t);
private:
	Mandelbrot mandelbrot;
	BmpFileHeader bmpFileHdr;
	BmpInfoHeader bmpInfoHdr;

	void UpdateBmpHeader();
};

#endif // _BMPFACTORY_H

