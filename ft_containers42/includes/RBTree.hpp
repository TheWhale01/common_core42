#ifndef __RBTREE_HPP__
# define __RBTREE_HPP__

#include "utility.hpp"
#include "iterator.hpp"
#include "algorithm.hpp"
#include "type_traits.hpp"
#include <memory>
#include <functional>

enum Colors
{
	RED,
	BLACK,
};

template <class T, class Compare = std::less<T>, class Alloc = std::allocator<T> >
class RBTree
{
	public:
		class Node
		{
			public:
				T data;
				bool is_nil;
				int color;
				Node *parent;
				Node *leftChild;
				Node *rightChild;

				Node(void) : is_nil(false), color(RED), parent(NULL), leftChild(NULL), rightChild(NULL) {}
				Node(T const &data) : data(data), is_nil(false), color(RED), parent(NULL), leftChild(NULL), rightChild(NULL) {}
		};

		typedef Compare compare_type;
		typedef RBTree<T> RBTree_t;
		typedef typename RBTree<T>::Node node_t;
		typedef typename Alloc::template rebind<node_t>::other allocator_type;

		RBTree(void) {_init_tree();}
		RBTree(compare_type comp, allocator_type alloc): _comp(comp), _allocator(alloc) {_init_tree();}

		~RBTree(void)
		{
			_deleteTree(_root);
			_freeNode(_nil);
		}

		ft::pair<node_t *, bool> insert(T data)
		{
			node_t *y = _nil;
			node_t *x = _root;

			while (x != _nil)
			{
				y = x;
				if (_comp(data, x->data))
					x = x->leftChild;
				else if (_comp(x->data, data))
					x = x->rightChild;
				else
					return (ft::make_pair(x, false));
			}
			node_t *node = _allocator.allocate(1);
			_allocator.construct(node, data);
			node->leftChild = _nil;
			node->rightChild = _nil;
			node->parent = y;
			if (y == _nil)
				_root = node;
			else if (_comp(node->data, y->data))
				y->leftChild = node;
			else
				y->rightChild = node;
			_nil->parent = node;
			if (node->parent == _nil)
			{
				node->color = BLACK;
				return (ft::make_pair(node, true));
			}
			if (node->parent->parent == _nil)
				return (ft::make_pair(node, true));
			_insertFix(node);
			_root->parent = _nil;
			_nil->parent = max();
			return (ft::make_pair(node, true));
		}

		ft::pair<node_t *, bool> insert_opti(T data, node_t *clue)
		{
			node_t *y = _nil;
			node_t *x = clue;

			while (x != _nil)
			{
				y = x;
				if (_comp(data, x->data))
					x = x->leftChild;
				else if (_comp(x->data, data))
					x = x->rightChild;
				else
					return (ft::make_pair(x, false));
			}
			node_t *node = _allocator.allocate(1);
			_allocator.construct(node, data);
			node->leftChild = _nil;
			node->rightChild = _nil;
			node->parent = y;
			if (y == _nil)
				_root = node;
			else if (_comp(node->data, y->data))
				y->leftChild = node;
			else
				y->rightChild = node;
			_nil->parent = node;
			if (node->parent == _nil)
			{
				node->color = BLACK;
				return (ft::make_pair(node, true));
			}
			if (node->parent->parent == _nil)
				return (ft::make_pair(node, true));
			_insertFix(node);
			_root->parent = _nil;
			_nil->parent = max();
			return (ft::make_pair(node, true));
		}

		void deleteNode(node_t *z)
		{
			node_t *x, *y;
			if (z == _nil)
				return;
			y = z;
			int y_original_color = y->color;
			if (z->leftChild == _nil)
			{
				x = z->rightChild;
				_transplant(z, z->rightChild);
			}
			else if (z->rightChild == _nil)
			{
				x = z->leftChild;
				_transplant(z, z->leftChild);
			}
			else
			{
				y = min(z->rightChild);
				y_original_color = y->color;
				x = y->rightChild;
				if (y->parent == z)
				{
					x->parent = y;
				}
				else
				{
					_transplant(y, y->rightChild);
					y->rightChild = z->rightChild;
					y->rightChild->parent = y;
				}

				_transplant(z, y);
				y->leftChild = z->leftChild;
				y->leftChild->parent = y;
				y->color = z->color;
			}
			_freeNode(z);
			z = NULL;
			if (y_original_color == BLACK)
				_deleteFix(x);
			_root->parent = _nil;
			_nil->parent = max(_root);
		}

		node_t *search(T const data) const
		{
			node_t *tmp = _root;

			while (tmp != _nil && tmp->data != data)
			{
				if (_comp(data, tmp->data))
					tmp = tmp->leftChild;
				else
					tmp = tmp->rightChild;
			}
			return (tmp);
		}

		node_t *min(void) const {return (min(_root));}
		node_t *max(void) const {return (max(_root));}

		node_t *min(node_t *n) const
		{
			node_t *tmp = n;

			while (tmp != _nil && tmp->leftChild != _nil)
				tmp = tmp->leftChild;
			return (tmp);
		}

		node_t *max(node_t *n) const
		{
			node_t *tmp = n;

			while (tmp != _nil && tmp->rightChild != _nil)
				tmp = tmp->rightChild;
			return (tmp);
		}

		void swap(RBTree &tree)
		{
			ft::swap(_root, tree._root);
			ft::swap(_nil, tree._nil);
			ft::swap(_comp, tree._comp);
		}

		node_t *getNil(void) const {return (_nil);}
		node_t const *getRoot(void) const {return (_root);}
		compare_type value_comp(void) const {return (_comp);}
		allocator_type const &get_allocator(void) const {return (_allocator);}

	private:
		node_t *_root;
		node_t *_nil;
		compare_type _comp;
		allocator_type _allocator;

		void _init_tree(void)
		{
			_nil = _allocator.allocate(1);
			_allocator.construct(_nil, T());
			_nil->parent = NULL;
			_nil->leftChild = NULL;
			_nil->rightChild = NULL;
			_nil->color = BLACK;
			_nil->is_nil = true;
			_root = _nil;
			_root->parent = _nil;
		}

		void _leftRotate(node_t *n)
		{
			node_t *sw = n->rightChild;

			n->rightChild = sw->leftChild;
			if (sw->leftChild != _nil)
				sw->leftChild->parent = n;
			sw->parent = n->parent;
			if (n->parent == _nil)
				_root = sw;
			else if (n == n->parent->leftChild)
				n->parent->leftChild = sw;
			else
				n->parent->rightChild = sw;
			sw->leftChild = n;
			n->parent = sw;
		}

		void _rightRotate(node_t *n)
		{
			node_t *sw = n->leftChild;

			n->leftChild = sw->rightChild;
			if (sw->rightChild != _nil)
				sw->rightChild->parent = n;
			sw->parent = n->parent;
			if (n->parent == _nil)
				_root = sw;
			else if (n == n->parent->leftChild)
				n->parent->leftChild = sw;
			else
				n->parent->rightChild = sw;
			sw->rightChild = n;
			n->parent = sw;
		}

		void _insertFix(node_t *n)
		{
			node_t *u;

			while (n != _root && n->parent->color == RED)
			{
				if (n->parent == n->parent->parent->rightChild)
				{
					u = n->parent->parent->leftChild;
					if (u->color == RED)
					{
						u->color = BLACK;
						n->parent->color = BLACK;
						n->parent->parent->color = RED;
						n = n->parent->parent;
					}
					else
					{
						if (n == n->parent->leftChild)
						{
							n = n->parent;
							_rightRotate(n);
						}
						n->parent->color = BLACK;
						n->parent->parent->color = RED;
						_leftRotate(n->parent->parent);
					}
				}
				else
				{
					u = n->parent->parent->rightChild;

					if (u->color == RED)
					{
						u->color = BLACK;
						n->parent->color = BLACK;
						n->parent->parent->color = RED;
						n = n->parent->parent;
					}
					else
					{
						if (n == n->parent->rightChild)
						{
							n = n->parent;
							_leftRotate(n);
						}
						n->parent->color = BLACK;
						n->parent->parent->color = RED;
						_rightRotate(n->parent->parent);
					}
				}
			}
			_root->color = BLACK;
		}

		void _transplant(node_t *a, node_t *b)
		{
			if (a->parent == _nil)
				_root = b;
			else if (a == a->parent->leftChild)
				a->parent->leftChild = b;
			else
				a->parent->rightChild = b;
			b->parent = a->parent;
		}

		void _deleteFix(node_t *x)
		{
			node_t *s;
			while (x != _root && x->color == BLACK)
			{
				if (x == x->parent->leftChild)
				{
					s = x->parent->rightChild;
					if (s->color == RED)
					{
						s->color = BLACK;
						x->parent->color = RED;
						_leftRotate(x->parent);
						s = x->parent->rightChild;
					}

					if (s->leftChild->color == BLACK && s->rightChild->color == BLACK)
					{
						s->color = RED;
						x = x->parent;
					}
					else
					{
						if (s->rightChild->color == BLACK)
						{
							s->leftChild->color = BLACK;
							s->color = RED;
							_rightRotate(s);
							s = x->parent->rightChild;
						}

						s->color = x->parent->color;
						x->parent->color = BLACK;
						s->rightChild->color = BLACK;
						_leftRotate(x->parent);
						x = _root;
					}
				}
				else
				{
					s = x->parent->leftChild;
					if (s->color == RED)
					{
						s->color = BLACK;
						x->parent->color = RED;
						_rightRotate(x->parent);
						s = x->parent->leftChild;
					}

					if (s->rightChild->color == BLACK && s->rightChild->color == BLACK)
					{
						s->color = RED;
						x = x->parent;
					}
					else
					{
						if (s->leftChild->color == BLACK)
						{
							s->rightChild->color = BLACK;
							s->color = RED;
							_leftRotate(s);
							s = x->parent->leftChild;
						}

						s->color = x->parent->color;
						x->parent->color = BLACK;
						s->leftChild->color = BLACK;
						_rightRotate(x->parent);
						x = _root;
					}
				}
			}
			x->color = BLACK;
		}

		void _deleteTree(node_t *root)
		{
			if (root == _nil)
				return;
			_deleteTree(root->leftChild);
			_deleteTree(root->rightChild);
			_freeNode(root);
		}

		void _freeNode(node_t *n)
		{
			if (n != _nil)
				_allocator.destroy(n);
			_allocator.deallocate(n, 1);
		}
};

template<typename T>
class RBTreeIter: public ft::iterator_traits<T*> {
	public:
		typedef ft::bidirectional_iterator_tag iterator_category;
		typedef typename ft::iterator_traits<T*>::value_type value_type;
		typedef typename ft::iterator_traits<T*>::reference reference;
		typedef typename ft::iterator_traits<T*>::pointer pointer;
		typedef typename ft::iterator_traits<T*>::difference_type difference_type;
		typedef typename RBTree<value_type>::Node* ptrnode_t;

		RBTreeIter() {}
		RBTreeIter(ptrnode_t node): _node(node) {}
		RBTreeIter(const RBTreeIter<value_type> &other) {*this = other;}

		RBTreeIter& operator=(const RBTreeIter<value_type>& other)
		{
			_node = other.node();
			return (*this);
		}

		pointer operator->() const {return (&_node->data);}
		reference operator*() const {return (_node->data);}

		RBTreeIter& operator++()
		{
			if (_node->is_nil)
			{
				_node = _node->parent;
				return (*this);
			}
			if (_node->rightChild && !_node->rightChild->is_nil)
				_node = tree_min(_node->rightChild);
			else
			{
				ptrnode_t y = _node->parent;
				while (y && _node == y->rightChild)
				{
					_node = y;
					y = y->parent;
				}
				_node = y;
			}
			return (*this);
		}

		RBTreeIter operator++(int)
		{
			if (_node->is_nil)
			{
				_node = _node->parent;
				return (*this);
			}
			RBTreeIter<value_type> temp = *this;
			if (_node->rightChild && !_node->rightChild->is_nil)
				_node = tree_min(_node->rightChild);
			else
			{
				ptrnode_t y = _node->parent;
				while (y && _node == y->rightChild)
				{
					_node = y;
					y = y->parent;
				}
				_node = y;
			}
			return (temp);
		}

		RBTreeIter& operator--()
		{
			if (_node->is_nil)
			{
				_node = _node->parent;
				return (*this);
			}
			if (_node->leftChild && !_node->leftChild->is_nil)
				_node = tree_max(_node->leftChild);
			else
			{
				ptrnode_t y = _node->parent;
				while (!y->is_nil && _node == y->leftChild)
				{
					_node = y;
					y = y->parent;
				}
				_node = y;
			}
			return (*this);
		}

		RBTreeIter operator--(int)
		{
			RBTreeIter<value_type> temp = *this;
			if (_node->is_nil)
			{
				_node = _node->parent;
				return (*this);
			}
			if (_node->leftChild && !_node->leftChild->is_nil)
				_node = tree_max(_node->leftChild);
			else
			{
				ptrnode_t y = _node->parent;
				while (y && _node == y->leftChild)
				{
					_node = y;
					y = y->parent;
				}
				_node = y;
			}
			return (temp);
		}

		ptrnode_t node() const {return _node;}

	private:
		ptrnode_t _node;

		ptrnode_t tree_min(ptrnode_t n) const
		{
			while(n->leftChild && !n->leftChild->is_nil)
				n = n->leftChild;
			return n;
		}

		ptrnode_t tree_max(ptrnode_t n) const
		{
			while (!n->rightChild->is_nil)
				n = n->rightChild;
			return n;
		}
};

template<typename T>
class RBTreeConstIter: public ft::iterator_traits<const T*>
{
	public:
		typedef ft::bidirectional_iterator_tag iterator_category;
		typedef typename ft::iterator_traits<const T*>::value_type value_type;
		typedef typename ft::iterator_traits<const T*>::reference reference;
		typedef typename ft::iterator_traits<const T*>::pointer pointer;
		typedef typename ft::iterator_traits<const T*>::difference_type difference_type;
		typedef typename RBTree<value_type>::Node* ptrnode_t;

		RBTreeConstIter() {}
		RBTreeConstIter(ptrnode_t node): _node(node) {}
		RBTreeConstIter(const RBTreeIter<value_type> &lhs): _node(lhs.node()) {}
		RBTreeConstIter(const RBTreeConstIter<value_type> &other) {*this = other;}

		RBTreeConstIter& operator=(const RBTreeConstIter<value_type>& other)
		{
			_node = other.node();
			return (*this);
		}

		pointer operator->() const {return (&_node->data);}
		reference operator*() const {return (_node->data);}

		RBTreeConstIter& operator++()
		{
			if (_node->is_nil)
			{
				_node = _node->parent;
				return (*this);
			}
			if (_node->rightChild && !_node->rightChild->is_nil)
				_node = tree_min(_node->rightChild);
			else
			{
				ptrnode_t y = _node->parent;
				while (y && _node == y->rightChild)
				{
					_node = y;
					y = y->parent;
				}
				_node = y;
			}
			return (*this);
		}

		RBTreeConstIter operator++(int)
		{
			if (_node->is_nil)
			{
				_node = _node->parent;
				return (*this);
			}
			RBTreeConstIter<value_type> temp = *this;
			if (_node->rightChild && !_node->rightChild->is_nil)
				_node = tree_min(_node->rightChild);
			else
			{
				ptrnode_t y = _node->parent;
				while (y && _node == y->rightChild)
				{
					_node = y;
					y = y->parent;
				}
				_node = y;
			}
			return (temp);
		}

		RBTreeConstIter& operator--()
		{
			if (_node->is_nil)
			{
				_node = _node->parent;
				return (*this);
			}
			if (_node->leftChild && !_node->leftChild->is_nil)
				_node = tree_max(_node->leftChild);
			else
			{
				ptrnode_t y = _node->parent;
				while (!y->is_nil && _node == y->leftChild)
				{
					_node = y;
					y = y->parent;
				}
				_node = y;
			}
			return (*this);
		}

		RBTreeConstIter operator--(int)
		{
			RBTreeConstIter<value_type> temp = *this;
			if (_node->is_nil)
			{
				_node = _node->parent;
				return (*this);
			}
			if (_node->leftChild && !_node->leftChild->is_nil)
				_node = tree_max(_node->leftChild);
			else
			{
				ptrnode_t y = _node->parent;
				while (y && _node == y->leftChild)
				{
					_node = y;
					y = y->parent;
				}
				_node = y;
			}
			return (temp);
		}

		ptrnode_t node() const {return _node;}

	private:
		ptrnode_t _node;

		ptrnode_t tree_min(ptrnode_t n) const
		{
			while(n->leftChild && !n->leftChild->is_nil)
				n = n->leftChild;
			return n;
		}

		ptrnode_t tree_max(ptrnode_t n) const
		{
			while (!n->rightChild->is_nil)
				n = n->rightChild;
			return n;
		}
};

template<typename A, typename B>
bool operator==(const RBTreeIter<A> & lhs, const RBTreeIter<B> & rhs) {return (lhs.node() == rhs.node());}

template<typename A, typename B>
bool operator!=(const RBTreeIter<A> & lhs, const RBTreeIter<B> & rhs) {return (lhs.node() != rhs.node());}

template<typename A, typename B>
bool operator==(const RBTreeConstIter<A> & lhs, const RBTreeConstIter<B> & rhs) {return (lhs.node() == rhs.node());}

template<typename A, typename B>
bool operator!=(const RBTreeConstIter<A> & lhs, const RBTreeConstIter<B> & rhs) {return (lhs.node() != rhs.node());}

template<typename A, typename B>
bool operator==(const RBTreeConstIter<A> &lhs, const RBTreeIter<B> &rhs) {return (lhs.node() == rhs.node());}

template<typename A, typename B>
bool operator!=(const RBTreeConstIter<A> &lhs, const RBTreeIter<B> &rhs) {return (lhs.node() != rhs.node());}

template<typename A, typename B>
bool operator==(const RBTreeIter<A> &lhs, const RBTreeConstIter<B> &rhs) {return (lhs.node() == rhs.node());}

template<typename A, typename B>
bool operator!=(const RBTreeIter<A> &lhs, const RBTreeConstIter<B> &rhs) {return (lhs.node() != rhs.node());}

#endif