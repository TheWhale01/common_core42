#include "MutantStack.hpp"

int main(void)
{
	size_t stack_len = 10;
	MutantStack<int> mstack;

	for (size_t i = 0; i < stack_len; i++)
		mstack.push(i);
	std::cout << "Stack content:" << std::endl;
	for (MutantStack<int>::iterator i = mstack.begin(); i != mstack.end(); i++)
		std::cout << "\t" << *i << std::endl;
	return (0);
}