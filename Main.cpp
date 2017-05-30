/* 2017.05.12 09:04
 */
#include <iostream>
#include <string>
#include <vector>
#include "HuffmanCoderInfoIO.h"
#include "EncodeStrategy.h"

using namespace std;

int main(int argc, char **argv)
{
	HuffmanCoderInfoIO huffman;
	EncodeStrategy encoderStg(&huffman);
	encoderStg.Encode("/tmp/tmp", "/tmp/tmp.huf");

	return 0;
}

