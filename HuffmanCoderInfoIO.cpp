#include <bitset>
#include <algorithm>
#include <fstream>
#include "HuffmanCoderInfoIO.h"
#include "Common.h"

// static member need not only declaration with 'static' but also a definition
// without 'static'
std::allocator<HuffmanCoder> HuffmanCoderInfoIO::alctHuffmanCoder;

HuffmanCoderInfoIO::HuffmanCoderInfoIO(): coderPtr(nullptr)
{
}

HuffmanCoderInfoIO::HuffmanCoderInfoIO(const HuffmanCoderInfoIO &coderInfo)
	: leafNodeNmb(coderInfo.leafNodeNmb), treeNodeNmb(coderInfo.treeNodeNmb),
	treeStruct(coderInfo.treeStruct), leafNodesData(coderInfo.leafNodesData),
	keyWeight(coderInfo.keyWeight)
{
	coderPtr = alctHuffmanCoder.allocate(1);
	alctHuffmanCoder.construct(coderPtr, *coderInfo.coderPtr);
}

HuffmanCoderInfoIO::HuffmanCoderInfoIO(HuffmanCoderInfoIO &&coderInfo)
	: leafNodeNmb(std::move(coderInfo.leafNodeNmb)),
	treeNodeNmb(std::move(coderInfo.treeNodeNmb)),
	treeStruct(std::move(coderInfo.treeStruct)),
	leafNodesData(std::move(coderInfo.leafNodesData)),
	keyWeight(std::move(coderInfo.keyWeight))
{
	coderPtr = coderInfo.coderPtr;
	coderInfo.coderPtr = nullptr;
}

HuffmanCoderInfoIO::HuffmanCoderInfoIO(const std::string &ts,
		const std::vector<HuffmanCoder::Pair_CU> &nodesData)
	: coderPtr(nullptr)
{
	SetTreeInfo(ts, nodesData);
}

HuffmanCoderInfoIO::~HuffmanCoderInfoIO()
{
	if (coderPtr) {
		alctHuffmanCoder.destroy(coderPtr);
		alctHuffmanCoder.deallocate(coderPtr, 1);
	}
	coderPtr = nullptr;
}

HuffmanCoderInfoIO& HuffmanCoderInfoIO::operator=(const HuffmanCoderInfoIO &coderInfo)
{
	leafNodeNmb = coderInfo.leafNodeNmb;
	treeNodeNmb = coderInfo.treeNodeNmb;
	treeStruct = coderInfo.treeStruct;
	leafNodesData = coderInfo.leafNodesData;
	keyWeight = coderInfo.keyWeight;
	if (coderPtr)
		alctHuffmanCoder.destroy(coderPtr);
	else
		alctHuffmanCoder.allocate(1);
	alctHuffmanCoder.construct(coderPtr, *coderInfo.coderPtr);
	return *this;
}

HuffmanCoderInfoIO& HuffmanCoderInfoIO::operator=(HuffmanCoderInfoIO &&coderInfo)
{
	leafNodeNmb = std::move(coderInfo.leafNodeNmb);
	treeNodeNmb = std::move(coderInfo.treeNodeNmb);
	treeStruct = std::move(coderInfo.treeStruct);
	leafNodesData = std::move(coderInfo.leafNodesData);
	keyWeight = std::move(coderInfo.keyWeight);
	if (coderPtr) {
		alctHuffmanCoder.destroy(coderPtr);
		alctHuffmanCoder.deallocate(coderPtr, 1);
	}
	coderPtr = coderInfo.coderPtr;
	coderInfo.coderPtr = nullptr;
	return *this;
}

std::istream& HuffmanCoderInfoIO::ReadInfo(std::istream &is)
{
	size_t leafNodeNmb, treeNodeNmb, treeStructBufSize, i = 0;
	is.read(reinterpret_cast<char*>(&leafNodeNmb), sizeof(leafNodeNmb));
	treeNodeNmb = 2 * leafNodeNmb - 1;
	treeStructBufSize = (treeNodeNmb + 7) / 8;

	std::shared_ptr<char> bufferSptr(new char[leafNodeNmb + treeStructBufSize]);
	char *buffer = bufferSptr.get();
	is.read(buffer, leafNodeNmb + treeStructBufSize);
	if (is.gcount() < static_cast<std::streamsize>(leafNodeNmb + treeStructBufSize))
		return is;

	std::string treeStruct;
	std::vector<HuffmanCoder::Pair_CU> leafNodesData;
	char *leafDataBuff = buffer, *treeStructBuff = buffer + leafNodeNmb;
	while (i < treeStructBufSize) {
		treeStruct += std::bitset<8>(treeStructBuff[i]).to_string();
		leafNodesData.push_back({leafDataBuff[i++], 0});
	}
	while (i < leafNodeNmb)
		leafNodesData.push_back({leafDataBuff[i++], 0});
	treeStruct.erase(treeNodeNmb);

	// copy single bit into double bit to describe one tree node
	std::string::iterator itTreeStruct = treeStruct.begin();
	while (itTreeStruct < treeStruct.end()) {
		itTreeStruct = treeStruct.insert(itTreeStruct+1, *itTreeStruct);
		++itTreeStruct;
	}
	SetTreeInfo(treeStruct, leafNodesData);
	return is;
}

std::ostream& HuffmanCoderInfoIO::WriteInfo(std::ostream &os)
{
	// shrink double bit into single bit to describe one tree node
	std::string treeStructStr;
	for (size_t i = 0; i < treeStruct.size() / 2; ++i)
		treeStructStr += treeStruct[2 * i];

	/* append '0' to fill up 8 bit */
	size_t extra0Len = 8 - treeStructStr.size() % 8;
	treeStructStr += std::string(extra0Len, '0');

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

	os.write(reinterpret_cast<char*>(&leafNodeNmb), sizeof(leafNodeNmb));
	os.write(buffer, leafNodeNmb + treeStructBufSize);
	return os;
}

enum PreprcsRslt HuffmanCoderInfoIO::Preprocess(std::istream &is)
{
	is.read(reinterpret_cast<char*>(&fileSize), sizeof(fileSize));
	return RSLTOK;
}
enum PreprcsRslt HuffmanCoderInfoIO::Preprocess(std::istream &is, std::iostream &os)
{
	fileSize = CalcFileSize(is);
	os.write(reinterpret_cast<char*>(&fileSize), sizeof(fileSize));
	StatisticKeyWeight(is);
	return RSLTOK;
}

bool HuffmanCoderInfoIO::SetTreeStruct(const std::string &ts)
{
	bool setOk = false;
	if (CheckTreeStruct(ts)) {
		treeStruct = ts;
		treeNodeNmb = treeStruct.size() / 2;
		leafNodeNmb = (treeNodeNmb + 1) / 2;
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
		leafNodeNmb = treeNodeNmb = 0;
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
	size_t readCount = blockSize;
	keyWeight.clear();
	while (readCount == blockSize) {
		is.read(buffer, blockSize);
		readCount = is.gcount();
		for (size_t i = 0; i < readCount; ++i)
			++keyWeight[buffer[i]];
	}
	if (nullptr == coderPtr) {
		coderPtr = alctHuffmanCoder.allocate(1);
		alctHuffmanCoder.construct(coderPtr, keyWeight);
	} else {
		coderPtr->SetKeyWeight(keyWeight);
	}
	SetTreeStruct(coderPtr->GetHuffTreeStruct());
	SetLeafNodeData(coderPtr->GetHuffTreeLeafData());
	return is;
}

std::map<char, unsigned> HuffmanCoderInfoIO::GetKeyWeight() const
{
	return keyWeight;
}

std::istream& HuffmanCoderInfoIO::Read(std::istream &is, char *buf, size_t size)
{
	is.read(buf, size);
	gcount = is.gcount();
	return is;
}

std::ostream& HuffmanCoderInfoIO::Write(std::ostream &os, char *buf, size_t size)
{
	os.write(buf, size);
	return os;
}

size_t HuffmanCoderInfoIO::Gcount() const
{
	return gcount;
}

size_t HuffmanCoderInfoIO::GetFileSize() const
{
	return fileSize;
}

const Coder* HuffmanCoderInfoIO::GetCoder() const
{
	return coderPtr;
}
