#pragma once
#include <list>
#include <stack>
#include <iostream>

template<class T, class Container = std::deque<T> >
class MutantStack: public std::stack<T>
{
	public:
		MutantStack(void) {}
		MutantStack(MutantStack const &rhs) {*this = rhs;}
		virtual ~MutantStack(void) {}

		typedef typename Container::iterator iterator;
		typedef typename Container::const_iterator const_iterator;
		typedef typename Container::reverse_iterator reverse_iterator;
		typedef typename Container::const_reverse_iterator const_reverse_iterator;

		MutantStack &operator=(MutantStack const &rhs)
		{
			if (this == &rhs)
				return (*this);
			static_cast< std::stack<T> >(*this) = static_cast< std::stack<T> >(rhs);
			return (*this);
		}

		iterator begin(void) {return (this->c.begin());}
		iterator end(void) {return (this->c.end());}
		const_iterator begin(void) const {return (this->c.begin());}
		const_iterator end(void) const {return (this->c.end());}
		reverse_iterator rbegin(void) {return (this->c.rbegin());}
		reverse_iterator rend(void) {return (this->c.rend());}
		const_reverse_iterator rbegin(void) const {return (this->c.rbegin());}
		const_reverse_iterator rend(void) const {return (this->c.rend());}
};