#ifndef _BMPCOMMON_H
#define _BMPCOMMON_H
// 2017.08.05 14:05

#include <cstdint>
#include <iostream>

struct BmpFileHeader {
	uint16_t	bfType;		// BM(0x4D42)
	uint32_t	bfSize;		// size of whole bmp file
	uint16_t	bfReserved1;	// 0
	uint16_t	bfReserved2;	// 0
	uint32_t	bfOffBits;	// 14+40+sizeof(palette)

	BmpFileHeader();
	void ReadHeader(std::istream&);
	void WriteHeader(std::ostream&);
};

struct BmpInfoHeader {
	uint32_t	biSize;			// size of BmpInfoHeader(40)
	int32_t		biWidth;		// width in pixel
	int32_t		biHeight;		// height in pixel
	uint16_t	biPlanes;		// fixed value(1)
	uint16_t	biBitPerPxl;		// bit per pixel(1| 16| 24| 32)
	uint32_t	biCompression;		// compression method:
						//	0 - no compression(BI_RGB)
						//	1 - RLE 8(BI_RLE8)
						//	2 - RLE 4(BI_RLE4)
						//	3 - Bitfields(BI_BITFIELDS)
	uint32_t	biImageSize;		// ((biWidth*biBitPerPxl/8+3)/4*4 * biHeight)
						//	maybe is 0 if compression is BI_RGB
	int32_t		biXPxlsPerMeter;	// pixels per meter on X-axis
	int32_t		biYPxlsPerMeter;	// pixels per meter on Y-axis
	uint32_t	biClrUsed;		// number of colors in using actually
						//	(0 means 2^biBitPerPxl)
	uint32_t	biClrImportant;		// number of important colrs
						//	(0 means all important)

	BmpInfoHeader();
	void ReadHeader(std::istream&);
	void WriteHeader(std::ostream&);
	uint32_t GetBiImageSize();
};

std::ostream& operator<<(std::ostream&, const BmpFileHeader&);
std::ostream& operator<<(std::ostream&, const BmpInfoHeader&);

#endif // _BMPCOMMON_H
