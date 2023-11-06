#include "containers.hpp"

using namespace NM;

void map_iterators(void)
{
	std::cout << std::endl << "----\tMap iterators test\t----" << std::endl;
	map<int, int> mp;

	for (int i = 0; i < 10; i++)
		mp.insert(make_pair(i, i));
	map<int, int>::iterator it = mp.end();
	map<int, int>::reverse_iterator rit = mp.rend();
	std::cout << mp << std::endl << std::endl;
	std::cout << "begin: " << *(mp.begin()) << std::endl;
	std::cout << "end: " << *(--it) << std::endl;
	std::cout << "rbegin: " << *(mp.rbegin()) << std::endl;
	std::cout << "rend: " << *(++rit) << std::endl << std::endl;
}

void map_modifiers(void)
{
	std::cout << "----\tMap modifiers test\t----" << std::endl;
	map<int, int> mp;
	vector<pair<int, int> > v;

	std::cout << mp << std::endl;
	mp[0] = 0;
	std::cout << mp[0] << std::endl;
	for (int i = 1; i <= 10; i++)
		v.push_back(make_pair(i, i));
	mp.insert(v.begin(), v.end());
	std::cout << mp << std::endl;
	std::cout << mp[2] << std::endl;
	for (int i = 1; i < 10; i+=2)
		mp.erase(i);
	std::cout << mp << std::endl;
	std::cout << (mp.find(1) == mp.end() ? "Not found" : "Found") << std::endl;
	std::cout << (mp.find(2) == mp.end() ? "Not found" : "Found") << std::endl;
}

void map_tests(void)
{
	map_iterators();
	map_modifiers();
}