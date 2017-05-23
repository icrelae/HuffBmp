#ifndef _HUFFMANCODERINFOIO_H
#define _HUFFMANCODERINFOIO_H

#include <iostream>
#include "CoderInfoIO.h"
#include "HuffmanCoder.h"

class HuffmanCoderInfoIO: public CoderInfoIO {
public:
	HuffmanCoderInfoIO(const std::string &ts = "",
			const std::vector<HuffmanCoder::Pair_CU> &nodesData = std::vector<HuffmanCoder::Pair_CU>());
	virtual ~HuffmanCoderInfoIO();

	virtual std::istream& ReadInfo(std::istream&) override;
	virtual std::ostream& WriteInfo(std::ostream&) override;

	bool SetTreeInfo(const std::string&, const std::vector<HuffmanCoder::Pair_CU>&);
	std::string GetTreeStruct() const;
	std::vector<HuffmanCoder::Pair_CU> GetLeafNodeData() const;
private:
	size_t leafNodeNmb;
	size_t treeNodeNmb;
	std::string treeStruct;
	static const size_t blockSize = 64;
	std::vector<HuffmanCoder::Pair_CU> leafNodesData;

	bool SetTreeStruct(const std::string&);
	bool SetLeafNodeData(const std::vector<HuffmanCoder::Pair_CU>&);
	bool CheckTreeStruct(const std::string&) const;
	static std::istream& ReadData(std::istream&, char*, size_t);
};

#endif // _HUFFMANCODERINFOIO_H
