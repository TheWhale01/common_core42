#ifndef __ITERATOR_HPP__
# define __ITERATOR_HPP__
#include <cstddef>
#include <iostream>

namespace ft
{
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag {};
	struct bidirectional_iterator_tag {};
	struct random_access_iterator_tag {};

	template <class Iterator>
	class iterator_traits
	{
		public:
			typedef typename Iterator::difference_type difference_type;
			typedef typename Iterator::value_type value_type;
			typedef typename Iterator::pointer pointer;
			typedef typename Iterator::reference reference;
			typedef typename Iterator::iterator_category iterator_category;
	};
	
	template <class T>
	class iterator_traits<T*>
	{
		public:
			typedef std::ptrdiff_t difference_type;
			typedef T value_type;
			typedef T* pointer;
			typedef T& reference;
			typedef	ft::random_access_iterator_tag iterator_category;
	};
	
	template <class T>
	class iterator_traits<const T*>
	{
		public:
			typedef std::ptrdiff_t difference_type;
			typedef T	 value_type;
			typedef const T* pointer;
			typedef const T& reference;
			typedef	ft::random_access_iterator_tag iterator_category;
	};

	template<class Iterator>
	class reverse_iterator
	{
		public:
			typedef Iterator iterator_type;
			typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
			typedef typename iterator_traits<Iterator>::value_type value_type;
			typedef typename iterator_traits<Iterator>::difference_type difference_type;
			typedef typename iterator_traits<Iterator>::pointer pointer;
			typedef typename iterator_traits<Iterator>::reference reference;

			reverse_iterator(void): base_iterator() {}
			explicit reverse_iterator(iterator_type it): base_iterator(it) {}
			template<class Iter>
			reverse_iterator(const reverse_iterator<Iter> &rev_it) {base_iterator = rev_it.base();}

			iterator_type base(void) const {return (base_iterator);}

			reference operator*(void) const
			{
				iterator_type tmp = base_iterator;
				--tmp;
				return (*tmp);
			}

			reverse_iterator operator+(difference_type n) const {return (reverse_iterator(base_iterator - n));}

			reverse_iterator &operator++(void)
			{
				--base_iterator;
				return (*this);
			}

			reverse_iterator operator++(int)
			{
				reverse_iterator tmp = *this;
				++(*this);
				return (tmp);
			}

			reverse_iterator &operator+=(difference_type n)
			{
				base_iterator -= n;
				return (*this);
			}

			reverse_iterator operator-(difference_type n) const {return (reverse_iterator(base_iterator + n));}

			reverse_iterator &operator--(void)
			{
				++base_iterator;
				return (*this);
			}

			reverse_iterator operator--(int)
			{
				reverse_iterator tmp = *this;
				--(*this);
				return (tmp);
			}

			reverse_iterator &operator-=(difference_type n)
			{
				base_iterator += n;
				return (*this);
			}

			pointer operator->(void) const {return (&(operator*()));}
			reference operator[](difference_type n) const {return (base_iterator[-n-1]);}

		private:
			iterator_type base_iterator;
	};

	template<class Iterator1, class Iterator2>
	bool operator==(reverse_iterator<Iterator1> const &lhs, reverse_iterator<Iterator2> const &rhs) {return (lhs.base() == rhs.base());}

	template<class Iterator1, class Iterator2>
	bool operator!=(reverse_iterator<Iterator1> const &lhs, reverse_iterator<Iterator2> const &rhs) {return (lhs.base() != rhs.base());}

	template<class Iterator1, class Iterator2>
	bool operator<(reverse_iterator<Iterator1> const &lhs, reverse_iterator<Iterator2> const &rhs) {return (lhs.base() > rhs.base());}

	template<class Iterator1, class Iterator2>
	bool operator>(reverse_iterator<Iterator1> const &lhs, reverse_iterator<Iterator2> const &rhs) {return (lhs.base() < rhs.base());}

	template<class Iterator1, class Iterator2>
	bool operator<=(reverse_iterator<Iterator1> const &lhs, reverse_iterator<Iterator2> const &rhs) {return (lhs.base() >= rhs.base());}

	template<class Iterator1, class Iterator2>
	bool operator>=(reverse_iterator<Iterator1> const &lhs, reverse_iterator<Iterator2> const &rhs) {return (lhs.base() <= rhs.base());}

	template<class Iterator1, class Iterator2>
	typename reverse_iterator<Iterator1>::difference_type operator-(reverse_iterator<Iterator1> const &lhs, reverse_iterator<Iterator2> const &rhs) {return (rhs.base() - lhs.base());}

	template<class Iterator>
	reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, reverse_iterator<Iterator> const &rev_it) {return (rev_it + n);}

	template<class InputIterator>
	typename ft::iterator_traits<InputIterator>::difference_type distance_s(InputIterator first, InputIterator last, ft::random_access_iterator_tag) {return (last - first);}

	template<class InputIterator>
	typename ft::iterator_traits<InputIterator>::difference_type distance_s(InputIterator first, InputIterator last, typename ft::iterator_traits<InputIterator>::iterator_category)
	{
		typename ft::iterator_traits<InputIterator>::difference_type size;

		size = 0;
		while (first++ != last)
			size++;
		return (size);
	}

	template<class InputIterator>
	typename ft::iterator_traits<InputIterator>::difference_type distance(InputIterator first, InputIterator last)
	{
		typedef typename ft::iterator_traits<InputIterator>::iterator_category iterator_category;

		return (distance_s(first, last, iterator_category()));
	}
}

#endif