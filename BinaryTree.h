#ifndef _BINARYTREE_H
#define _BINARYTREE_H

#include <memory>
#include <vector>

#define CODE_CHLDNULL	('0')
#define CODE_CHLDEXIST	('1')

template <typename DT>
class BinaryTreeNode
{
	public:
		using NodePtr = std::shared_ptr<BinaryTreeNode<DT>>;

		BinaryTreeNode(DT, const NodePtr &l = nullptr, const NodePtr &r = nullptr);

		DT data;
		NodePtr lchild;
		NodePtr rchild;
};

template <typename DT>
class BinaryTree
{
	public:
		BinaryTree(const typename BinaryTreeNode<DT>::NodePtr &r = nullptr);

		const typename BinaryTreeNode<DT>::NodePtr GetRoot() const;
		void SetRoot(typename BinaryTreeNode<DT>::NodePtr&);
		std::string GetTreeStruct() const;
		typename BinaryTreeNode<DT>::NodePtr SetTreeStruct(
				const std::string&,
				const std::vector<DT>&);
	private:
		typename BinaryTreeNode<DT>::NodePtr root;

		std::string GetTreeStructPreOrder() const;
		typename BinaryTreeNode<DT>::NodePtr SetTreeStructPreOrder(
				const std::string&,
				const std::vector<DT>&);
};

#endif // _BINARYTREE_H
