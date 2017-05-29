#ifndef _BINARYTREE_H
#define _BINARYTREE_H

#include <memory>
#include <vector>
#include <list>
#include <utility>
#include <functional>

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
	std::vector<DT> GetLeafData() const;
private:
	typename BinaryTreeNode<DT>::NodePtr root;
	static const char CODE_CHLDNULL = '0';
	static const char CODE_CHLDEXIST = '1';

	std::string GetTreeStructPreOrder() const;
	typename BinaryTreeNode<DT>::NodePtr SetTreeStructPreOrder(
			const std::string&,
			const std::vector<DT>&);
	std::vector<DT> GetNodeDataPreOrder(
			std::function
			<bool(const typename BinaryTreeNode<DT>::NodePtr&)>) const;
	static bool IsLeaf(const typename BinaryTreeNode<DT>::NodePtr&);
};

template <typename DT>
BinaryTree<DT>::BinaryTree(const typename BinaryTreeNode<DT>::NodePtr &p)
	: root(p)
{
}

template <typename DT>
const typename BinaryTreeNode<DT>::NodePtr BinaryTree<DT>::GetRoot() const
{
	return root;
}

template <typename DT>
void BinaryTree<DT>::SetRoot(typename BinaryTreeNode<DT>::NodePtr &nodePtr)
{
	root = nodePtr;
}

template <typename DT>
std::string BinaryTree<DT>::GetTreeStruct() const
{
	return (root == nullptr) ? "" : GetTreeStructPreOrder();
}

template <typename DT>
typename BinaryTreeNode<DT>::NodePtr BinaryTree<DT>::SetTreeStruct(
		const std::string& treeStruct,
		const std::vector<DT> &vecData)
{
	return SetTreeStructPreOrder(treeStruct, vecData);
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
			treeStruct += (nullptr == nodeStackIt->first->lchild) ?
				CODE_CHLDNULL : CODE_CHLDEXIST;
			nodeStack.push_back({nodeStackIt->first->lchild, 0});
			break;
		case 1:
			++nodeStackIt->second;
			treeStruct += (nullptr == nodeStackIt->first->rchild) ?
				CODE_CHLDNULL : CODE_CHLDEXIST;
			nodeStack.push_back({nodeStackIt->first->rchild, 0});
			break;
		case 2:
			nodeStack.pop_back();
			break;
		}
		if (nullptr == (nodeStack.rbegin()->first))
			nodeStack.pop_back();
	}
	return treeStruct;
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
	while (indexStr < treeStruct.size() && indexVec < vecData.size()
			&& !nodeStack.empty()) {
		nodeStackIt = nodeStack.rbegin();
		switch (nodeStackIt->second) {
		case 0:
			++nodeStackIt->second;
			nodeStackIt->first->lchild =
				(CODE_CHLDNULL == treeStruct[indexStr++]) ?
				nullptr :
				std::make_shared<BinaryTreeNode<DT>>(vecData[indexVec++]);
			nodeStack.push_back({nodeStackIt->first->lchild, 0});
			break;
		case 1:
			++nodeStackIt->second;
			nodeStackIt->first->rchild =
				(CODE_CHLDNULL == treeStruct[indexStr++]) ?
				nullptr :
				std::make_shared<BinaryTreeNode<DT>>(vecData[indexVec++]);
			nodeStack.push_back({nodeStackIt->first->rchild, 0});
			break;
		case 2:
			nodeStack.pop_back();
			break;
		}
		if (nullptr == (nodeStack.rbegin()->first))
			nodeStack.pop_back();
	}
	if (indexStr < treeStruct.size() || indexVec < vecData.size())
		root = nullptr;
	return root;
}

template <typename DT>
std::vector<DT> BinaryTree<DT>::GetLeafData() const
{
	return GetNodeDataPreOrder(IsLeaf);
}

template <typename DT>
std::vector<DT> BinaryTree<DT>::GetNodeDataPreOrder(
		std::function
		<bool(const typename BinaryTreeNode<DT>::NodePtr&)> pred) const
{
	std::vector<DT> vecData;
	std::list<std::pair<decltype(root), unsigned char>> nodeStack{{root, 0}};
	typename decltype(nodeStack)::reverse_iterator nodeStackIt;
	while (!nodeStack.empty()) {
		nodeStackIt = nodeStack.rbegin();
		switch (nodeStackIt->second) {
		case 0:
			++nodeStackIt->second;
			nodeStack.push_back({nodeStackIt->first->lchild, 0});
			break;
		case 1:
			++nodeStackIt->second;
			nodeStack.push_back({nodeStackIt->first->rchild, 0});
			break;
		case 2:
			if (pred(nodeStackIt->first))
				vecData.push_back(nodeStackIt->first->data);
			nodeStack.pop_back();
			break;
		}
		if (nullptr == (nodeStack.rbegin()->first))
			nodeStack.pop_back();
	}
	return vecData;
}

template <typename DT>
bool BinaryTree<DT>::IsLeaf(const typename BinaryTreeNode<DT>::NodePtr &node)
{
	return (node->lchild == nullptr && node->rchild == nullptr);
}

#endif // _BINARYTREE_H
