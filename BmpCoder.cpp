#include <bitset>
#include "BmpCoder.h"
#include "BmpFactory.h"
#include "Common.h"
#include "Mandelbrot.h"

BmpCoder::BmpCoder(char m)
{
	SetMask(m);
}

void BmpCoder::SetMask(char m)
{
	mask = m;
}

bool BmpCoder::IsValidBmp(const BmpFileHeader &fileHdr, const BmpInfoHeader &infoHdr)
{
	bool result =
		fileHdr.bfType == 0x4d42 &&
		fileHdr.bfReserved1 == 0x4248 &&
		infoHdr.biBitPerPxl == 24 &&
		static_cast<size_t>(infoHdr.biWidth*infoHdr.biHeight) < MAXLENGTH;
	return result;
}

int BmpCoder::Decode(std::shared_ptr<const char[]> bmpFile, std::ofstream &ofs)
{
	int result = -1;
	BmpFileHeader fileHdr;
	BmpInfoHeader infoHdr;
	const char *bmpFilePtr = bmpFile.get();
	fileHdr.ReadHeader(bmpFilePtr);
	bmpFilePtr += 14;
	infoHdr.ReadHeader(bmpFilePtr);
	bmpFilePtr += 40;
	if (IsValidBmp(fileHdr, infoHdr))
		result = GetPlain(bmpFilePtr, infoHdr.biImageSize, ofs);
	else
		throw std::runtime_error("cannot decode this bmp file");
	return result;
}

int BmpCoder::GetPlain(const char *imageBeg, size_t imageSize, std::ofstream &ofs)
{
	const std::bitset<8> bitSet(mask);
	const char *colorPtr = imageBeg;
	const char *imageEnd = imageBeg + imageSize;
	size_t bitCounter = 0, outputCounter = 0, plainFileSize = 0;
	std::shared_ptr<char> buffer(new char[BUFFSIZE], std::default_delete<char[]>());
	char *buffPtr = buffer.get();
	for (size_t i = 0; i < sizeof(plainFileSize)*8; ++i, colorPtr += 3)
		plainFileSize |= (*colorPtr & 0x1) << i;
	for (size_t i = 0; i < 3; colorPtr = imageBeg + ++i) {
		for (; colorPtr < imageEnd && outputCounter < plainFileSize; colorPtr += 3) {
			// here suppose all data bits stored from lowest bit sequentialy
			for (size_t j = 0; j < bitSet.count(); ++j) {
				if (*colorPtr >> j & 0x1)
					*buffPtr |= 0x1 << bitCounter;
				else
					*buffPtr &= ~(0x1 << bitCounter);
				if (++bitCounter == 8) {
					bitCounter = 0;
					size_t offset = ++buffPtr - buffer.get();
					if (outputCounter + offset == plainFileSize ||
							offset == BUFFSIZE) {
						ofs.write(buffer.get(), offset);
						outputCounter += offset;
						buffPtr = buffer.get();
					}
				}
			}
		}
	}
	return 0;
}

unsigned BmpCoder::Encode(std::ifstream &ifs, std::shared_ptr<char[]> &bmpFile)
{
	unsigned result = 0;
	ifs.seekg(0, std::fstream::beg);
	size_t fileSize = CalcFileSize(ifs);
	std::bitset<8> bitSetOfMask(mask);
	size_t imageSize = fileSize * 8 / bitSetOfMask.count() / 3;
	size_t width = WIDTHDFT, height = HEIGHTDFT;
	while (imageSize > width*height) {
		width *= 2;
		height *= 2;
		if (width * height > MAXLENGTH) {
			bmpFile = nullptr;
			throw std::out_of_range("file is too large");
		}
	}
	BmpFactory bmpFactory;
	bmpFactory.SetBiBitPerPxl(24);
	bmpFactory.SetBfReserved1(0x4248);	// "HB"
	bmpFactory.SetResolution(width, height);
	bmpFactory.GetFile(bmpFile);
	if (0 == GetCipher(ifs, fileSize, bmpFile.get() + bmpFactory.GetBfOffBits(),
				bmpFactory.GetBiImageSize()))
		result = bmpFactory.GetBfSize();
	return result;
}

int BmpCoder::GetCipher(std::ifstream &ifs, size_t fileSize, char *imageBeg, size_t imageSize)
{
	const std::bitset<8> bitSet(mask);
	char *colorPtr = imageBeg;
	char *imageEnd = imageBeg + imageSize;
	size_t bitCounter = 0, outputCounter = 0, plainFileSize = fileSize;
	std::shared_ptr<char> buffer(new char[fileSize], std::default_delete<char[]>());
	char *buffPtr = buffer.get();
	ifs.read(buffPtr, fileSize);
	for (size_t i = 0; i < sizeof(plainFileSize)*8; ++i, colorPtr += 3)
		(plainFileSize >> i) & 0x1 ? *colorPtr |= 0x1 : *colorPtr &= ~0x1;
	for (size_t i = 0; i < 3; colorPtr = imageBeg + ++i) {
		for (; colorPtr < imageEnd && outputCounter < plainFileSize; colorPtr += 3) {
			// here suppose all data bits stored from lowest bit sequentialy
			for (size_t j = 0; j < bitSet.count(); ++j) {
				if (*buffPtr >> bitCounter & 0x1)
					*colorPtr |= 0x1 << j;
				else
					*colorPtr &= ~(0x1 << j);
				if (++bitCounter == 8) {
					++buffPtr;
					++outputCounter;
					bitCounter = 0;
				}
			}
		}
	}
	return 0;
}
