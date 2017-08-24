#include "BmpFactory.h"

BmpFactory::BmpFactory()
{
	bmpFileHdr.bfOffBits = 54;
	bmpInfoHdr.biWidth = 1920;
	bmpInfoHdr.biHeight = 1080;
	bmpInfoHdr.biBitPerPxl = 24;
	bmpInfoHdr.biXPxlsPerMeter = 0;
	bmpInfoHdr.biYPxlsPerMeter = 0;
	UpdateBmpHeader();
}

void BmpFactory::UpdateBmpHeader()
{
	bmpInfoHdr.biImageSize = bmpInfoHdr.GetBiImageSize();
	bmpFileHdr.bfSize = bmpFileHdr.bfOffBits + bmpInfoHdr.biImageSize;
}

bool BmpFactory::GetFile(const std::string fileName, const std::ios_base::openmode mode)
{
	std::fstream bmpFile(fileName, mode);
	return true;
}

void BmpFactory::SetBitPerPxl(const int bits)
{
	bmpInfoHdr.biBitPerPxl = bits;
	UpdateBmpHeader();
}

void BmpFactory::SetResolution(const int width, const int height)
{
	bmpInfoHdr.biWidth = width;
	bmpInfoHdr.biHeight = height;
	UpdateBmpHeader();
}
