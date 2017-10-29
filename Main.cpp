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

using namespace std;

void ShowBmpInfo(std::string bmpFileName)
{
	BmpFileHeader bmpFileHdr;
	BmpInfoHeader bmpInfoHdr;
	std::fstream bmpFile(bmpFileName, ios::in | ios::binary);
	if (bmpFile.good()) {
		bmpFileHdr.ReadHeader(bmpFile);
		bmpInfoHdr.ReadHeader(bmpFile);
		cout << bmpFileHdr << bmpInfoHdr;
	} else {
		string errorMsg = "open " + bmpFileName + " failed!";
		cout << errorMsg << endl;
	}
}

void TestXor()
{
	XorCoderInfoIO xorCoder;
	EncodeStrategy encoderStg(&xorCoder);
	DecodeStrategy decoderStg(&xorCoder);
	encoderStg.Encode("/tmp/tmp", "/tmp/tmp.cipher");
	decoderStg.Decode("/tmp/tmp.cipher", "/tmp/tmp.plain");
}

void TestHuff()
{
	HuffmanCoderInfoIO huffmanCoder;
	EncodeStrategy encoderStg(&huffmanCoder);
	DecodeStrategy decoderStg(&huffmanCoder);
	encoderStg.Encode("/tmp/tmp", "/tmp/tmp.cipher");
	decoderStg.Decode("/tmp/tmp.cipher", "/tmp/tmp.plain");
}

void TestBmpFactory()
{
	std::string bmpFileName("/tmp/tmp.bmp");
	BmpFactory bmp;
	bmp.GetFile(bmpFileName, ios::out | ios::binary);
}

int main(int argc, char **argv)
{

	return 0;
}

