#ifndef _BINARYTREE_H
#define _BINARYTREE_H

#include <memory>
#include <vector>
#include <list>
#include <utility>

// BinaryTreeNode
template <typename DT>
class BinaryTreeNode
{
	public:
		using NodePtr = std::shared_ptr<BinaryTreeNode<DT>>;

		BinaryTreeNode(const DT&, const NodePtr &l = nullptr, const NodePtr &r = nullptr);

		DT data;
		NodePtr lchild;
		NodePtr rchild;
};

template <typename DT>
BinaryTreeNode<DT>::BinaryTreeNode(const DT &d, const NodePtr &l, const NodePtr &r)
	: data(d), lchild(l), rchild(r)
{
}

// BinaryTree
template <typename DT>
class BinaryTree
{
	public:
		BinaryTree(const typename BinaryTreeNode<DT>::NodePtr &p = nullptr);

		const typename BinaryTreeNode<DT>::NodePtr GetRoot() const;
		void SetRoot(typename BinaryTreeNode<DT>::NodePtr&);
		std::string GetTreeStruct() const;
		typename BinaryTreeNode<DT>::NodePtr SetTreeStruct(
				const std::string&,
				const std::vector<DT>&);
	private:
		typename BinaryTreeNode<DT>::NodePtr root;
		static const char CODE_CHLDNULL = '0';
		static const char CODE_CHLDEXIST = '1';

		std::string GetTreeStructPreOrder() const;
		typename BinaryTreeNode<DT>::NodePtr SetTreeStructPreOrder(
				const std::string&,
				const std::vector<DT>&);
};

template <typename DT>
BinaryTree<DT>::BinaryTree(const typename BinaryTreeNode<DT>::NodePtr &p)
	: root(p)
{
}

template <typename DT>
std::string BinaryTree<DT>::GetTreeStruct() const
{
	return root == nullptr ? "" : GetTreeStructPreOrder();
}

template <typename DT>
void BinaryTree<DT>::SetRoot(typename BinaryTreeNode<DT>::NodePtr &nodePtr)
{
	root = nodePtr;
}

template <typename DT>
std::string BinaryTree<DT>::GetTreeStructPreOrder() const
{
	std::string treeStruct = "";
	std::list<std::pair<decltype(root), unsigned char>> nodeStack{{root, 0}};
	typename decltype(nodeStack)::reverse_iterator nodeStackIt;
	while (!nodeStack.empty()) {
		nodeStackIt = nodeStack.rbegin();
		switch (nodeStackIt->second) {
			case 0:
				++nodeStackIt->second;
				if (nullptr != nodeStackIt->first.lchild) {
					nodeStack.push_back({nodeStackIt->first.lchild, 0});
					treeStruct += CODE_CHLDEXIST;
				} else
					treeStruct += CODE_CHLDNULL;
				break;
			case 1:
				++nodeStackIt->second;
				if (nullptr != nodeStackIt->first.rchild) {
					nodeStack.push_back({nodeStackIt->first.rchild, 0});
					treeStruct += CODE_CHLDEXIST;
				} else
					treeStruct += CODE_CHLDNULL;
				break;
			case 2:
				nodeStack.pop_back();
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
	return SetTreeStructPreOrder(treeStruct, vecData);
}

template <typename DT>
typename BinaryTreeNode<DT>::NodePtr BinaryTree<DT>::SetTreeStructPreOrder(
				const std::string &treeStruct,
				const std::vector<DT> &vecData)
{
	DT rootData;
	std::string::size_type indexStr = 0;
	typename std::vector<DT>::size_type indexVec = 0;
	root = std::make_shared<BinaryTreeNode<DT>>(rootData);
	std::list<std::pair<decltype(root), unsigned char>> nodeStack{{root, 0}};
	typename decltype(nodeStack)::reverse_iterator nodeStackIt;
	while (!nodeStack.empty() && indexStr < treeStruct.size()) {
		nodeStackIt = nodeStack.rbegin();
		switch (nodeStackIt->second) {
			case 0:
				++nodeStackIt->second;
				if (CODE_CHLDEXIST == treeStruct[indexStr++]) {
					nodeStackIt->first->lchild =
						std::make_shared<BinaryTreeNode<DT>>(vecData[indexVec]);
					nodeStack.push_back({nodeStackIt->first->lchild, 0});
					++indexVec;
				} else
					nodeStackIt->first->lchild = nullptr;
				break;
			case 1:
				++nodeStackIt->second;
				if (CODE_CHLDEXIST == treeStruct[indexStr++]) {
					nodeStackIt->first->rchild =
						std::make_shared<BinaryTreeNode<DT>>(vecData[indexVec]);
					nodeStack.push_back({nodeStackIt->first->rchild, 0});
					++indexVec;
				} else
					nodeStackIt->first->rchild = nullptr;
				break;
			case 2:
				nodeStack.pop_back();
				break;
		}
	}
	if (indexStr < treeStruct.size())
		root = nullptr;
	return root;
}

template <typename DT>
const typename BinaryTreeNode<DT>::NodePtr BinaryTree<DT>::GetRoot() const
{
	return root;
}

#endif // _BINARYTREE_H
