#include "BmpCoderInfoIO.h"

void BmpCoderInfoIO::ReadBmpFileHeader(std::istream &is)
{
	is.read((char*)&bmpFileHdr.bfType, sizeof(bmpFileHdr.bfType));
	is.read((char*)&bmpFileHdr.bfSize, sizeof(bmpFileHdr.bfSize));
	is.read((char*)&bmpFileHdr.bfReserved1, sizeof(bmpFileHdr.bfReserved1));
	is.read((char*)&bmpFileHdr.bfReserved2, sizeof(bmpFileHdr.bfReserved2));
	is.read((char*)&bmpFileHdr.bfOffBits, sizeof(bmpFileHdr.bfOffBits));
}

void BmpCoderInfoIO::ReadBmpInfoHeader(std::istream &is)
{
	is.read((char*)&bmpInfoHdr.biSize, sizeof(bmpInfoHdr.biSize));
	is.read((char*)&bmpInfoHdr.biWidth, sizeof(bmpInfoHdr.biWidth));
	is.read((char*)&bmpInfoHdr.biHeight, sizeof(bmpInfoHdr.biHeight));
	is.read((char*)&bmpInfoHdr.biPlanes, sizeof(bmpInfoHdr.biPlanes));
	is.read((char*)&bmpInfoHdr.biBitCount, sizeof(bmpInfoHdr.biBitCount));
	is.read((char*)&bmpInfoHdr.biCompression, sizeof(bmpInfoHdr.biCompression));
	is.read((char*)&bmpInfoHdr.biSizeImage, sizeof(bmpInfoHdr.biSizeImage));
	is.read((char*)&bmpInfoHdr.biXPelsPerMeter, sizeof(bmpInfoHdr.biXPelsPerMeter));
	is.read((char*)&bmpInfoHdr.biYPelsPerMeter, sizeof(bmpInfoHdr.biYPelsPerMeter));
	is.read((char*)&bmpInfoHdr.biClrUsed, sizeof(bmpInfoHdr.biClrUsed));
	is.read((char*)&bmpInfoHdr.biClrImportant, sizeof(bmpInfoHdr.biClrImportant));
}
