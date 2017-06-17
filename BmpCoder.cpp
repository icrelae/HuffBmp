#include <ostream>
#include "BmpCoder.h"

std::string BmpCoder::Encode(std::string &originCode) const
{
	std::string result = "";
	std::swap(result, originCode);
	return result;
}

std::string BmpCoder::Decode(std::string &originCode) const
{
	std::string result = "";
	std::swap(result, originCode);
	return result;
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
	os << "biBitCount: " << biHdr.biBitCount << std::endl;
	os << "biCompression: " << biHdr.biCompression << std::endl;
	os << "biSizeImage: " << biHdr.biSizeImage << std::endl;
	os << "biXPelsPerMeter: " << biHdr.biXPelsPerMeter << std::endl;
	os << "biYPelsPerMeter: " << biHdr.biYPelsPerMeter << std::endl;
	os << "biClrUsed: " << biHdr.biClrUsed << std::endl;
	os << "biClrImportant: " << biHdr.biClrImportant << std::endl;
	return os;
}
