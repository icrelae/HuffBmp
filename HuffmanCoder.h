#ifndef _HUFFMANCODER_H
#define _HUFFMANCODER_H

#include <map>
#include <memory>
#include <utility>
#include "Coder.h"
#include "BinaryTree.h"

class HuffmanCoder: public Coder {
public:
	using Pair_CU = std::pair<char, unsigned>;
	using HuffTreeNode = BinaryTreeNode<Pair_CU>;
	using HuffTreeNodePtr = std::shared_ptr<HuffTreeNode>;

	static const char CODE_LCHILD = '0';
	static const char CODE_RCHILD = '1';

	HuffmanCoder(const HuffmanCoder&);
	HuffmanCoder(HuffmanCoder&&);
	HuffmanCoder(const std::map<char, unsigned>&);
	HuffmanCoder(const std::string&, const std::vector<Pair_CU>&);
	virtual ~HuffmanCoder();

	virtual std::string Encode(std::string&) const override;
	virtual std::string Decode(std::string&) const override;

	HuffmanCoder& operator=(const HuffmanCoder&);
	HuffmanCoder& operator=(HuffmanCoder&&);

	void SetKeyWeight(const std::map<char, unsigned>&);
	void SetHuffTreeStruct(const std::string&, const std::vector<Pair_CU>&);
	std::string GetHuffTreeStruct() const;
	std::vector<Pair_CU> GetHuffTreeLeafData() const;
private:
	BinaryTree<Pair_CU> huffTree;
	std::map<char, unsigned> keyWeight;
	std::map<char, std::string> mapTable;

	HuffTreeNodePtr BuildTree() const;
	static bool SortByWeightAsc(
			const HuffTreeNodePtr&, const HuffTreeNodePtr&);
	static HuffTreeNodePtr Combine2Node(
			const HuffTreeNodePtr&, const HuffTreeNodePtr&);
	std::map<char, std::string>::size_type BuildMapTable(const HuffTreeNodePtr&);
};

#endif // _HUFFMANCODER_H
