#ifndef _BINARYTREE_H
#define _BINARYTREE_H

#include <memory>

template <typename DT>
class BinaryTreeNode
{
	public:
		BinaryTreeNode(DT d,
				std::shared_ptr<BinaryTreeNode<DT>> l = nullptr,
				std::shared_ptr<BinaryTreeNode<DT>> r = nullptr);
		DT data;
		std::shared_ptr<BinaryTreeNode<DT>> lchild;
		std::shared_ptr<BinaryTreeNode<DT>> rchild;
};

#endif // _BINARYTREE_H
