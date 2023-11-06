#ifndef __MAP_HPP__
# define __MAP_HPP__

#include "RBTree.hpp"
#include "utility.hpp"
#include "iterator.hpp"
#include <memory>

namespace ft
{
	template<class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> > >
	class map
	{
		public:
			typedef Key key_type;
			typedef T mapped_type;
			typedef ft::pair<const key_type, mapped_type> value_type;
			typedef Compare key_compare;
			typedef Alloc allocator_type;
			typedef typename allocator_type::reference reference;
			typedef typename allocator_type::const_reference const_reference;
			typedef typename allocator_type::pointer pointer;
			typedef typename allocator_type::const_pointer const_pointer;
			typedef RBTreeIter<value_type> iterator;
			typedef RBTreeConstIter<value_type> const_iterator;
			typedef ft::reverse_iterator<iterator> reverse_iterator;
			typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
			typedef typename ft::iterator_traits<iterator>::difference_type difference_type;
			typedef std::size_t size_type;

			class value_compare: std::binary_function<value_type, value_type, bool>
			{
				public:
					typedef bool result_type;
					typedef value_type first_argument_type;
					typedef value_type second_argument_type;
					
					value_compare(key_compare c): comp(c) {}

					result_type operator()(const value_type &lhs, const value_type &rhs) const {return (comp(lhs.first, rhs.first));}

				protected:
					key_compare comp;
			};

			typedef RBTree<value_type, value_compare, allocator_type> RBTree_t;
			typedef typename RBTree_t::node_t node_t;

			// CONSTRUCTORS
			explicit map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()): _size(0), _comp(comp), _alloc(alloc), _tree(RBTree_t(comp, alloc)) {}
			template<class InputIterator>
			map(InputIterator first, InputIterator last, const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()): _size(0), _comp(comp), _alloc(alloc), _tree(RBTree_t(comp, alloc)) {insert(first, last);}
			map(const map &x): _size(0), _comp(x._comp), _alloc(x._alloc), _tree(RBTree_t(_comp, _alloc)) {insert(x.begin(), x.end());}

			// DESTRUCTOR
			~map(void) {}

			// OPERATOR OVERLOAD
			map &operator=(const map &x)
			{
				if (this == &x)
					return (*this);
				clear();
				insert(x.begin(), x.end());
				return (*this);
			}

			// ITERATORS
			iterator begin(void) {return (iterator(_tree.min()));}
			const_iterator begin(void) const {return (const_iterator(_tree.min()));}
			iterator end(void) {return (iterator(_tree.getNil()));}
			const_iterator end(void) const {return (_tree.getNil());}
			reverse_iterator rbegin(void) {return (reverse_iterator(_tree.getNil()));}
			const_reverse_iterator rbegin(void) const {return (const_reverse_iterator(_tree.getNil()));}
			reverse_iterator rend(void) {return (reverse_iterator(_tree.min()));}
			const_reverse_iterator rend(void) const {return (const_reverse_iterator(_tree.min()));}

			// CAPACITY
			bool empty(void) const {return (!_size);}
			size_type size(void) const {return (_size);}
			size_type max_size(void) const {return (_tree.get_allocator().max_size());}

			// ELEMENT ACCESS
			mapped_type &operator[](const key_type &k) {return ((*((insert(ft::make_pair(k,mapped_type()))).first)).second);}

			// MODIFIERS
			ft::pair<iterator, bool> insert(const value_type &val)
			{
				ft::pair<node_t *, bool> pr = _tree.insert(val);
				if (pr.second)
					_size++;
				return (pr);
			}

			iterator insert(iterator pos, const value_type &val)
			{
				(void)pos;
				return (insert(val).first);
			}

			template<class InputIterator>
			void insert(InputIterator first, InputIterator last) {while (first != last) insert(*(first)++);}

			void erase(iterator position)
			{
				_tree.deleteNode(position.node());
				_size--;
			}

			size_type erase(const key_type &k)
			{
				iterator found = find(k);

				if (found == end())
					return (0);
				_tree.deleteNode(found.node());
				_size--;
				return (1);
			}

			void erase(iterator first, iterator last) {while (first != last) erase(first++);}

			void swap(map &x)
			{
				ft::swap(_size, x._size);
				ft::swap(_comp, x._comp);
				_tree.swap(x._tree);
			}

			void clear(void) {erase(begin(), end());}

			// OBSERVERS
			key_compare key_comp(void) const {return (_comp);}
			value_compare value_comp(void) const {return (_tree.value_comp());}

			// OPERATIONS
			iterator find(const key_type &k)
			{
				for (iterator it = begin(); it != end(); it++)
					if (it->first == k)
						return (it);
				return (end());
			}

			const_iterator find(const key_type &k) const
			{
				for (const_iterator it = begin(); it != end(); it++)
					if (it->first == k)
						return (it);
				return (end());
			}

			size_type count(const key_type &k) const {return (find(k) == end() ? 0 : 1);}

			iterator lower_bound(key_type const &k)
			{
				iterator it;

				for (it = begin(); it != end(); it++)
					if (it->first >= k)
						return (it);
				return (it);
			}

			const_iterator lower_bound(key_type const &k) const
			{
				const_iterator it;

				for (it = begin(); it != end(); it++)
					if (it->first >= k)
						return (it);
				return (it);
			}

			iterator upper_bound(key_type const &k)
			{
				iterator it;

				for (it = begin(); it != end(); it++)
					if (it->first > k)
						return (it);
				return (it);
			}

			const_iterator upper_bound(key_type const &k) const
			{
				const_iterator it;

				for (it = begin(); it != end(); it++)
					if (it->first > k)
						return (it);
				return (it);
			}

			ft::pair<iterator, iterator> equal_range(key_type const &key) {return (make_pair(lower_bound(key), upper_bound(key)));}
			ft::pair<const_iterator, const_iterator> equal_range(key_type const &key) const {return (make_pair(lower_bound(key), upper_bound(key)));}

			// ALLOCATOR
			allocator_type get_allocator(void) const {return (_alloc);}

		private:
			size_type _size;
			key_compare _comp;
			allocator_type _alloc;
			RBTree_t _tree;
	};
	
	template<class Key, class T, class Compare, class Alloc>
	bool operator==(map<Key, T, Compare, Alloc> const &lhs, map<Key, T, Compare, Alloc> const &rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		typename map<Key, T, Compare, Alloc>::const_iterator lhs_it = lhs.begin();
		typename map<Key, T, Compare, Alloc>::const_iterator rhs_it = rhs.begin();
		while ((*lhs_it) == (*rhs_it) && lhs_it != lhs.end())
		{
			lhs_it++;
			rhs_it++;
		}
		return (lhs_it == lhs.end() ? true : false);
	}

	template<class Key, class T, class Compare, class Alloc>
	void swap(map<Key, T, Compare, Alloc> &x, map<Key, T, Compare, Alloc> &y) {x.swap(y);}

	template<class Key, class T, class Compare, class Alloc>
	bool operator!=(map<Key, T, Compare, Alloc> const &lhs, map<Key, T, Compare, Alloc> const &rhs) {return (!(lhs == rhs));}

	template<class Key, class T, class Compare, class Alloc>
	bool operator<(map<Key, T, Compare, Alloc> const &lhs, map<Key, T, Compare, Alloc> const &rhs) {return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));}

	template<class Key, class T, class Compare, class Alloc>
	bool operator>(map<Key, T, Compare, Alloc> const &lhs, map<Key, T, Compare, Alloc> const &rhs) {return (ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));}

	template<class Key, class T, class Compare, class Alloc>
	bool operator<=(map<Key, T, Compare, Alloc> const &lhs, map<Key, T, Compare, Alloc> const &rhs) {return (!(rhs < lhs));}

	template<class Key, class T, class Compare, class Alloc>
	bool operator>=(map<Key, T, Compare, Alloc> const &lhs, map<Key, T, Compare, Alloc> const &rhs) {return (!(lhs < rhs));}
}

#endif