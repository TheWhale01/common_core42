#include "easyfind.hpp"

int main(void)
{
	std::vector<int> v;

	for (int i = 0; i < 4; i++)
		v.push_back(i * 2);
	std::cout << v << std::endl;
	try
	{
		std::cout << easyfind(v, 3) << std::endl;
	}
	catch (std::exception const &e)
	{
		std::cerr << e.what() << std::endl;
	}
	try
	{
		std::cout << easyfind(v, 4) << std::endl;
	}
	catch (std::exception const &e)
	{
		std::cerr << e.what() << std::endl;
	}
	return (0);
}