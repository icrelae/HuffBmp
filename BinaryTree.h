#ifndef _BINARYTREE_H
#define _BINARYTREE_H

#include <memory>
#include <vector>

template <typename DT>
class BinaryTreeNode
{
	public:
		using NodePtr = std::shared_ptr<BinaryTreeNode<DT>>;
		BinaryTreeNode(DT d,
				const NodePtr &l = nullptr,
				const NodePtr &r = nullptr);
		DT data;
		NodePtr lchild;
		NodePtr rchild;
};

template <typename DT>
class BinaryTree
{
	public:
		std::string GetTreeStruct();
		typename BinaryTreeNode<DT>::NodePtr SetTreeStruct(
				const std::string&,
				const std::vector<DT>&);
		BinaryTree(const typename BinaryTreeNode<DT>::NodePtr&);
		const typename BinaryTreeNode<DT>::NodePtr GetRoot();
	private:
		typename BinaryTreeNode<DT>::NodePtr root;
		std::string GetTreeStructPreOrder();
		typename BinaryTreeNode<DT>::NodePtr SetTreeStructPreOrder(
				const std::string&,
				const std::vector<DT>&);
};

#endif // _BINARYTREE_H
