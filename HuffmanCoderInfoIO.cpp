#include <bitset>
#include <algorithm>
#include "HuffmanCoderInfoIO.h"

HuffmanCoderInfoIO::HuffmanCoderInfoIO(size_t leafNmb):
	leafNodeNmb(leafNmb), treeNodeNmb(2*leafNmb - 1)
	// n2 + n0 = n; 2 * n2 + 1 = n; n2 + 1 = n0;
{
}

HuffmanCoderInfoIO::~HuffmanCoderInfoIO()
{
}

std::istream& HuffmanCoderInfoIO::ReadInfo(std::istream &is)
{
	is.read((char*)&leafNodeNmb, sizeof(leafNodeNmb));
	treeNodeNmb = 2 * leafNodeNmb - 1;
	size_t treeStructBufSize = (treeNodeNmb + 7) / 8, i = 0;
	char *buffer = new char[leafNodeNmb + treeStructBufSize];
	char *leafDataBuff = buffer, *treeStructBuff = buffer + leafNodeNmb;
	is.read((char*)buffer, leafNodeNmb + treeStructBufSize);
	leafNodesData.clear();
	treeStruct.clear();
	while (i < treeStructBufSize) {
		treeStruct += std::bitset<8>(treeStructBuff[i]).to_string();
		leafNodesData.push_back({leafDataBuff[i++], 0});
	}
	while (i < leafNodeNmb)
		leafNodesData.push_back({leafDataBuff[i++], 0});
	delete []buffer;
	treeStruct.erase(treeNodeNmb);
	return is;
}

std::ostream& HuffmanCoderInfoIO::WriteInfo(std::ostream &os)
{
	os.write((char*)&leafNodeNmb, sizeof(leafNodeNmb));
	size_t treeStructBufSize = (treeNodeNmb + 7) / 8, i = 0;
	char *buffer = new char[leafNodeNmb + treeStructBufSize];
	char *leafDataBuff = buffer, *treeStructBuff = buffer + leafNodeNmb;
	while (i < treeStructBufSize - 1) {
		leafDataBuff[i] = leafNodesData[i].first;
		std::bitset<8> byte(treeStruct, i*8, i*8+8);
		treeStructBuff[i++] = byte.to_ulong();
	}
	while (i < leafNodeNmb)
		leafDataBuff[i] = leafNodesData[i].first;
	std::bitset<8> byteExtra();
	// TODO: deal with extra bits of treestruct
	os.write((char*)buffer, leafNodeNmb + treeStructBufSize);
	delete []buffer;
	return os;
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
