#include "HuffmanCoder.h"

HuffmanNode::HuffmanNode(char c, unsigned w,
		std::shared_ptr<HuffmanNode> l = nullptr,
		std::shared_ptr<HuffmanNode> r = nullptr):
	value(c), weight(w), left(l), right(r)
{
}

HuffmanCoder::HuffmanCoder(const std::map<char, unsigned> &map):
	valueWeight(map), huffmanRoot(' ', 0)
{
}
