#ifndef _HUFFMANCODERINFOIO_H
#define _HUFFMANCODERINFOIO_H

#include "CoderInfoIO.h"
#include "HuffmanCoder.h"

class HuffmanCoderInfoIO: public CoderInfoIO {
public:
	HuffmanCoderInfoIO();
	HuffmanCoderInfoIO(const HuffmanCoderInfoIO&);
	HuffmanCoderInfoIO(HuffmanCoderInfoIO&&);
	HuffmanCoderInfoIO(const std::string&, const std::vector<HuffmanCoder::Pair_CU>&);
	virtual ~HuffmanCoderInfoIO();

	virtual std::istream& ReadInfo(std::istream&) override;
	virtual std::ostream& WriteInfo(std::ostream&) override;
	virtual enum PreprcsRslt Preprocess(std::istream&) override;
	virtual enum PreprcsRslt Preprocess(std::istream&, std::iostream&) override;
	virtual std::istream& Read(std::istream&, char*, size_t) override;
	virtual std::ostream& Write(std::ostream&, char*, size_t) override;
	virtual size_t Gcount() const override;
	virtual size_t GetFileSize() const override;
	virtual const Coder* GetCoder() const override;

	HuffmanCoderInfoIO& operator=(const HuffmanCoderInfoIO&);
	HuffmanCoderInfoIO& operator=(HuffmanCoderInfoIO&&);

	bool SetTreeInfo(const std::string&, const std::vector<HuffmanCoder::Pair_CU>&);
	std::string GetTreeStruct() const;
	std::vector<HuffmanCoder::Pair_CU> GetLeafNodeData() const;
	std::map<char, unsigned> GetKeyWeight() const;
private:
	size_t leafNodeNmb;
	size_t treeNodeNmb;
	size_t gcount;
	size_t fileSize;
	std::string treeStruct;
	static const size_t blockSize = 64;
	std::vector<HuffmanCoder::Pair_CU> leafNodesData;
	std::map<char, unsigned> keyWeight;
	HuffmanCoder *coderPtr;
	static std::allocator<HuffmanCoder> alctHuffmanCoder;

	bool SetTreeStruct(const std::string&);
	bool SetLeafNodeData(const std::vector<HuffmanCoder::Pair_CU>&);
	bool CheckTreeStruct(const std::string&) const;
	std::istream& StatisticKeyWeight(std::istream&);
};

#endif // _HUFFMANCODERINFOIO_H
