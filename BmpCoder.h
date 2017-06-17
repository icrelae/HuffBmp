#ifndef _BMPCODER_H
#define _BMPCODER_H
// 2017.06.09 21:22

#include "Coder.h"

class BmpFileHeader {
public:
	unsigned short bfType;
	unsigned int bfSize;
	unsigned short bfReserved1;
	unsigned short bfReserved2;
	unsigned int bfOffBits;
};

class BmpInfoHeader {
public:
	unsigned int biSize;
	unsigned int biWidth;
	unsigned int biHeight;
	unsigned short biPlanes;
	unsigned short biBitCount;
	unsigned int biCompression;
	unsigned int biSizeImage;
	unsigned int biXPelsPerMeter;
	unsigned int biYPelsPerMeter;
	unsigned int biClrUsed;
	unsigned int biClrImportant;
};

class BmpCoder: public Coder {
public:
	virtual std::string Encode(std::string&) const override;
	virtual std::string Decode(std::string&) const override;
};

std::ostream& operator<<(std::ostream&, const BmpFileHeader&);
std::ostream& operator<<(std::ostream&, const BmpInfoHeader&);

#endif // _BMPCODER_H
