#include "BmpCommon.h"

BmpFileHeader::BmpFileHeader(): bfType(0x424d),
	bfSize(0), bfReserved1(0), bfReserved2(0), bfOffBits(0)
{
}

void BmpFileHeader::ReadHeader(std::istream &is)
{
	is.read((char*)&bfType, sizeof(bfType));
	is.read((char*)&bfSize, sizeof(bfSize));
	is.read((char*)&bfReserved1, sizeof(bfReserved1));
	is.read((char*)&bfReserved2, sizeof(bfReserved2));
	is.read((char*)&bfOffBits, sizeof(bfOffBits));
}

void BmpFileHeader::WriteHeader(std::ostream &os)
{
	os.write((char*)&bfType, sizeof(bfType));
	os.write((char*)&bfSize, sizeof(bfSize));
	os.write((char*)&bfReserved1, sizeof(bfReserved1));
	os.write((char*)&bfReserved2, sizeof(bfReserved2));
	os.write((char*)&bfOffBits, sizeof(bfOffBits));
}

BmpInfoHeader::BmpInfoHeader():
	biSize(40), biWidth(0), biHeight(0), biPlanes(1), biBitPerPxl(0),
	biCompression(0), biImageSize(0), biXPxlsPerMeter(0), biYPxlsPerMeter(0),
	biClrUsed(0), biClrImportant(0)
{
}
void BmpInfoHeader::ReadHeader(std::istream &is)
{
	is.read((char*)&biSize, sizeof(biSize));
	is.read((char*)&biWidth, sizeof(biWidth));
	is.read((char*)&biHeight, sizeof(biHeight));
	is.read((char*)&biPlanes, sizeof(biPlanes));
	is.read((char*)&biBitPerPxl, sizeof(biBitPerPxl));
	is.read((char*)&biCompression, sizeof(biCompression));
	is.read((char*)&biImageSize, sizeof(biImageSize));
	is.read((char*)&biXPxlsPerMeter, sizeof(biXPxlsPerMeter));
	is.read((char*)&biYPxlsPerMeter, sizeof(biYPxlsPerMeter));
	is.read((char*)&biClrUsed, sizeof(biClrUsed));
	is.read((char*)&biClrImportant, sizeof(biClrImportant));
}

void BmpInfoHeader::WriteHeader(std::ostream &os)
{
	os.write((char*)&biSize, sizeof(biSize));
	os.write((char*)&biWidth, sizeof(biWidth));
	os.write((char*)&biHeight, sizeof(biHeight));
	os.write((char*)&biPlanes, sizeof(biPlanes));
	os.write((char*)&biBitPerPxl, sizeof(biBitPerPxl));
	os.write((char*)&biCompression, sizeof(biCompression));
	os.write((char*)&biImageSize, sizeof(biImageSize));
	os.write((char*)&biXPxlsPerMeter, sizeof(biXPxlsPerMeter));
	os.write((char*)&biYPxlsPerMeter, sizeof(biYPxlsPerMeter));
	os.write((char*)&biClrUsed, sizeof(biClrUsed));
	os.write((char*)&biClrImportant, sizeof(biClrImportant));
}

std::ostream& operator<<(std::ostream &os, const BmpFileHeader &bfHdr)
{
	os << "bfType: " << bfHdr.bfType << std::endl;
	os << "bfSize: " << bfHdr.bfSize << std::endl;
	os << "bfReserved1: " << bfHdr.bfReserved1 << std::endl;
	os << "bfReserved2: " << bfHdr.bfReserved2 << std::endl;
	os << "bfOffBits: " << bfHdr.bfOffBits << std::endl;
	return os;
}

std::ostream& operator<<(std::ostream &os, const BmpInfoHeader &biHdr)
{
	os << "biSize: " << biHdr.biSize << std::endl;
	os << "biWidth: " << biHdr.biWidth << std::endl;
	os << "biHeight: " << biHdr.biHeight << std::endl;
	os << "biPlanes: " << biHdr.biPlanes << std::endl;
	os << "biBitPerPxl: " << biHdr.biBitPerPxl << std::endl;
	os << "biCompression: " << biHdr.biCompression << std::endl;
	os << "biImageSize: " << biHdr.biImageSize << std::endl;
	os << "biXPxlsPerMeter: " << biHdr.biXPxlsPerMeter << std::endl;
	os << "biYPxlsPerMeter: " << biHdr.biYPxlsPerMeter << std::endl;
	os << "biClrUsed: " << biHdr.biClrUsed << std::endl;
	os << "biClrImportant: " << biHdr.biClrImportant << std::endl;
	return os;
}

uint32_t BmpInfoHeader::GetBiImageSize()
{
	int lineBytes = (biWidth * biBitPerPxl/8 + 3) / 4 * 4;
	if (biWidth && !lineBytes)
		lineBytes = 4;
	return (lineBytes * biHeight);
}
