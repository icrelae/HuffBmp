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
	return root == nullptr ? "" : GetTreeStructPreOrder();
}

template <typename DT>
std::string BinaryTree<DT>::GetTreeStructPreOrder()
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

template <typename DT>
typename BinaryTreeNode<DT>::NodePtr BinaryTree<DT>::SetTreeStruct(
		const std::string& treeStruct,
		const std::vector<DT> &vecData)
{
	return SetTreeStructPreOrder(treeStruct);
}

template <typename DT>
typename BinaryTreeNode<DT>::NodePtr BinaryTree<DT>::SetTreeStructPreOrder(
				const std::string &treeStruct,
				const std::vector<DT> &vecData)
{
	std::string::size_type indexStr = 0;
	typename std::vector<DT>::size_type indexVec = 0;
	root = std::make_shared<BinaryTreeNode<DT>>({' ', 0});
	std::list<std::pair<decltype(root), unsigned char>> nodeStack{{root, 0}};
	typename decltype(nodeStack)::iterator nodeStackIt;
	while (!nodeStack.empty() && indexStr < treeStruct.size()) {
		nodeStackIt = nodeStack.end() - 1;
		switch (nodeStackIt->second) {
			case 0:
				++nodeStackIt->second;
				if ('1' == treeStruct[indexStr++]) {
					nodeStackIt->first.lchild =
						std::make_shared<decltype(root)>(vecData[indexVec]);
					nodeStack.push_back({nodeStackIt->first.lchild, 0});
					++indexVec;
				}
				break;
			case 1:
				++nodeStackIt->second;
				if ('1' == treeStruct[indexStr++]) {
					nodeStackIt->first.rchild =
						std::make_shared<decltype(root)>(vecData[indexVec]);
					nodeStack.push_back({nodeStackIt->first.rchild, 0});
					++indexVec;
				}
				break;
			case 2:
				nodeStack.erase(nodeStackIt);
				break;
		}
	}
	if (indexStr < treeStruct.size())
		root = nullptr;
	return root;
}
