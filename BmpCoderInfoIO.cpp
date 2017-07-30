#include "BmpCoderInfoIO.h"

std::istream& BmpCoderInfoIO::ReadInfo(std::istream &is)
{
	char first3Byte[3];
	ReadBmpFileHeader(is, bmpFileHdr);
	ReadBmpInfoHeader(is, bmpInfoHdr);
	is.read(first3Byte, sizeof(first3Byte));
	mask = 0;
	for (size_t i = 0; i < sizeof(first3Byte)/sizeof(first3Byte[0]); ++i)
		mask |= (first3Byte[i] & 0x01) << i;
	return is;
}

std::ostream& BmpCoderInfoIO::WriteInfo(std::ostream &os)
{
	WriteBmpFileHeader(os, bmpFileHdr);
	WriteBmpInfoHeader(os, bmpInfoHdr);
	// TODO: write mask
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

void BmpCoderInfoIO::ReadBmpFileHeader(std::istream &is)
{
	ReadBmpFileHeader(is, bmpFileHdr);
}

void BmpCoderInfoIO::ReadBmpInfoHeader(std::istream &is)
{
	ReadBmpInfoHeader(is, bmpInfoHdr);
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

void BmpCoderInfoIO::WriteBmpFileHeader(std::ostream &os, BmpFileHeader &bmpFileHdr)
{
	os.write((char*)&bmpFileHdr.bfType, sizeof(bmpFileHdr.bfType));
	os.write((char*)&bmpFileHdr.bfSize, sizeof(bmpFileHdr.bfSize));
	os.write((char*)&bmpFileHdr.bfReserved1, sizeof(bmpFileHdr.bfReserved1));
	os.write((char*)&bmpFileHdr.bfReserved2, sizeof(bmpFileHdr.bfReserved2));
	os.write((char*)&bmpFileHdr.bfOffBits, sizeof(bmpFileHdr.bfOffBits));
}

void BmpCoderInfoIO::WriteBmpInfoHeader(std::ostream &os, BmpInfoHeader &bmpInfoHdr)
{
	os.write((char*)&bmpInfoHdr.biSize, sizeof(bmpInfoHdr.biSize));
	os.write((char*)&bmpInfoHdr.biWidth, sizeof(bmpInfoHdr.biWidth));
	os.write((char*)&bmpInfoHdr.biHeight, sizeof(bmpInfoHdr.biHeight));
	os.write((char*)&bmpInfoHdr.biPlanes, sizeof(bmpInfoHdr.biPlanes));
	os.write((char*)&bmpInfoHdr.biBitCount, sizeof(bmpInfoHdr.biBitCount));
	os.write((char*)&bmpInfoHdr.biCompression, sizeof(bmpInfoHdr.biCompression));
	os.write((char*)&bmpInfoHdr.biSizeImage, sizeof(bmpInfoHdr.biSizeImage));
	os.write((char*)&bmpInfoHdr.biXPelsPerMeter, sizeof(bmpInfoHdr.biXPelsPerMeter));
	os.write((char*)&bmpInfoHdr.biYPelsPerMeter, sizeof(bmpInfoHdr.biYPelsPerMeter));
	os.write((char*)&bmpInfoHdr.biClrUsed, sizeof(bmpInfoHdr.biClrUsed));
	os.write((char*)&bmpInfoHdr.biClrImportant, sizeof(bmpInfoHdr.biClrImportant));
}

bool BmpCoderInfoIO::IsValidBmp(const BmpFileHeader &fileHdr, const BmpInfoHeader &infoHdr)
{
	bool isValidBmp = true;
	if (fileHdr.bfType != 0x424d)		// BM
		isValidBmp = false;
	if (fileHdr.bfReserved1 != 0x4842)	// HB
		isValidBmp = false;
	if (infoHdr.biBitCount != 24)
		isValidBmp = false;
	return isValidBmp;
}

std::istream& BmpCoderInfoIO::Read(std::istream &is, char *buf, size_t size)
{
	// TODO
	return is;
}

std::ostream& BmpCoderInfoIO::Write(std::ostream &os, char *buf, size_t size)
{
	// TODO
	return os;
}

size_t BmpCoderInfoIO::Gcount() const
{
	return gcount;
}

const Coder* BmpCoderInfoIO::GetCoder() const
{
	return coderPtr;
}
