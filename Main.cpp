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
#include "BmpCoderInfoIO.h"

using namespace std;

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

int main(int argc, char **argv)
{
	TestXor();
	TestHuff();
	std::ifstream ifs(string(argv[1]), fstream::binary);
	BmpCoderInfoIO bmpCoder;
	bmpCoder.ReadBmpFileHeader(ifs);
	bmpCoder.ReadBmpInfoHeader(ifs);
	cout << bmpCoder.bmpFileHdr << bmpCoder.bmpInfoHdr;

	return 0;
}

