#include "HuffmanCoder.h"

HuffmanCoder::HuffmanCoder(const std::map<char, unsigned> &map):
	valueWeight(map), huffmanRoot(' ', 0)
{
}
