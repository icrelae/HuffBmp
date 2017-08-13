#include "BmpCoderInfoIO.h"

//TODO: obsolete
std::istream& BmpCoderInfoIO::ReadInfo(std::istream &is)
{
	char first3Byte[3];
	bmpFileHdr.ReadHeader(is);
	bmpInfoHdr.ReadHeader(is);
	is.read(first3Byte, sizeof(first3Byte));
	mask = 0;
	for (size_t i = 0; i < sizeof(first3Byte)/sizeof(first3Byte[0]); ++i)
		mask |= (first3Byte[i] & 0x01) << i;
	return is;
}

std::ostream& BmpCoderInfoIO::WriteInfo(std::ostream &os)
{
	bmpFileHdr.WriteHeader(os);
	bmpInfoHdr.WriteHeader(os);
	// TODO: write mask
	return os;
}

enum PreprcsRslt BmpCoderInfoIO::Preprocess(std::istream &is)
{
	enum PreprcsRslt preprcsResult= RSLTERROR;
	bmpFileHdr.ReadHeader(is);
	bmpInfoHdr.ReadHeader(is);
	if (IsValidBmp(bmpFileHdr, bmpInfoHdr))
		preprcsResult = RSLTOK;
	return preprcsResult;
}

enum PreprcsRslt BmpCoderInfoIO::Preprocess(std::istream &is, std::iostream &os)
{
	enum PreprcsRslt preprcsResult= RSLTERROR;
	bmpFileHdr.ReadHeader(os);
	bmpInfoHdr.ReadHeader(os);
	if (IsValidBmp(bmpFileHdr, bmpInfoHdr))
		preprcsResult = RSLTOK;
	return preprcsResult;
}

void BmpCoderInfoIO::ReadBmpFileHeader(std::istream &is)
{
	bmpFileHdr.ReadHeader(is);
}

void BmpCoderInfoIO::ReadBmpInfoHeader(std::istream &is)
{
	bmpInfoHdr.ReadHeader(is);
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
