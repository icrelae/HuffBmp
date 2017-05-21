#ifndef _HUFFMANCODERINFOIO_H
#define _HUFFMANCODERINFOIO_H

#include <iostream>
#include "CoderInfoIO.h"
#include "HuffmanCoder.h"

class HuffmanCoderInfoIO: public CoderInfoIO {
public:
	std::string treeStruct;
	std::vector<HuffmanCoder::Pair_CU> leafNodesData;
	static const size_t blockSize = 64;

	HuffmanCoderInfoIO(size_t leafNmb = 0);
	virtual ~HuffmanCoderInfoIO();

	virtual std::istream& ReadInfo(std::istream&) override;
	virtual std::ostream& WriteInfo(std::ostream&) override;
	static std::istream& ReadData(std::istream&, char*, size_t);
private:
	size_t leafNodeNmb;
	size_t treeNodeNmb;
};

#endif // _HUFFMANCODERINFOIO_H
