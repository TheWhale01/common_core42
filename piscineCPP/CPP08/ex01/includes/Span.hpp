#pragma once
#include <list>
#include <vector>
#include <limits>
#include <iostream>
#include <algorithm>
#include <exception>
#include <bits/stdc++.h>

class Span
{
	public:
		Span(void);
		Span(size_t N);
		Span(Span const &rhs);
		~Span(void);

		Span &operator=(Span const &rhs);

		int	shortestSpan(void) const;
		int longestSpan(void) const;
		void addNumber(int nb);

		template<class InputIterator>
		void iterAdd(InputIterator begin, InputIterator end)
		{
			size_t size;

			size = 0;
			for (InputIterator it = begin; it != end; it++)
				size++;
			if (size && size + _data.size() > _N)
				throw (SpanFullException());
			_data.insert(_data.end(), begin, end);
		}

		std::vector<int> const &getData(void) const {return (_data);}

		class DistanceNotFoundException: public std::exception
		{
			public:
				virtual const char *what(void) const throw() {return ("Distance not found.");}
		};

		class SpanFullException: public std::exception
		{
			public:
				virtual const char *what(void) const throw() {return ("Span full.");}
		};

	private:
		size_t _N;
		std::vector<int> _data;
};

std::ostream &operator<<(std::ostream &stream, Span const &sp);