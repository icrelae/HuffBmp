/* 2017.05.12 09:04
 */
#include <iostream>
#include <string>
#include <vector>
#include "EncodeStrategy.h"
#include "DecodeStrategy.h"
#include "HuffmanCoderInfoIO.h"
#include "XorCoderInfoIO.h"

using namespace std;

int main(int argc, char **argv)
{
	XorCoderInfoIO xorCoder;
	HuffmanCoderInfoIO huffmanCoder;
	EncodeStrategy encoderStg(&xorCoder);
	DecodeStrategy decoderStg(&xorCoder);
	encoderStg.Encode("/tmp/tmp", "/tmp/tmp.cipher");
	decoderStg.Decode("/tmp/tmp.cipher", "/tmp/tmp.plain");

	return 0;
}

