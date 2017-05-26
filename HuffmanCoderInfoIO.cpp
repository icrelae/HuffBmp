#include <bitset>
#include <algorithm>
#include "HuffmanCoderInfoIO.h"

HuffmanCoderInfoIO::HuffmanCoderInfoIO(const std::string &ts,
			const std::vector<HuffmanCoder::Pair_CU> &nodesData)
{
	SetTreeInfo(ts, nodesData);
}

HuffmanCoderInfoIO::~HuffmanCoderInfoIO()
{
}

std::istream& HuffmanCoderInfoIO::ReadInfo(std::istream &is)
{
	is.read((char*)&leafNodeNmb, sizeof(leafNodeNmb));
	treeNodeNmb = 2 * leafNodeNmb - 1;
	size_t treeStructBufSize = (treeNodeNmb + 7) / 8, i = 0;
	std::shared_ptr<char> bufferSptr(new char[leafNodeNmb + treeStructBufSize]);
	char *buffer = bufferSptr.get();
	char *leafDataBuff = buffer, *treeStructBuff = buffer + leafNodeNmb;
	is.read(buffer, leafNodeNmb + treeStructBufSize);
	leafNodesData.clear();
	treeStruct.clear();
	while (i < treeStructBufSize) {
		treeStruct += std::bitset<8>(treeStructBuff[i]).to_string();
		leafNodesData.push_back({leafDataBuff[i++], 0});
	}
	while (i < leafNodeNmb)
		leafNodesData.push_back({leafDataBuff[i++], 0});
	treeStruct.erase(treeNodeNmb);
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
	return StatisticKeyWeight(is);
}

std::istream& HuffmanCoderInfoIO::ReadData(std::istream &is, char *buff, size_t len)
{
	while (is && len >= blockSize) {
		is.read(buff, blockSize);
		buff += blockSize;
		len -= blockSize;
	}
	if (is && len > 0) {
		is.read(buff, len);
		len -= is.gcount();
	}
	if (!is)
		throw std::out_of_range("istream error");
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
	if (nodesData.size() == leafNodeNmb)
		leafNodesData = nodesData;
	else
		setOk = false;
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
	if (SetTreeStruct(ts) && SetLeafNodeData(nodesData))
		setOk = true;
	else
		*this = copyInfo;
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
	return is;
}

std::map<char, unsigned> HuffmanCoderInfoIO::GetKeyWeight() const
{
	return keyWeight;
}
