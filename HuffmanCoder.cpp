#include <algorithm>
#include <list>
#include <bitset>
#include "HuffmanCoder.h"

HuffmanCoder::HuffmanCoder(const std::map<char, unsigned> &map)
	: valueWeight(map)
{
	HuffTreeNodePtr root = BuildTree();
	huffTree.SetRoot(root);
	BuildMapTable(huffTree.GetRoot());
}

HuffmanCoder::HuffmanCoder(
		const std::string &treeStruct, const std::vector<Pair_CU> &leafData)
{
	huffTree.SetTreeStruct(treeStruct, leafData);
	BuildMapTable(huffTree.GetRoot());
}

HuffmanCoder::~HuffmanCoder()
{
}

bool HuffmanCoder::SortByWeightAsc(const HuffTreeNodePtr &lhs,
		const HuffTreeNodePtr &rhs)
{
	return lhs->data.second < rhs->data.second;
}

HuffmanCoder::HuffTreeNodePtr HuffmanCoder::BuildTree() const
{
	std::list<HuffmanCoder::HuffTreeNodePtr> lstNodePtr;
	// cast 'pair<char, unsigned>' into 'HuffTreeNode'
	for (auto const &pairValWei : valueWeight) {
		lstNodePtr.push_back(std::make_shared<HuffTreeNode>(pairValWei));
	}
	lstNodePtr.sort(SortByWeightAsc);
	HuffTreeNodePtr newNode;
	decltype(lstNodePtr)::const_iterator lstIt1, lstIt2;
	while (1 < lstNodePtr.size()) {
		// merge first two node in 'newNode' as lchild and rchild
		lstIt1 = lstIt2 = lstNodePtr.begin();
		++lstIt2;
		newNode = Combine2Node(*lstIt1, *lstIt2);
		// delete first two node in list
		lstNodePtr.erase(lstNodePtr.begin());
		lstNodePtr.erase(lstNodePtr.begin());
		// find place in list to insert 'newNode'
		lstIt1 = find_if(lstNodePtr.begin(), lstNodePtr.end(),
				[newNode] (const HuffTreeNodePtr &p) {
					return p->data.second > newNode->data.second;
				});
		lstNodePtr.insert(lstIt1, newNode);
	}
	return *lstNodePtr.begin();
}

HuffmanCoder::HuffTreeNodePtr HuffmanCoder::Combine2Node(
		const HuffmanCoder::HuffTreeNodePtr &lnode,
		const HuffmanCoder::HuffTreeNodePtr &rnode)
{
	return std::make_shared<HuffTreeNode>(
			Pair_CU({' ', lnode->data.second + rnode->data.second}),
			lnode, rnode);
}

std::map<char, std::string>::size_type HuffmanCoder::BuildMapTable(const HuffTreeNodePtr &root)
{
	std::string codeStr = "";

	std::list<std::pair<decltype(root), unsigned char>> nodeStack{{root, 0}};
	typename decltype(nodeStack)::reverse_iterator nodeStackIt;
	while (!nodeStack.empty()) {
		nodeStackIt = nodeStack.rbegin();
		switch (nodeStackIt->second) {
		case 0:
			++nodeStackIt->second;
			if (nullptr != nodeStackIt->first->lchild) {
				nodeStack.push_back({nodeStackIt->first->lchild, 0});
				codeStr += CODE_LCHILD;
			}
			break;
		case 1:
			++nodeStackIt->second;
			if (nullptr != nodeStackIt->first->rchild) {
				nodeStack.push_back({nodeStackIt->first->rchild, 0});
				codeStr += CODE_RCHILD;
			}
			break;
		case 2:
			if (nodeStackIt->first->lchild == nullptr &&
					nodeStackIt->first->rchild==nullptr) {
				char c = nodeStackIt->first->data.first;
				mapTable[c] = codeStr;
			}
			nodeStack.pop_back();
			codeStr.pop_back();
			break;
		}
	}
	return mapTable.size();
}

std::string HuffmanCoder::Encode(std::string &originCode)
{
	std::string result = "";

	while (originCode.size() > 7) {
		// bit code to 'char'
		std::bitset<8> oneByte =
			std::bitset<8>(originCode, 0, 8, CODE_LCHILD, CODE_RCHILD);
		const char key = static_cast<char>(oneByte.to_ulong());
		//result += mapTable[c];	// invalid, if map[k] non-exist it will be inserted,
						// but current func is 'const'
		decltype(mapTable)::const_iterator itMapTable = mapTable.find(key);
		if (itMapTable == mapTable.end())
			throw std::out_of_range("no value for key: " + key);
		result += itMapTable->second;
		originCode.erase(0, 8);
	}
	return result;
}

std::string HuffmanCoder::Decode(std::string &originStr)
{
	std::string result = "";

	const HuffTreeNodePtr root = huffTree.GetRoot();
	const HuffTreeNodePtr *nodePtr = &root;
	std::string::const_iterator itOriginStr = originStr.begin();
	std::string::const_iterator itLastCodeEnd = itOriginStr;
	while(itOriginStr != originStr.end()) {
		if ((*nodePtr)->lchild == nullptr && (*nodePtr)->rchild == nullptr) {
			// leaf of huffmanTree, get data and reset 'nodePtr'
			result += (*nodePtr)->data.first;
			nodePtr = &root;
			// record last end of completed code
			itLastCodeEnd = itOriginStr;
			continue;
		}
		switch (*itOriginStr) {
		case CODE_LCHILD:
			nodePtr = &(*nodePtr)->lchild;
			break;
		case CODE_RCHILD:
			nodePtr = &(*nodePtr)->rchild;
			break;
		default:
			throw std::out_of_range("unknown code: " + *itOriginStr);
		}
		++itOriginStr;
	}
	// return the rest of originStr
	originStr = originStr.substr(itLastCodeEnd - originStr.begin());
	return result;
}

std::string HuffmanCoder::GetHuffTreeStruct() const
{
	return huffTree.GetTreeStruct();
}

std::vector<HuffmanCoder::Pair_CU> HuffmanCoder::GetHuffTreeLeafData() const
{
	return huffTree.GetLeafData();
}
