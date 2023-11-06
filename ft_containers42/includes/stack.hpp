#ifndef __STACK_HPP__
# define __STACK_HPP__

#include "vector.hpp"

namespace ft
{
	template<class T, class Container = ft::vector<T> >
	class stack
	{
		public:
			typedef T value_type;
			typedef Container container_type;
			typedef size_t size_type;

			explicit stack(container_type const &ctnr = container_type()): c(ctnr) {}
			virtual ~stack(void) {}

			bool empty(void) const {return (c.empty());}

			size_type size(void) const {return (c.size());}

			value_type &top(void) {return (c.back());}
			value_type const &top(void) const {return (c.back());}

			void push(value_type const &val) {c.push_back(val);}

			void pop(void) {c.pop_back();}

			template<class A, class C>
			friend bool operator==(stack<A, C> const &lhs, stack<A, C> const &rhs);

			template<class A, class C>
			friend bool operator<(stack<A, C> const &lhs, stack<A, C> const &rhs);

		protected:
			container_type c;
	};

	template<class A, class C>
	bool operator==(stack<A, C> const &lhs, stack<A, C> const &rhs) {return ((lhs.c) == (rhs.c));}

	template<class A, class C>
	bool operator!=(stack<A, C> const &lhs, stack<A, C> const &rhs) {return (!(lhs == rhs));}

	template<class A, class C>
	bool operator<(stack<A, C> const &lhs, stack<A, C> const &rhs) {return (lhs.c < rhs.c);}

	template<class A, class C>
	bool operator>(stack<A, C> const &lhs, stack<A, C> const &rhs) {return (rhs < lhs);}

	template<class A, class C>
	bool operator<=(stack<A, C> const &lhs, stack<A, C> const &rhs) {return (!(rhs < lhs));}

	template<class A, class C>
	bool operator>=(stack<A, C> const &lhs, stack<A, C> const &rhs) {return (!(lhs < rhs));}
}

#endif