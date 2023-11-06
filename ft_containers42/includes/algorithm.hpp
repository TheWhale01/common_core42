#ifndef __ALGORITHM_HPP__
# define __ALGORITHM_HPP__ 

namespace ft
{
	template<class T>
	void swap(T &a, T &b)
	{
		T c(a);

		a = b;
		b = c;
	}

	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
	{
		while (first1 != last1)
		{
			if (first2==last2 || *first2 < *first1)
				return (false);
			else if (*first1 < *first2)
				return (true);
			++first1;
			++first2;
		}
		return (first2 != last2);
	}

	template<class InputIterator1, class InputIterator2, class Compare>
	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp)
	{
		while (first1 != last1)
		{
			if (first2==last2 || comp(*first2, first1))
				return (false);
			else if (comp(*first1, first2))
				return (true);
			++first1;
			++first2;
		}
		return (first2 != last2);
	}

	template<class BidirectionalIterator1, class BidirectionalIterator2>
	BidirectionalIterator2 copy_backward ( BidirectionalIterator1 first,
											BidirectionalIterator1 last,
											BidirectionalIterator2 result )
	{
		while (last!=first) *(--result) = *(--last);
		return result;
	}

	template<class InputIterator, class OutputIterator>
	OutputIterator copy (InputIterator first, InputIterator last, OutputIterator result)
	{
		while (first!=last)
		{
			*result = *first;
			++result; ++first;
		}
		return result;
	}

	template <class OutputIterator, class Size, class T>
	void fill_n (OutputIterator first, Size n, const T& val)
	{
		while (n>0)
		{
			*first = val;
			++first; --n;
		}
	}
}

#endif