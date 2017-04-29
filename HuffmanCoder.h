#ifndef _HUFFMANCODER_H
#define _HUFFMANCODER_H

#include <map>
#include <memory>
#include "coder.h"
#include "BinaryTree.h"

class HuffmanCoder: public Coder {
	public:
		HuffmanCoder(const std::map<char, unsigned>&);
		virtual ~HuffmanCoder();
		virtual std::string Encode(std::string);
		virtual std::string Decode(std::string);
	private:
		std::shared_ptr<BinaryTreeNode<paire<char, unsigned>>> huffmanRoot;
		std::map<char, unsigned> valueWeight;
		std::map<char, std::string> mapTable;
		std::shared_ptr<BinaryTreeNode<paire<char, unsigned>>> BuildTree();
};

#endif // _HUFFMANCODER_H
