#include <iostream>
#include "BinaryTree.h"

template <typename DT>
BinaryTreeNode<DT>::BinaryTreeNode(DT d,
		std::shared_ptr<BinaryTreeNode<DT>> l,
		std::shared_ptr<BinaryTreeNode<DT>> r):
	data(d), lchild(l), rchild(r)
{
}
