#ifndef __VECTOR_HPP__
# define __VECTOR_HPP__

#include "memory.hpp"
#include "iterator.hpp"
#include "algorithm.hpp"
#include "type_traits.hpp"
#include <memory>
#include <sstream>

namespace ft
{
	template< class T, class Alloc = std::allocator<T> >
	class vector
	{
		public:
			typedef T value_type;
			typedef std::size_t size_type;
			typedef Alloc allocator_type;
			typedef typename allocator_type::reference reference;
			typedef typename allocator_type::const_reference const_reference;
			typedef typename allocator_type::pointer pointer;
			typedef typename allocator_type::const_pointer const_pointer;
			typedef pointer iterator;
			typedef const_pointer const_iterator;
			typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
			typedef ft::reverse_iterator<iterator> reverse_iterator;
			typedef typename iterator_traits<iterator>::difference_type difference_type;

			// CONSTRUCTORS
			explicit vector(const allocator_type &alloc = allocator_type()): _data(NULL), _size(0), _capacity(0), _allocator(alloc) {}
			explicit vector(size_type n, const value_type &val = value_type(),
				const allocator_type &alloc = allocator_type()): _size(n), _capacity(n), _allocator(alloc)
			{
				_data = _allocator.allocate(_capacity);
				for (size_type i = 0; i < n; i++)
					_allocator.construct(_data + i, val);
			}

			template <class InputIterator>
			vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type(),  typename ft::enable_if<!ft::is_integral<InputIterator>::value, bool>::type = true): _size(ft::distance(first, last)), _capacity(_size), _allocator(alloc)
			{
				_data = _allocator.allocate(_capacity);
				for (size_type i = 0; first != last; i++)
					_allocator.construct(_data + i, *(first++));
			}
			vector(const vector &x): _data(NULL), _size(0), _capacity(0) {*this = x;}

			// DESTRUCTOR
			virtual ~vector(void)
			{
				for (size_type i = 0; i < _size; i++)
					_allocator.destroy(_data + i);
				_allocator.deallocate(_data, _capacity);
			}

			// OPERATOR OVERLOAD
			vector &operator=(vector const &rhs)
			{
				if (this == &rhs)
					return (*this);
				_allocator = rhs._allocator;
				assign(rhs.begin(), rhs.end());
				return (*this);
			}

			// ITERATORS
			iterator begin(void) {return (_data);}
			iterator end(void) {return (_data + _size);}
			const_iterator begin(void) const {return (_data);}
			const_iterator end(void) const {return (_data + _size);}
			reverse_iterator rbegin(void) {return (reverse_iterator(_data + _size));}
			reverse_iterator rend(void) {return (reverse_iterator(_data));}
			const_reverse_iterator rbegin(void) const {return (const_reverse_iterator(_data + _size));}
			const_reverse_iterator rend(void) const {return (const_reverse_iterator(_data));}

			// CAPACITY
			bool empty(void) const {return (!_size);}

			void reserve(size_type n)
			{
				if (n <= _capacity)
					return ;
				if (n > max_size())
					throw (std::length_error("vector::reserve"));
				pointer new_data = _allocator.allocate(n);
				for (size_type i = 0; i < _size; i++)
				{
					_allocator.construct(new_data + i, *(_data + i));
					_allocator.destroy(_data + i);
				}
				_allocator.deallocate(_data, _capacity);
				_data = new_data;
				_capacity = n;
			}

			void resize(size_type n, value_type val = value_type())
			{
				if (n < _size)
				{
					for (size_type i = n; i < _size; i++)
						_allocator.destroy(_data + i);
					_size = n;
				}
				else if (n > _size)
					insert(end(), n - _size, val);
			}

			size_type size(void) const {return (_size);}
			size_type max_size(void) const {return (_allocator.max_size());}
			size_type capacity(void) const {return (_capacity);}

			// ELEMENT ACCESS
			pointer data(void) {return (_data);}
			const_pointer data(void) const {return (_data);}
			reference back(void) {return (*(_data + (_size - 1)));}
			const_reference back(void) const {return (*(_data + (_size - 1)));}
			reference front(void) {return (*_data);}
			const_reference front(void) const {return (*_data);}

			reference at(size_type n)
			{
				if (n >= _size)
					throw (std::out_of_range("vector::at"));
				return (*(_data + n));
			}

			const_reference at(size_type n) const
			{
				if (n >= _size)
					throw (std::out_of_range("vector::at"));
				return (*(_data + n));
			}

			reference operator[](size_type n) {return (*(_data + n));}
			const_reference operator[](size_type n) const {return (*(_data + n));}

			// MODIFIERS
			void assign(size_type n, const value_type& val)
			{
				clear();
				if (n > _capacity)
					reserve(_capacity * 2 > n ? _capacity * 2 : n);
				_size = n;
				for (size_type i = 0; i < _size; i++)
					_allocator.construct(_data + i, val);
			}

			template<class InputIterator>
			void assign(InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0)
			{
				clear();
				size_type size = ft::distance(first, last);
				if (size > _capacity)
					reserve(_capacity * 2 > size ? _capacity * 2 : size);
				_size = size;
				for (size_type i = 0; first != last; i++)
					_allocator.construct(_data + i, *(first++));
			}

			void push_back(const value_type& val)
			{
				if (_size == _capacity || !_capacity)
					reserve(_capacity ? _capacity * 2 : 1);
				_allocator.construct(_data + _size++, val);
			}

			void pop_back(void)
			{
				if (!_size)
					return ;
				_allocator.destroy(_data + (_size - 1));
				_size--;
			}

			void clear(void)
			{
				for (size_type i = 0; i < _size; i++)
					_allocator.destroy(_data + i);
				_size = 0;
			}

			iterator erase(iterator pos)
			{
				iterator start = pos;
				_allocator.destroy(pos);
				while (pos + 1 != end())
				{
					_allocator.construct(pos, *(pos + 1));
					_allocator.destroy(pos + 1);
					pos++;
				}
				_size--;
				return (start);
			}

			iterator erase(iterator first, iterator last)
			{
				size_type range_size = ft::distance(first, last);
				for (size_type i = 0; i < range_size; i++)
					erase(first);
				return (first);
			}

			iterator insert(iterator position, const value_type &val)
			{
				difference_type start = position - begin();
				insert(position, 1, val);
				return (begin() + start);
			}

			void insert(iterator position, size_type n, value_type const &val)
			{
				if (!n)
					return;
				if (static_cast<size_type>(ft::distance(begin(), position)) > _size)
					throw std::out_of_range("position out of range");
				if (_size + n > _capacity)
				{
					const size_type new_capacity = _size + (_size > n ? _size : n);
					pointer new_data = _allocator.allocate(new_capacity);
					const size_type insert_offset = static_cast<size_type>(ft::distance(begin(), position));
					ft::uninitialized_copy(begin(), position, new_data);
					ft::uninitialized_fill_n(new_data + insert_offset, n, val);
					ft::uninitialized_copy(position, end(), new_data + insert_offset + n);
					for (size_type i = 0; i < _size; i++)
						_allocator.destroy(_data + i);
					_allocator.deallocate(_data, _capacity);
					_data = new_data;
					_size += n;
					_capacity = new_capacity;
				}
				else
				{
					const size_type insert_offset = static_cast<size_type>(ft::distance(begin(), position));
					ft::uninitialized_copy_backward(begin() + insert_offset, end(), end() + n);
					ft::uninitialized_fill_n(begin() + insert_offset, n, val);
					_size += n;
				}
			}

			template<class InputIterator>
			void insert(iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, bool>::type = true)
			{
				size_type range_size = ft::distance(first, last);

				if (!range_size)
					return;
				if (static_cast<size_type>(ft::distance(begin(), position)) > _size)
					throw std::out_of_range("position out of range");
				if (_size + range_size > _capacity)
				{
					const size_type new_capacity = _size + (_size > range_size ? _size : range_size);
					pointer new_data = _allocator.allocate(new_capacity);
					const size_type insert_offset = static_cast<size_type>(ft::distance(begin(), position));
					ft::uninitialized_copy(begin(), position, new_data);
					ft::uninitialized_copy(first, last, new_data + insert_offset);
					ft::uninitialized_copy(position, end(), new_data + insert_offset + range_size);
					for (size_type i = 0; i < _size; i++)
						_allocator.destroy(_data + i);
					_allocator.deallocate(_data, _capacity);
					_data = new_data;
					_size += range_size;
					_capacity = new_capacity;
				}
				else
				{
					const size_type insert_offset = static_cast<size_type>(ft::distance(begin(), position));
					ft::uninitialized_copy_backward(begin() + insert_offset, end(), end() + range_size);
					ft::uninitialized_copy(first, last, begin() + insert_offset);
					_size += range_size;
				}
			}

			void swap(vector &x)
			{
				ft::swap(x._data, _data);
				ft::swap(x._size, _size);
				ft::swap(x._capacity, _capacity);
			}

			allocator_type get_allocator(void) const {return (_allocator);}

		private:
			pointer _data;
			size_type _size;
			size_type _capacity;
			allocator_type _allocator;
	};

	template<class T, class Alloc>
	void swap(vector<T, Alloc> &x, vector<T, Alloc> &y) {x.swap(y);}

	//COMPARISON OPERATORS
	template<class T, class Alloc>
	bool operator==(vector<T, Alloc> const &lhs, vector<T, Alloc> const &rhs)
	{
		size_t i;

		if (lhs.size() != rhs.size())
			return (false);
		i = -1;
		while (++i < lhs.size())
			if (lhs[i] != rhs[i])
				return (false);
		return (true);
	}

	template<class T, class Alloc>
	bool operator!=(vector<T, Alloc> const &lhs, vector<T, Alloc> const &rhs) {return (!(lhs==rhs));}

	template<class T, class Alloc>
	bool operator<(vector<T, Alloc> const &lhs, vector<T, Alloc> const &rhs) {return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));}

	template<class T, class Alloc>
	bool operator>(vector<T, Alloc> const &lhs, vector<T, Alloc> const &rhs) {return (ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));}

	template<class T, class Alloc>
	bool operator<=(vector<T, Alloc> const &lhs, vector<T, Alloc> const &rhs) {return (!(lhs > rhs));}

	template<class T, class Alloc>
	bool operator>=(vector<T, Alloc> const &lhs, vector<T, Alloc> const &rhs) {return (!(lhs < rhs));}
}

#endif