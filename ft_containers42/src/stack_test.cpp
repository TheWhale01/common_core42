#include "containers.hpp"

using namespace NM;

void stack_tests(void)
{
	std::cout << "----\tStack tests\t----" << std::endl;
	stack<int> st;

	std::cout << "empty: " << std::boolalpha << st.empty() << std::endl;
	std::cout << "inserting 10 elements..." << std::endl;

	for (int i = 0; i < 10; i++)
		st.push(i);
	std::cout << st << std::endl;
	std::cout << "empty: " << std::boolalpha << st.empty() << std::endl;
	std::cout << "size: " << st.size() << std::endl;
	std::cout << "top: " << st.top() << std::endl;

	std::cout << std::endl << "Removing 3 elements..." << std::endl;
	for (int i = 0; i < 3; i++)
		st.pop();
	std::cout << st << std::endl;
	std::cout << "empty: " << std::boolalpha << st.empty() << std::endl;
	std::cout << "size: " << st.size() << std::endl;
	std::cout << "top: " << st.top() << std::endl;
}