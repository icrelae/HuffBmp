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

	BinaryTreeNode();
	BinaryTreeNode(const DT&, const NodePtr &l = nullptr, const NodePtr &r = nullptr);

	DT data;
	NodePtr lchild;
	NodePtr rchild;
};

template <typename DT>
BinaryTreeNode<DT>::BinaryTreeNode(): lchild(nullptr), rchild(nullptr)
{
}

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
	using Pred4TreeNodePtr = std::function
		<bool(const typename BinaryTreeNode<DT>::NodePtr&)>;
	BinaryTree(const typename BinaryTreeNode<DT>::NodePtr &p = nullptr);

	const typename BinaryTreeNode<DT>::NodePtr GetRoot() const;
	void SetRoot(typename BinaryTreeNode<DT>::NodePtr&);
	typename BinaryTreeNode<DT>::NodePtr SetTreeStruct(
			const std::string&, const std::vector<DT>&, Pred4TreeNodePtr);
	std::string GetTreeStruct() const;
	std::vector<DT> GetLeafData() const;
	static bool IsLeaf(const typename BinaryTreeNode<DT>::NodePtr&);
private:
	typename BinaryTreeNode<DT>::NodePtr root;
	static const char CODE_CHLDNULL = '0';
	static const char CODE_CHLDEXIST = '1';

	std::string GetTreeStructPreOrder() const;
	std::string GetTreeStructLvlOrder() const;
	typename BinaryTreeNode<DT>::NodePtr SetTreeStructPreOrder(
			const std::string&, const std::vector<DT>&, Pred4TreeNodePtr);
	typename BinaryTreeNode<DT>::NodePtr SetTreeStructLvlOrder(
			const std::string&, const std::vector<DT>&, Pred4TreeNodePtr);
	std::vector<DT> GetNodeDataPreOrder(Pred4TreeNodePtr) const;
	std::vector<DT> GetNodeDataLvlOrder(Pred4TreeNodePtr) const;
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
	return (root == nullptr) ? "" : GetTreeStructLvlOrder();
}

template <typename DT>
typename BinaryTreeNode<DT>::NodePtr BinaryTree<DT>::SetTreeStruct(
		const std::string& treeStruct,
		const std::vector<DT> &vecData,
		Pred4TreeNodePtr pred)
{
	return SetTreeStructLvlOrder(treeStruct, vecData, pred);
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
		if (nodeStack.size() > 0 && nullptr == (nodeStack.rbegin()->first))
			nodeStack.pop_back();
	}
	return treeStruct;
}

template <typename DT>
std::string BinaryTree<DT>::GetTreeStructLvlOrder() const
{
	std::string treeStruct = "";
	std::list<std::pair<decltype(root), unsigned char>> nodeStack{{root, 0}};
	typename decltype(nodeStack)::iterator nodeStackIt;
	while (!nodeStack.empty()) {
		nodeStackIt = nodeStack.begin();
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
			nodeStack.pop_front();
			break;
		}
		if (nodeStack.size() > 0 && nullptr == (nodeStack.rbegin()->first))
			nodeStack.pop_back();
	}
	return treeStruct;
}

template <typename DT>
typename BinaryTreeNode<DT>::NodePtr BinaryTree<DT>::SetTreeStructPreOrder(
		const std::string &treeStruct,
		const std::vector<DT> &vecData,
		Pred4TreeNodePtr pred)
{
	DT rootData;
	std::string::size_type indexStr = 0;
	typename std::vector<DT>::size_type indexVec = 0;
	root = std::make_shared<BinaryTreeNode<DT>>(rootData);
	std::list<std::pair<decltype(root), unsigned char>> nodeStack{{root, 0}};
	typename decltype(nodeStack)::reverse_iterator nodeStackIt;
	while (!nodeStack.empty()) {
		nodeStackIt = nodeStack.rbegin();
		switch (nodeStackIt->second) {
		case 0:
			++nodeStackIt->second;
			if (indexStr >= treeStruct.size())
				throw std::out_of_range("bad treeStruct");
			nodeStackIt->first->lchild =
				(CODE_CHLDNULL == treeStruct[indexStr++]) ?
				nullptr :
				std::make_shared<BinaryTreeNode<DT>>();
			nodeStack.push_back({nodeStackIt->first->lchild, 0});
			break;
		case 1:
			++nodeStackIt->second;
			if (indexStr >= treeStruct.size())
				throw std::out_of_range("bad treeStruct");
			nodeStackIt->first->rchild =
				(CODE_CHLDNULL == treeStruct[indexStr++]) ?
				nullptr :
				std::make_shared<BinaryTreeNode<DT>>();
			nodeStack.push_back({nodeStackIt->first->rchild, 0});
			break;
		case 2:
			if (pred(nodeStackIt->first)) {
				if (indexVec >= vecData.size())
					throw std::out_of_range("node data not enough");
				else
					nodeStackIt->first->data = vecData[indexVec++];
			}
			nodeStack.pop_back();
			break;
		}
		if (nodeStack.size() > 0 && nullptr == (nodeStack.rbegin()->first))
			nodeStack.pop_back();
	}
	if (indexStr < treeStruct.size() || indexVec < vecData.size())
		root = nullptr;
	return root;
}

template <typename DT>
typename BinaryTreeNode<DT>::NodePtr BinaryTree<DT>::SetTreeStructLvlOrder(
		const std::string &treeStruct,
		const std::vector<DT> &vecData,
		Pred4TreeNodePtr pred)
{
	DT rootData;
	std::string::size_type indexStr = 0;
	typename std::vector<DT>::size_type indexVec = 0;
	root = std::make_shared<BinaryTreeNode<DT>>(rootData);
	std::list<std::pair<decltype(root), unsigned char>> nodeStack{{root, 0}};
	typename decltype(nodeStack)::iterator nodeStackIt;
	while (!nodeStack.empty()) {
		nodeStackIt = nodeStack.begin();
		switch (nodeStackIt->second) {
		case 0:
			++nodeStackIt->second;
			if (indexStr >= treeStruct.size())
				throw std::out_of_range("bad treeStruct");
			nodeStackIt->first->lchild =
				(CODE_CHLDNULL == treeStruct[indexStr++]) ?
				nullptr :
				std::make_shared<BinaryTreeNode<DT>>();
			nodeStack.push_back({nodeStackIt->first->lchild, 0});
			break;
		case 1:
			++nodeStackIt->second;
			if (indexStr >= treeStruct.size())
				throw std::out_of_range("bad treeStruct");
			nodeStackIt->first->rchild =
				(CODE_CHLDNULL == treeStruct[indexStr++]) ?
				nullptr :
				std::make_shared<BinaryTreeNode<DT>>();
			nodeStack.push_back({nodeStackIt->first->rchild, 0});
			break;
		case 2:
			if (pred(nodeStackIt->first)) {
				if (indexVec >= vecData.size())
					throw std::out_of_range("node data not enough");
				else
					nodeStackIt->first->data = vecData[indexVec++];
			}
			nodeStack.pop_front();
			break;
		}
		if (nodeStack.size() > 0 && nullptr == (nodeStack.rbegin()->first))
			nodeStack.pop_back();
	}
	if (indexStr < treeStruct.size() || indexVec < vecData.size())
		root = nullptr;
	return root;
}

template <typename DT>
std::vector<DT> BinaryTree<DT>::GetLeafData() const
{
	return GetNodeDataLvlOrder(IsLeaf);
}

template <typename DT>
std::vector<DT> BinaryTree<DT>::GetNodeDataPreOrder(Pred4TreeNodePtr pred) const
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
		if (nodeStack.size() > 0 && nullptr == (nodeStack.rbegin()->first))
			nodeStack.pop_back();
	}
	return vecData;
}

template <typename DT>
std::vector<DT> BinaryTree<DT>::GetNodeDataLvlOrder(Pred4TreeNodePtr pred) const
{
	std::vector<DT> vecData;
	std::list<std::pair<decltype(root), unsigned char>> nodeStack{{root, 0}};
	typename decltype(nodeStack)::iterator nodeStackIt;
	while (!nodeStack.empty()) {
		nodeStackIt = nodeStack.begin();
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
			nodeStack.pop_front();
			break;
		}
		if (nodeStack.size() > 0 && nullptr == (nodeStack.rbegin()->first))
			nodeStack.pop_back();
	}
	return vecData;
}

template <typename DT>
bool BinaryTree<DT>::IsLeaf(const typename BinaryTreeNode<DT>::NodePtr &node)
{
	return (node != nullptr && node->lchild == nullptr && node->rchild == nullptr);
}

#endif // _BINARYTREE_H
