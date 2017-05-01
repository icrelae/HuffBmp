#ifndef _HUFFMANCODER_H
#define _HUFFMANCODER_H

#include <map>
#include <memory>
#include <utility>
#include <algorithm>
#include <list>
#include "coder.h"
#include "BinaryTree.h"

class HuffmanCoder: public Coder {
	public:
		HuffmanCoder(const std::map<char, unsigned>&);
		virtual ~HuffmanCoder();
		virtual std::string Encode(std::string) const override;
		virtual std::string Decode(std::string) const override;
		using Pair_CU = std::pair<char, unsigned>;
		using HuffTreeNode = BinaryTreeNode<Pair_CU>;
		using HuffTreeNodePtr = std::shared_ptr<HuffTreeNode>;
	private:
		std::map<char, unsigned> valueWeight;
		std::map<char, std::string> mapTable;
		HuffTreeNodePtr huffmanRoot;
		HuffTreeNodePtr BuildTree();
		static bool SortByWeight(
				const HuffTreeNodePtr&, const HuffTreeNodePtr&);
		static HuffTreeNodePtr Combine2Node(
				const HuffTreeNodePtr&, const HuffTreeNodePtr&);
};

#endif // _HUFFMANCODER_H
