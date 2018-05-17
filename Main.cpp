/* 2017.05.12 09:04
 */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "EncodeStrategy.h"
#include "DecodeStrategy.h"
#include "HuffmanCoderInfoIO.h"
#include "XorCoderInfoIO.h"
#include "BmpFactory.h"
#include "BmpCoder.h"
#include "Common.h"

using namespace std;

void TestXor()
{
	XorCoderInfoIO xorCoder;
	EncodeStrategy encoderStg(&xorCoder);
	DecodeStrategy decoderStg(&xorCoder);
	encoderStg.Encode("/tmp/tmp", "/tmp/tmp.cipher");
	decoderStg.Decode("/tmp/tmp.cipher", "/tmp/tmp.plain");
	system("md5sum /tmp/tmp /tmp/tmp.plain");
}

void TestHuff()
{
	HuffmanCoderInfoIO huffmanCoder;
	EncodeStrategy encoderStg(&huffmanCoder);
	DecodeStrategy decoderStg(&huffmanCoder);
	encoderStg.Encode("/tmp/tmp", "/tmp/tmp.cipher");
	decoderStg.Decode("/tmp/tmp.cipher", "/tmp/tmp.plain");
	system("md5sum /tmp/tmp /tmp/tmp.plain");
}

void TestBmpFactory()
{
	std::string bmpFileName("/tmp/tmp.bmp");
	BmpFactory bmp;
	bmp.GetFile(bmpFileName);
}

void TestBmpCoder()
{
	BmpCoder bmpCoder;
	std::string fileForEncode = "/tmp/tmp";
	std::string fileForDecode = fileForEncode + ".plain";
	std::string fileForBmp = fileForEncode + ".bmp";
	std::shared_ptr<char[]> bmpSptr;
	std::ifstream ifs(fileForEncode, std::ios::binary);
	std::ofstream ofsPlain(fileForDecode, std::ios::binary);
	std::ofstream ofsBmp(fileForBmp, std::ios::binary);
	unsigned fileSize = bmpCoder.Encode(ifs, bmpSptr);
	ofsBmp.write(bmpSptr.get(), fileSize);
	bmpCoder.Decode(bmpSptr, ofsPlain);
	ofsPlain.close();
	system("md5sum /tmp/tmp /tmp/tmp.plain");
}

void ShowHelp(std::ostream &os)
{
	os << "show bmp file header and info header" << endl;
}

void ShowBmpInfo(std::ostream &os, const BmpFileHeader &bmpFileHdr, const
		BmpInfoHeader &bmpInfoHdr)
{
	os << bmpFileHdr << bmpInfoHdr;
}

bool ReadBmpInfo(std::string bmpFileName, size_t &length,
	BmpFileHeader &bmpFileHdr, BmpInfoHeader &bmpInfoHdr)
{
	std::fstream bmpFile(bmpFileName, ios::in | ios::binary);
	if (!bmpFile.good())
		return false;
	length = CalcFileSize(bmpFile);
	bmpFileHdr.ReadHeader(bmpFile);
	bmpInfoHdr.ReadHeader(bmpFile);
	return true;
}

int main(int argc, char **argv)
{
	if (argc < 2)
		return 1;

	size_t length;
	BmpFileHeader bmpFileHdr;
	BmpInfoHeader bmpInfoHdr;
	std::string argv1(argv[1]);
	if (!ReadBmpInfo(argv1, length, bmpFileHdr, bmpInfoHdr)) {
		string errorMsg = "open " + argv1 + " failed!";
		cout << errorMsg << endl;
		return 1;
	}

	switch (argc) {
	case 2:
		ShowBmpInfo(cout, bmpFileHdr, bmpInfoHdr);
		break;
	default:
		ShowHelp(cout);
		break;
	}

	return 0;
}

