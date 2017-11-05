#include <cstring>
#include "BmpCommon.h"

BmpFileHeader::BmpFileHeader(): bfType(0x4d42),
	bfSize(0), bfReserved1(0), bfReserved2(0), bfOffBits(0)
{
}

void BmpFileHeader::ReadHeader(std::istream &is)
{
	is.read(reinterpret_cast<char*>(&bfType), sizeof(bfType));
	is.read(reinterpret_cast<char*>(&bfSize), sizeof(bfSize));
	is.read(reinterpret_cast<char*>(&bfReserved1), sizeof(bfReserved1));
	is.read(reinterpret_cast<char*>(&bfReserved2), sizeof(bfReserved2));
	is.read(reinterpret_cast<char*>(&bfOffBits), sizeof(bfOffBits));
}

void BmpFileHeader::WriteHeader(std::ostream &os)
{
	os.write(reinterpret_cast<char*>(&bfType), sizeof(bfType));
	os.write(reinterpret_cast<char*>(&bfSize), sizeof(bfSize));
	os.write(reinterpret_cast<char*>(&bfReserved1), sizeof(bfReserved1));
	os.write(reinterpret_cast<char*>(&bfReserved2), sizeof(bfReserved2));
	os.write(reinterpret_cast<char*>(&bfOffBits), sizeof(bfOffBits));
}

void BmpFileHeader::WriteHeader(signed char *ptr)
{
	memcpy(ptr, &bfType, sizeof(bfType));
	ptr += sizeof(bfType);
	memcpy(ptr, &bfSize, sizeof(bfSize));
	ptr += sizeof(bfSize);
	memcpy(ptr, &bfReserved1, sizeof(bfReserved1));
	ptr += sizeof(bfReserved1);
	memcpy(ptr, &bfReserved2, sizeof(bfReserved2));
	ptr += sizeof(bfReserved2);
	memcpy(ptr, &bfOffBits, sizeof(bfOffBits));
	ptr += sizeof(bfOffBits);
}

BmpInfoHeader::BmpInfoHeader():
	biSize(40), biWidth(0), biHeight(0), biPlanes(1), biBitPerPxl(0),
	biCompression(0), biImageSize(0), biXPxlsPerMeter(0), biYPxlsPerMeter(0),
	biClrUsed(0), biClrImportant(0)
{
}
void BmpInfoHeader::ReadHeader(std::istream &is)
{
	is.read(reinterpret_cast<char*>(&biSize), sizeof(biSize));
	is.read(reinterpret_cast<char*>(&biWidth), sizeof(biWidth));
	is.read(reinterpret_cast<char*>(&biHeight), sizeof(biHeight));
	is.read(reinterpret_cast<char*>(&biPlanes), sizeof(biPlanes));
	is.read(reinterpret_cast<char*>(&biBitPerPxl), sizeof(biBitPerPxl));
	is.read(reinterpret_cast<char*>(&biCompression), sizeof(biCompression));
	is.read(reinterpret_cast<char*>(&biImageSize), sizeof(biImageSize));
	is.read(reinterpret_cast<char*>(&biXPxlsPerMeter), sizeof(biXPxlsPerMeter));
	is.read(reinterpret_cast<char*>(&biYPxlsPerMeter), sizeof(biYPxlsPerMeter));
	is.read(reinterpret_cast<char*>(&biClrUsed), sizeof(biClrUsed));
	is.read(reinterpret_cast<char*>(&biClrImportant), sizeof(biClrImportant));
}

void BmpInfoHeader::WriteHeader(std::ostream &os)
{
	os.write(reinterpret_cast<char*>(&biSize), sizeof(biSize));
	os.write(reinterpret_cast<char*>(&biWidth), sizeof(biWidth));
	os.write(reinterpret_cast<char*>(&biHeight), sizeof(biHeight));
	os.write(reinterpret_cast<char*>(&biPlanes), sizeof(biPlanes));
	os.write(reinterpret_cast<char*>(&biBitPerPxl), sizeof(biBitPerPxl));
	os.write(reinterpret_cast<char*>(&biCompression), sizeof(biCompression));
	os.write(reinterpret_cast<char*>(&biImageSize), sizeof(biImageSize));
	os.write(reinterpret_cast<char*>(&biXPxlsPerMeter), sizeof(biXPxlsPerMeter));
	os.write(reinterpret_cast<char*>(&biYPxlsPerMeter), sizeof(biYPxlsPerMeter));
	os.write(reinterpret_cast<char*>(&biClrUsed), sizeof(biClrUsed));
	os.write(reinterpret_cast<char*>(&biClrImportant), sizeof(biClrImportant));
}

void BmpInfoHeader::WriteHeader(signed char *ptr)
{
	memcpy(ptr, &biSize, sizeof(biSize));
	ptr += sizeof(biSize);
	memcpy(ptr, &biWidth, sizeof(biWidth));
	ptr += sizeof(biWidth);
	memcpy(ptr, &biHeight, sizeof(biHeight));
	ptr += sizeof(biHeight);
	memcpy(ptr, &biPlanes, sizeof(biPlanes));
	ptr += sizeof(biPlanes);
	memcpy(ptr, &biBitPerPxl, sizeof(biBitPerPxl));
	ptr += sizeof(biBitPerPxl);
	memcpy(ptr, &biCompression, sizeof(biCompression));
	ptr += sizeof(biCompression);
	memcpy(ptr, &biImageSize, sizeof(biImageSize));
	ptr += sizeof(biImageSize);
	memcpy(ptr, &biXPxlsPerMeter, sizeof(biXPxlsPerMeter));
	ptr += sizeof(biXPxlsPerMeter);
	memcpy(ptr, &biYPxlsPerMeter, sizeof(biYPxlsPerMeter));
	ptr += sizeof(biYPxlsPerMeter);
	memcpy(ptr, &biClrUsed, sizeof(biClrUsed));
	ptr += sizeof(biClrUsed);
	memcpy(ptr, &biClrImportant, sizeof(biClrImportant));
	ptr += sizeof(biClrImportant);
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
