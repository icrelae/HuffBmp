#ifndef _BINARYTREE_H
#define _BINARYTREE_H

#include <memory>

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
		BinaryTree(const typename BinaryTreeNode<DT>::NodePtr&);
	private:
		typename BinaryTreeNode<DT>::NodePtr root;
		std::string TreeStructPreOrder();
};

#endif // _BINARYTREE_H
