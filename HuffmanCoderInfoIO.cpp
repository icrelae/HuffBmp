#include <bitset>
#include <algorithm>
#include "HuffmanCoderInfoIO.h"

// static member need not only declaration with 'static' but also definition
// without 'static'
std::allocator<HuffmanCoder> HuffmanCoderInfoIO::alctHuffmanCoder;

HuffmanCoderInfoIO::HuffmanCoderInfoIO(): coderPtr(nullptr)
{
}

HuffmanCoderInfoIO::HuffmanCoderInfoIO(const std::string &ts,
			const std::vector<HuffmanCoder::Pair_CU> &nodesData)
	: coderPtr(nullptr)
{
	SetTreeInfo(ts, nodesData);
}

HuffmanCoderInfoIO::~HuffmanCoderInfoIO()
{
	if (coderPtr)
		alctHuffmanCoder.deallocate(coderPtr, 1);
	coderPtr = nullptr;
}

std::istream& HuffmanCoderInfoIO::ReadInfo(std::istream &is)
{
	size_t leafNodeNmb, treeNodeNmb, treeStructBufSize, i = 0;
	is.read((char*)&leafNodeNmb, sizeof(leafNodeNmb));
	treeNodeNmb = 2 * leafNodeNmb - 1;
	treeStructBufSize = (treeNodeNmb + 7) / 8;
	std::shared_ptr<char> bufferSptr(new char[leafNodeNmb + treeStructBufSize]);
	char *buffer = bufferSptr.get();
	is.read(buffer, leafNodeNmb + treeStructBufSize);
	if (is.gcount() < static_cast<std::streamsize>(leafNodeNmb + treeStructBufSize))
		return is;
	std::vector<HuffmanCoder::Pair_CU> leafNodesData;
	std::string treeStruct;
	char *leafDataBuff = buffer, *treeStructBuff = buffer + leafNodeNmb;
	while (i < treeStructBufSize) {
		treeStruct += std::bitset<8>(treeStructBuff[i]).to_string();
		leafNodesData.push_back({leafDataBuff[i++], 0});
	}
	while (i < leafNodeNmb)
		leafNodesData.push_back({leafDataBuff[i++], 0});
	treeStruct.erase(treeNodeNmb);
	SetTreeInfo(treeStruct, leafNodesData);
	return is;
}

std::ostream& HuffmanCoderInfoIO::WriteInfo(std::ostream &os)
{
	/* append '0' to fill up 8 bit */
	size_t extra0Len = 8 - treeStruct.size() % 8;
	std::string treeStructStr = treeStruct + std::string(extra0Len, '0');
	size_t treeStructBufSize = (treeNodeNmb + 7) / 8, i = 0;
	std::shared_ptr<char> bufferSptr(new char[leafNodeNmb + treeStructBufSize]);
	char *buffer = bufferSptr.get();
	char *leafDataBuff = buffer, *treeStructBuff = buffer + leafNodeNmb;
	while (i < treeStructBufSize) {
		std::bitset<8> byte(treeStructStr, i*8, i*8+8);
		*treeStructBuff++ = byte.to_ulong();
		*leafDataBuff++ = leafNodesData[i++].first;
	}
	while (i < leafNodeNmb)
		*leafDataBuff++ = leafNodesData[i++].first;
	os.write((char*)&leafNodeNmb, sizeof(leafNodeNmb));
	os.write(buffer, leafNodeNmb + treeStructBufSize);
	return os;
}

std::istream& HuffmanCoderInfoIO::Preprocess(std::istream &is)
{
	StatisticKeyWeight(is);
	treeNodeNmb = treeStruct.size() / 2;
	leafNodeNmb = leafNodesData.size();
	return is;
}

// binaryTreeStruct: 00 11 11 00 ... -> huffmanTreeStruct: 0 1 1 0
bool HuffmanCoderInfoIO::SetTreeStruct(const std::string &ts)
{
	bool setOk = false;
	if (CheckTreeStruct(ts)) {
		leafNodeNmb = ts.size() / 2;
		treeNodeNmb = 2 * leafNodeNmb - 1;
		// n2 + n0 = n; 2 * n2 + 1 = n; n2 + 1 = n0;
		treeStruct.clear();
		for (size_t i = 0; i < leafNodeNmb; ++i)
			treeStruct += ts[i * 2];
		setOk = true;
	}
	return setOk;
}

std::string HuffmanCoderInfoIO::GetTreeStruct() const
{
	return treeStruct;
}

bool HuffmanCoderInfoIO::SetLeafNodeData(
		const std::vector<HuffmanCoder::Pair_CU> &nodesData)
{
	bool setOk = true;
	if (nodesData.size() == leafNodeNmb) {
		leafNodesData = nodesData;
	} else {
		setOk = false;
		leafNodesData.clear();
		treeStruct.clear();
		alctHuffmanCoder.destroy(coderPtr);
		alctHuffmanCoder.deallocate(coderPtr, 1);
		coderPtr = nullptr;
	}
	return setOk;
}

std::vector<HuffmanCoder::Pair_CU> HuffmanCoderInfoIO::GetLeafNodeData() const
{
	return leafNodesData;
}

bool HuffmanCoderInfoIO::CheckTreeStruct(const std::string &ts) const
{
	bool tsOk = true;
	if (1 == ts.size() % 2)
		tsOk = false;
	for (size_t i = 0; tsOk && i < ts.size(); i += 2)
		if (ts[i] != ts[i+1])
			tsOk = false;
	return tsOk;
}

bool HuffmanCoderInfoIO::SetTreeInfo(const std::string &ts,
		const std::vector<HuffmanCoder::Pair_CU> &nodesData)
{
	bool setOk = false;
	HuffmanCoderInfoIO copyInfo = *this;
	if (SetTreeStruct(ts) && SetLeafNodeData(nodesData)) {
		setOk = true;
		if (nullptr == coderPtr) {
			coderPtr = alctHuffmanCoder.allocate(1);
			alctHuffmanCoder.construct(coderPtr, treeStruct, leafNodesData);
		} else {
			coderPtr->SetHuffTreeStruct(treeStruct, leafNodesData);
		}
	} else {
		*this = copyInfo;
	}
	return setOk;
}

std::istream& HuffmanCoderInfoIO::StatisticKeyWeight(std::istream &is)
{
	std::shared_ptr<char> bufferSptr(new char[blockSize]);
	char *buffer = bufferSptr.get();
	size_t gcount = blockSize;
	keyWeight.clear();
	while (gcount == blockSize) {
		is.read(buffer, blockSize);
		gcount = is.gcount();
		for (size_t i = 0; i < gcount; ++i)
			++keyWeight[buffer[i]];
	}
	if (nullptr == coderPtr) {
		coderPtr = alctHuffmanCoder.allocate(1);
		alctHuffmanCoder.construct(coderPtr, keyWeight);
	} else {
		coderPtr->SetKeyWeight(keyWeight);
	}
	treeStruct = coderPtr->GetHuffTreeStruct();
	leafNodesData = coderPtr->GetHuffTreeLeafData();
	return is;
}

std::map<char, unsigned> HuffmanCoderInfoIO::GetKeyWeight() const
{
	return keyWeight;
}

const Coder* HuffmanCoderInfoIO::GetCoder() const
{
	return coderPtr;
}
