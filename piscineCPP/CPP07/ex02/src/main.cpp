#include "Array.hpp"

int main(void)
{
	Array<int> tab(4);
	Array<int> cpy;

	std::cout << "---------DEEP COPY---------" << std::endl;
	std::cout << "Original: " << tab << std::endl << "Copy: " << cpy << std::endl;
	for (size_t i = 0; i < 4; i++)
		tab[i] = i;
	cpy = tab;
	std::cout << "Original: " << tab << std::endl << "Copy: " << cpy << std::endl;
	cpy[2] = 123;
	std::cout << "Original: " << tab << std::endl << "Copy: " << cpy << std::endl;
	std::cout << std::endl;
	std::cout << "---------ACCESS OPERAND---------" << std::endl;
	try {std::cout << tab[123] << std::endl;}
	catch (std::exception const &e) {std::cerr << e.what() << std::endl;}
	return (0);
}