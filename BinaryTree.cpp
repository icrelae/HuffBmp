#include <iostream>
#include <list>
#include <utility>
#include "BinaryTree.h"

// BinaryTreeNode
template <typename DT>
BinaryTreeNode<DT>::BinaryTreeNode(
		DT d, const NodePtr &l, const NodePtr &r):
	data(d), lchild(l), rchild(r)
{
}

// BinaryTree
template <typename DT>
BinaryTree<DT>::BinaryTree(
		const typename BinaryTreeNode<DT>::NodePtr &p): root(p)
{
}

template <typename DT>
std::string BinaryTree<DT>::GetTreeStruct()
{
	return root == nullptr ? "" : TreeStructPreOrder();
}

template <typename DT>
std::string BinaryTree<DT>::TreeStructPreOrder()
{
	std::string treeStruct = "";
	std::list<std::pair<decltype(root), unsigned char>> nodeStack{{root, 0}};
	typename decltype(nodeStack)::iterator nodeStackIt;
	while (!nodeStack.empty()) {
		nodeStackIt = nodeStack.end() - 1;
		switch (nodeStackIt->second) {
			case 0:
				++nodeStackIt->second;
				if (nullptr != nodeStackIt->first.lchild) {
					nodeStack.push_back({nodeStackIt->first.lchild, 0});
					treeStruct += '1';
				} else
					treeStruct += '0';
				break;
			case 1:
				++nodeStackIt->second;
				if (nullptr != nodeStackIt->first.rchild) {
					nodeStack.push_back({nodeStackIt->first.rchild, 0});
					treeStruct += '1';
				} else
					treeStruct += '0';
				break;
			case 2:
				nodeStack.erase(nodeStackIt);
				break;
		}
	}
	return treeStruct;
}
