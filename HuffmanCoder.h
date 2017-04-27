#ifndef _HUFFMANCODER_H
#define _HUFFMANCODER_H

#include <map>
#include <memory>
#include "coder.h"

class HuffmanNode {
	public:
		HuffmanNode(char, unsigned, std::shared_ptr<HuffmanNode>,
				std::shared_ptr<HuffmanNode>);
		char value;
		unsigned weight;
		std::shared_ptr<HuffmanNode> left, right;
};

class HuffmanCoder: public Coder {
	public:
		HuffmanCoder(const std::map<char, unsigned>&);
		virtual ~HuffmanCoder();
		virtual std::string Encode(char);
		virtual char Decode(std::string);
	private:
		HuffmanNode buildTree();
		HuffmanNode huffmanRoot;
		void BuildTree();
		std::map<char, unsigned> valueWeight;
		std::map<char, std::string> mapTable;
};

#endif // _HUFFMANCODER_H
