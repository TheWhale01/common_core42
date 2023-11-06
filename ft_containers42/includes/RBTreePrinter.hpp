#ifndef __RBTREE_PRINTER_HPP__
# define __RBTREE_PRINTER_HPP__
#include <iostream>
#include <string>
#include "RBTree.hpp"

#define RED_COLOR "\e[0;31m"
#define BLACK_COLOR "\e[0;35m"
#define RESET_COLOR "\e[0;0m"

struct subTree
{
	subTree *_prev;
	std::string _str;

	subTree(subTree *prev, std::string str) : _prev(prev), _str(str)	{}
};

void printTrunks(std::ostream &stream, subTree *p)
{
	if (!p)
		return;
	printTrunks(stream, p->_prev);
	stream << p->_str;
}

template<typename node_t>
void printTree(std::ostream &stream, node_t const *node, node_t const *nil, subTree *prev, bool isLeft)
{
	if (node == nil)
		return;
	std::string prev_str = "    ";
	subTree sub = subTree(prev, prev_str);
	printTree(stream, node->rightChild, nil, &sub, true);
	if (!prev)
		sub._str = "———";
	else if (isLeft)
	{
		sub._str = ",———";
		prev_str = "   |";
	}
	else
	{
		sub._str = "`———";
		prev->_str = prev_str;
	}
	printTrunks(stream, &sub);
	stream << " " << (node->color == RED ? RED_COLOR : BLACK_COLOR) <<  node->data << RESET_COLOR << std::endl;
	if (prev)
		prev->_str = prev_str;
	sub._str = "   |";
	printTree(stream, node->leftChild, nil, &sub, false);
}

template <class T, class C, class A>
std::ostream &operator<<(std::ostream &stream, RBTree<T, C, A> const &tree)
{
	printTree(stream, tree.getRoot(), tree.getNil(), NULL, false);
	return (stream);
}

#endif