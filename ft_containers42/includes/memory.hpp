#ifndef __MEMORY_HPP__
# define __MEMORY_HPP__

#include "iterator.hpp"

namespace ft
{
	template<class InputIterator, class ForwardIterator>
	ForwardIterator uninitialized_copy ( InputIterator first, InputIterator last, ForwardIterator result )
	{
		for (; first!=last; ++result, ++first)
			new (static_cast<void*>(&*result)) typename ft::iterator_traits<ForwardIterator>::value_type(*first);
		return result;
	}

	template < class ForwardIterator, class Size, class T >
	void uninitialized_fill_n ( ForwardIterator first, Size n, const T& x )
	{
		for (; n--; ++first)
			new (static_cast<void*>(&*first)) typename ft::iterator_traits<ForwardIterator>::value_type(x);
	}

	template<class BidirectionalIterator1, class BidirectionalIterator2>
	BidirectionalIterator2 uninitialized_copy_backward ( BidirectionalIterator1 first,
											BidirectionalIterator1 last,
											BidirectionalIterator2 result )
	{
		while (last!=first)
			new (static_cast<void*>(&*(--result))) typename ft::iterator_traits<BidirectionalIterator2>::value_type(*(--last));
		return result;
	}
}

#endif