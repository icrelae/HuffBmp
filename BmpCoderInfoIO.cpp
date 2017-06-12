#include "BmpCoderInfoIO.h"

std::istream& BmpCoderInfoIO::ReadInfo(std::istream &is)
{
	ReadBmpFileHeader(is, bmpFileHdr);
	ReadBmpInfoHeader(is, bmpInfoHdr);
	return is;
}

std::ostream& BmpCoderInfoIO::WriteInfo(std::ostream &os)
{
	return os;
}

enum PreprcsRslt BmpCoderInfoIO::Preprocess(std::istream &is)
{
	enum PreprcsRslt preprcsResult= RSLTERROR;
	ReadBmpFileHeader(is, bmpFileHdr);
	ReadBmpInfoHeader(is, bmpInfoHdr);
	if (IsValidBmp(bmpFileHdr, bmpInfoHdr))
		preprcsResult = RSLTOK;
	return preprcsResult;
}

enum PreprcsRslt BmpCoderInfoIO::Preprocess(std::istream &is, std::iostream &os)
{
	enum PreprcsRslt preprcsResult= RSLTERROR;
	ReadBmpFileHeader(os, bmpFileHdr);
	ReadBmpInfoHeader(os, bmpInfoHdr);
	if (IsValidBmp(bmpFileHdr, bmpInfoHdr))
		preprcsResult = RSLTOK;
	return preprcsResult;
}

void BmpCoderInfoIO::ReadBmpFileHeader(std::istream &is, BmpFileHeader &bmpFileHdr)
{
	is.read((char*)&bmpFileHdr.bfType, sizeof(bmpFileHdr.bfType));
	is.read((char*)&bmpFileHdr.bfSize, sizeof(bmpFileHdr.bfSize));
	is.read((char*)&bmpFileHdr.bfReserved1, sizeof(bmpFileHdr.bfReserved1));
	is.read((char*)&bmpFileHdr.bfReserved2, sizeof(bmpFileHdr.bfReserved2));
	is.read((char*)&bmpFileHdr.bfOffBits, sizeof(bmpFileHdr.bfOffBits));
}

void BmpCoderInfoIO::ReadBmpInfoHeader(std::istream &is, BmpInfoHeader &bmpInfoHdr)
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

bool BmpCoderInfoIO::IsValidBmp(const BmpFileHeader &fileHdr, const BmpInfoHeader &infoHdr)
{
	return (fileHdr.bfType == 0x424d && (infoHdr.biBitCount == 24 || infoHdr.biBitCount == 32));
}
