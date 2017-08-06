#ifndef _BMPCOMMON_H
#define _BMPCOMMON_H
// 2017.08.05 14:05

#include <cstdint>
#include <iostream>

class BmpFileHeader {
public:
	uint16_t	bfType;
	uint32_t	bfSize;
	uint16_t	bfReserved1;
	uint16_t	bfReserved2;
	uint32_t	bfOffBits;

	void ReadHeader(std::istream&);
	void WriteHeader(std::ostream&);
};

class BmpInfoHeader {
public:
	uint32_t	biSize;
	int32_t		biWidth;
	int32_t		biHeight;
	uint16_t	biPlanes;
	uint16_t	biBitCount;
	uint32_t	biCompression;
	uint32_t	biSizeImage;
	int32_t		biXPelsPerMeter;
	int32_t		biYPelsPerMeter;
	uint32_t	biClrUsed;
	uint32_t	biClrImportant;

	void ReadHeader(std::istream&);
	void WriteHeader(std::ostream&);
};

std::ostream& operator<<(std::ostream&, const BmpFileHeader&);
std::ostream& operator<<(std::ostream&, const BmpInfoHeader&);

#endif // _BMPCOMMON_H
