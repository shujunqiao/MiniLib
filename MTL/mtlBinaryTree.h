#ifndef MTL_BINARY_TREE_H_INCLUDED__
#define MTL_BINARY_TREE_H_INCLUDED__

#include <cstdlib>
#include "mtlList.h"

template < typename type_t > class mtlBinaryTree;

template < typename type_t >
class mtlBranch
{
	friend class mtlBinaryTree<type_t>;
private:
	type_t					m_item;
	mtlBinaryTree<type_t>	*m_tree;
	mtlBranch<type_t>		*m_parent;
	mtlBranch<type_t>		*m_right;
	mtlBranch<type_t>		*m_left;

private:
	mtlBranch(const type_t &item, mtlBranch<type_t> *parent, mtlBinaryTree<type_t> *tree);
	mtlBranch( void ) {}
	mtlBranch<type_t>		&operator=(const mtlBranch<type_t>&) { return *this; }

	static int						GetDepth(const mtlBranch<type_t> *node, int currentDepth);
	static int						GetHeight(const mtlBranch<type_t> *node, int currentHeight);
	template < typename compare_t >
	static const mtlBranch<type_t>	*Find(const mtlBranch<type_t> *node, const compare_t &item, bool closest);
	template < typename compare_t >
	static mtlBranch<type_t>		*Find(mtlBranch<type_t> *node, const compare_t &item, bool closest);
	static bool						IsBalanced(const mtlBranch<type_t> *node, int permittedDifference);

public:
	const type_t			&GetItem( void ) const { return m_item; }
	const mtlBranch<type_t>	*GetParent( void ) const { return m_parent; }
	mtlBranch<type_t>		*GetParent( void ) { return m_parent; }
	const mtlBranch<type_t>	*GetRight( void ) const { return m_right; }
	mtlBranch<type_t>		*GetRight( void ) { return m_right; }
	const mtlBranch<type_t>	*GetLeft( void ) const { return m_left; }
	mtlBranch<type_t>		*GetLeft( void ) { return m_left; }
	int						GetDepth( void ) const { return GetDepth(this, 0); }
	int						GetHeight( void ) const { return GetHeight(this, 0); }
	template < typename compare_t >
	const mtlBranch<type_t>	*Find(const compare_t &item) const { return Find(this, item, false); }
	template < typename compare_t >
	mtlBranch<type_t>		*Find(const compare_t &item) { return Find(this, item, false); }
	template < typename compare_t >
	const mtlBranch<type_t>	*FindClosest(const compare_t &item) const { return Find(this, item, true); }
	template < typename compare_t >
	mtlBranch<type_t>		*FindClosest(const compare_t &item) { return Find(this, item, true); }
	const mtlBranch<type_t>	*FindMin( void ) const;
	mtlBranch<type_t>		*FindMin( void );
	const mtlBranch<type_t>	*FindMax( void ) const;
	mtlBranch<type_t>		*FindMax( void );
	bool					IsBalanced(int permittedDifference = 1) const { return IsBalanced(this, permittedDifference); }
	mtlBranch<type_t>		*Remove( void );
	template < typename func_t >
	void InOrder(const func_t &fn) const
	{
		if (m_left != NULL) { m_left->InOrder(functor); }
		fn(m_item);
		if (m_right != NULL) { m_right->InOrder(functor); }

	}
	template < typename func_t >
	void InReverseOrder(const func_t &fn) const
	{
		if (m_right != NULL) { m_right->InOrder(functor); }
		fn(m_item);
		if (m_left != NULL) { m_left->InOrder(functor); }
	}
	template < typename func_t >
	void InBreadth(const func_t &fn) const
	{
		mtlList<const mtlBranch<type_t>*> queue;
		queue.AddLast(this);
		while (queue.GetSize() != 0) {
			const mtlBranch<type_t> *front = queue.GetFirst();
			fn(front->GetItem());
			queue.RemoveFirst();
			if (front->m_left != NULL) { queue.AddLast(front->m_left); }
			if (front->m_right != NULL) { queue.AddLast(front->m_right); }
		}
	}
	template < typename func_t >
	void InBreadthReverse(const func_t &fn) const
	{
		mtlList<const mtlBranch<type_t>*> queue;
		queue.AddLast(this);
		while (queue.GetSize() != 0) {
			const mtlBranch<type_t> *front = queue.GetFirst();
			fn(front->GetItem());
			queue.RemoveFirst();
			if (front->m_right != NULL) { queue.AddLast(front->m_right); }
			if (front->m_left != NULL) { queue.AddLast(front->m_left); }
		}
	}
};

template < typename type_t >
mtlBranch<type_t>::mtlBranch(const type_t &item, mtlBranch<type_t> *parent, mtlBinaryTree<type_t> *tree) :
m_item(item), m_tree(tree), m_parent(parent), m_right(NULL), m_left(NULL)
{}

template < typename type_t >
int mtlBranch<type_t>::GetDepth(const mtlBranch<type_t> *node, int currentDepth)
{
	if (node == NULL) { return currentDepth; }
	return GetDepth(node->m_parent, currentDepth + 1);
}

template < typename type_t >
int mtlBranch<type_t>::GetHeight(const mtlBranch<type_t> *node, int currentHeight)
{
	if (node == NULL) { return currentHeight; }
	const int pos = GetHeight(node->m_right, currentHeight + 1);
	const int neg = GetHeight(node->m_left, currentHeight + 1);
	return (pos > neg) ? pos : neg;
}

template < typename type_t >
template < typename compare_t >
const mtlBranch<type_t> *mtlBranch<type_t>::Find(const mtlBranch<type_t> *node, const compare_t &item, bool closest)
{
	if (node->m_item == item) { return node; }
	if (node->m_item > item) {
		if (node->m_left != NULL) { return Find(node->m_left, item, closest); }
	} else {
		if (node->m_right != NULL) { return Find(node->m_right, item, closest); }
	}
	return closest ? node : NULL;
}

template < typename type_t >
template < typename compare_t >
mtlBranch<type_t> *mtlBranch<type_t>::Find(mtlBranch<type_t> *node, const compare_t &item, bool closest)
{
	if (node->m_item == item) { return node; }
	if (node->m_item > item) {
		if (node->m_left != NULL) { return Find(node->m_left, item, closest); }
	} else {
		if (node->m_right != NULL) { return Find(node->m_right, item, closest); }
	}
	return closest ? node : NULL;
}

// Find	a more efficient way of traversing...
template < typename type_t >
bool mtlBranch<type_t>::IsBalanced(const mtlBranch<type_t> *node, int permittedDifference)
{
	return node == NULL || (IsBalanced(node->m_left) && IsBalanced(node->m_right) && (abs(GetHeight(node->m_left, 0) - GetHeight(node->m_right, 0)) <= permittedDifference));
}

template < typename type_t >
mtlBranch<type_t> *mtlBranch<type_t>::Remove( void )
{
	return m_tree->Remove(this);
}

template < typename type_t >
const mtlBranch<type_t> *mtlBranch<type_t>::FindMin( void ) const
{
	const mtlBranch<type_t> *n = this;
	while (n->m_left != NULL) {
		n = n->m_left;
	}
	return n;
}

template < typename type_t >
mtlBranch<type_t> *mtlBranch<type_t>::FindMin( void )
{
	mtlBranch<type_t> *n = this;
	while (n->m_left != NULL) {
		n = n->m_left;
	}
	return n;
}

template < typename type_t >
const mtlBranch<type_t> *mtlBranch<type_t>::FindMax( void ) const
{
	const mtlBranch<type_t> *n = this;
	while (n->m_right != NULL) {
		n = n->m_right;
	}
	return n;
}

template < typename type_t >
mtlBranch<type_t> *mtlBranch<type_t>::FindMax( void )
{
	mtlBranch<type_t> *n = this;
	while (n->m_right != NULL) {
		n = n->m_right;
	}
	return n;
}

template < typename type_t >
class mtlBinaryTree
{
private:
	mtlBranch<type_t>	*m_root;
	int					m_size;

private:
	mtlBinaryTree &operator=(const mtlBinaryTree&) { return *this; }
	mtlBinaryTree(const mtlBinaryTree&) {}
	mtlBranch<type_t> *Insert(mtlBranch<type_t> *parent, mtlBranch<type_t> *&node, const type_t &item);
	void ToList(mtlList<type_t> &list, const mtlBranch<type_t> *node) const;
	void ToListReversed(mtlList<type_t> &list, const mtlBranch<type_t> *node) const;
	void Delete(mtlBranch<type_t> *node);

public:
	mtlBinaryTree( void );
	~mtlBinaryTree( void );
	const mtlBranch<type_t> *GetRoot( void ) const { return m_root; }
	mtlBranch<type_t>		*GetRoot( void ) { return m_root; }
	mtlBranch<type_t>		*Insert(const type_t &item);
	void					RemoveAll( void );
	int						GetSize( void ) const { return m_size; }
	void					ToList(mtlList<type_t> &list) const;
	void					ToListReversed(mtlList<type_t> &list) const;
	mtlBranch<type_t>		*Remove(mtlBranch<type_t> *node);
	bool					IsEmpty( void ) const;
	// rebalance
};

template < typename type_t >
mtlBranch<type_t> *mtlBinaryTree<type_t>::Insert(mtlBranch<type_t> *parent, mtlBranch<type_t> *&node, const type_t &item)
{
	if (node == NULL) {
		node = new mtlBranch<type_t>(item, parent, this);
		++m_size;
		return node;
	}
	if (node->m_item == item) { return node; }
	if (node->m_item > item) { return Insert(node, node->m_left, item); }
	return Insert(node, node->m_right, item);
}

template < typename type_t >
void mtlBinaryTree<type_t>::ToList(mtlList<type_t> &list, const mtlBranch<type_t> *node) const
{
	if (node->m_left != NULL) {
		ToList(list, node->m_left);
	}
	list.AddBack(node->m_item);
	if (node->m_right != NULL) {
		ToList(list, node->m_right);
	}
}

template < typename type_t >
void mtlBinaryTree<type_t>::ToListReversed(mtlList<type_t> &list, const mtlBranch<type_t> *node) const
{
	if (node->m_right != NULL) {
		ToList(list, node->m_right);
	}
	list.AddBack(node->m_item);
	if (node->m_left != NULL) {
		ToList(list, node->m_left);
	}
}

template < typename type_t >
void mtlBinaryTree<type_t>::Delete(mtlBranch<type_t> *node)
{
	if (node != NULL) {
		Delete(node->m_left);
		Delete(node->m_right);
		delete node;
	}
}

template < typename type_t >
mtlBinaryTree<type_t>::mtlBinaryTree( void ) :
m_root(NULL), m_size(0)
{}

template < typename type_t >
mtlBinaryTree<type_t>::~mtlBinaryTree( void )
{
	RemoveAll();
}

template < typename type_t >
mtlBranch<type_t> *mtlBinaryTree<type_t>::Insert(const type_t &item)
{
	return Insert(NULL, m_root, item);
}

template < typename type_t >
void mtlBinaryTree<type_t>::RemoveAll( void )
{
	Delete(m_root);
	m_root = NULL;
	m_size = 0;
}

template < typename type_t >
void mtlBinaryTree<type_t>::ToList(mtlList<type_t> &list) const
{
	list.RemoveAll();
	if (m_root == NULL) { return; }
	ToList(list, m_root);
}

template < typename type_t >
void mtlBinaryTree<type_t>::ToListReversed(mtlList<type_t> &list) const
{
	list.RemoveAll();
	if (m_root == NULL) { return; }
	ToListReversed(list, m_root);
}

template < typename type_t >
mtlBranch<type_t> *mtlBinaryTree<type_t>::Remove(mtlBranch<type_t> *node)
{
	if (node == NULL || node->m_tree != this) { return NULL; }

	// return the address of the node that assumes this place
	mtlBranch<type_t> *returnBranch = NULL;
	mtlBranch<type_t> **childPointer = NULL;
	if (node->m_parent != NULL) {
		if (node->m_parent->m_left == node) {
			childPointer = &node->m_parent->m_left;
		} else {
			childPointer = &node->m_parent->m_right;
		}
	}

	if (node->m_left == NULL) {
		if (node->m_right == NULL) {
			returnBranch = NULL;
		} else {
			returnBranch = node->m_left;
		}
	} else if (node->m_right == NULL) {
		returnBranch = node->m_right;
	} else { // positive and negative are guaranteed to be non-null
		// based on the address of the node, pick a "random" subtree to remove from (don't use LSB as it is unlikely to be 1)
		int side = 0;
		if (((unsigned long long)node & (1<<4))) {
			returnBranch = node->m_right->FindMin();
			side = 1;
		} else {
			returnBranch = node->m_left->FindMax();
			side = -1;
		}

		if (returnBranch->m_parent != node) {
			if (side == -1) { // only the smallest node's right side may be non-null (otherwise it would not be smallest)
				if (returnBranch->m_parent->m_left == returnBranch) {
					returnBranch->m_parent->m_left = returnBranch->m_right;
				} else {
					returnBranch->m_parent->m_right = returnBranch->m_right;
				}
			} else { // only the largest node's left side may be non-null (otherwise it would not be the largest)
				if (returnBranch->m_parent->m_left == returnBranch) {
					returnBranch->m_parent->m_left = returnBranch->m_left;
				} else {
					returnBranch->m_parent->m_right = returnBranch->m_left;
				}
			}
		}

		returnBranch->m_left = node->m_left;
		returnBranch->m_right = node->m_right;
	}

	if(returnBranch != NULL) {
		returnBranch->m_parent = node->m_parent;
	}

	if (node == m_root) {
		m_root = returnBranch;
	} else if (childPointer != NULL) {
		*childPointer = returnBranch;
	}
	delete node;
	return returnBranch;
}

template < typename type_t >
bool mtlBinaryTree<type_t>::IsEmpty( void ) const
{
	return m_root == NULL;
}

#endif
