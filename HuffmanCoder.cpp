#include "HuffmanCoder.h"

HuffmanCoder::HuffmanCoder(const std::map<char, unsigned> &map):
	valueWeight(map),
	huffmanRoot(std::make_shared<HuffTreeNode>(Pair_CU({' ', 0})))
{
}

bool HuffmanCoder::SortByWeight(const HuffTreeNodePtr &lhs,
		const HuffTreeNodePtr &rhs)
{
	return lhs->data.second < rhs->data.second;
}

HuffmanCoder::HuffTreeNodePtr HuffmanCoder::BuildTree()
{
	std::list<HuffmanCoder::HuffTreeNodePtr> lstNodePtr;
	// cast 'pair<char, unsigned>' into 'HuffTreeNode'
	for (auto const &pairValWei : valueWeight) {
		lstNodePtr.push_back(std::make_shared<HuffTreeNode>(pairValWei));
	}
	lstNodePtr.sort(SortByWeight);
	decltype(lstNodePtr)::const_iterator lstIt1, lstIt2;
	HuffTreeNodePtr newNode;
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
