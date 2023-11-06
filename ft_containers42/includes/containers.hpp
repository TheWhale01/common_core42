#ifndef __CONTAINERS_HPP__
# define __CONTAINERS_HPP__

#ifndef NM
# define NM ft
# include "map.hpp"
# include "set.hpp"
# include "stack.hpp"
# include "vector.hpp"
#else
# include <map>
# include <set>
# include <stack>
# include <vector>
#endif

# include <iostream>

template<class T>
std::ostream &operator<<(std::ostream &stream, NM::vector<T> const &v)
{
	typename NM::vector<T>::const_iterator it;

	stream << "[";
	for (it = v.begin(); it != v.end(); it++)
		stream << *it << (it + 1 == v.end() ? "" : ", ");
	stream << "]";
	return (stream);
}

template<class T1, class T2>
std::ostream &operator<<(std::ostream &stream, NM::pair<T1, T2> const &pr)
{
	stream << "(" << pr.first << ", " << pr.second << ")";
	return (stream);
}

#if !defined(USING_FT) && !defined(USING_STD)
template<class T1, class T2>
std::ostream &operator<<(std::ostream &stream, NM::map<T1, T2> const &mp)
{
	typename NM::map<T1, T2>::const_iterator it;

	stream << "[";
	for (it = mp.begin(); it != mp.end(); it++)
		stream << *it;
	stream << "]";
	return (stream); 
}

template<class T>
std::ostream &operator<<(std::ostream &stream, NM::set<T> const &st)
{
	typename NM::set<T>::const_iterator it;

	stream << "[";
	for (it = st.begin(); it != st.end(); it++)
		stream << *it << (*it != *st.rbegin() ? ", " : "");
	stream << "]";
	return (stream);
}

template<class T>
std::ostream &operator<<(std::ostream &stream, NM::stack<T> st)
{
	while (st.size())
	{
		stream << "| " << st.top() << " |" << std::endl;
		st.pop();
	}
	return (stream);
}

// Tester used:
// https://github.com/mli42/containers_test
// https://github.com/Mazoise/42TESTERS-CONTAINERS.git
// https://github.com/JCluzet/42_container_tester.git

//Tests
void test42(int argc, char** argv);
void vector_tests(void);
void map_tests(void);
void stack_tests(void);

#endif
#endif