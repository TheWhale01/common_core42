#include "containers.hpp"

using namespace NM;

template<class T>
static void print(vector<T> const &v)
{
	std::cout << "size: " << v.size() << std::endl;
	std::cout << "capacity: " << v.capacity() << std::endl;
	std::cout << "content: " << v << std::endl << std::endl;
}

void vect_iterators(void)
{
	std::cout << "----\tVector iterators test\t----" << std::endl;
	vector<int> v;

	print<int>(v);
	std::cout << "inserting 10 elements..." << std::endl;
	for (int i = 0; i < 10; i++)
		v.push_back(i);
	print<int>(v);
	std::cout << "begin: " << *(v.begin()) << std::endl;
	std::cout << "end: " << *(v.end() - 1) << std::endl;
	std::cout << "rbegin: " << *(v.rbegin()) << std::endl;
	std::cout << "rend: " << *(v.rend() - 1) << std::endl;
}

void vect_capacity(void)
{
	std::cout << "----\tVector capacity test\t----" << std::endl;
	vector<int> v;

	for (int i = 0; i < 10; i++)
		v.push_back(i);
	print<int>(v);
	v.erase(v.begin());
	v.erase(v.end() - 1);
	v.erase(v.begin() + 3);
	print<int>(v);

	v.resize(10, 42);
	print<int>(v);

	v.reserve(20);
	print<int>(v);

	v.reserve(5);
	print<int>(v);

	std::cout << "empty: " << std::boolalpha << v.empty() << std::endl;
	v.clear();
	std::cout << "empty: " << std::boolalpha << v.empty() << std::endl;
	print<int>(v);
}

void vect_access(void)
{
	std::cout << "----\tVector access test\t----" << std::endl;
	vector<int> v;

	for (int i = 0; i < 10; i++)
		v.insert(v.end(), i);
	print<int>(v);

	std::cout << "operator []: " << v[0] << std::endl;
	std::cout << "at(): " << v.at(0) << std::endl << std::endl;

	std::cout << "operator []: " << v[v.size() - 1] << std::endl;
	std::cout << "at(): " << v.at(v.size() - 1) << std::endl << std::endl;

	// std::cout << "operator []: " << v[-1] << std::endl; // Invalid read (normal)
	try {std::cout << "at(-1): " << v.at(-1) << std::endl << std::endl;}
	catch (std::exception const &e) {std::cerr << "Error caught: " << e.what() << std::endl << std::endl;}

	// std::cout << "operator []: " << v[v.size()] << std::endl; // Invalid read (normal)
	try {std::cout << "at(v.size()): " << v.at(v.size()) << std::endl;}
	catch (std::exception const &e) {std::cerr << "Error caught: " << e.what() << std::endl << std::endl;}

	std::cout << "front(): " << v.front() << std::endl;
	std::cout << "back(): " << v.back() << std::endl << std::endl;
}

void vect_modifiers(void)
{
	std::cout << "----\tVector modifiers test\t----" << std::endl;
	vector<int> base(5, 42);
	vector<int> cpy;

	std::cout << "base vector: " << std::endl;
	print<int>(base);
	cpy.assign(base.begin(), base.end());
	std::cout << "cpy vector (iterator range): " << std::endl;
	print<int>(cpy);
	cpy.clear();
	cpy.assign(5, 42);
	std::cout << "base vector: " << std::endl;
	print<int>(base);
	std::cout << "cpy vector (nb_values): " << std::endl;
	print<int>(cpy);

	std::cout << "poping 3 elements..." << std::endl;
	for (int i = 0; i < 3; i++)
		cpy.pop_back();
	std::cout << "cpy: " << std::endl;
	print<int>(cpy);
	
	std::cout << "swap: " << std::endl;
	cpy.swap(base);
	std::cout << "cpy: " << std::endl;
	print<int>(cpy);
	std::cout << "base: " << std::endl;
	print<int>(base);

	std::cout << "insert (iterator range) on base: " << std::endl;
	base.insert(base.end(), cpy.begin(), cpy.end());
	print<int>(base);
}

void vect_op(void)
{
	std::cout << "----\tVector relational operators test\t----" << std::endl;
	vector<int> v1;
	vector<int> v2;

	for (int i = 0; i < 10; i++)
	{
		v1.push_back(i);
		v2.push_back(i * 2);
	}

	print<int>(v1);
	print<int>(v2);

	std::cout << " == " << std::boolalpha << (v1 == v2) << std::endl;
	std::cout << " != " << std::boolalpha << (v1 != v2) << std::endl;
	std::cout << " < " << std::boolalpha << (v1 < v2) << std::endl;
	std::cout << " > " << std::boolalpha << (v1 > v2) << std::endl;
	std::cout << " <= " << std::boolalpha << (v1 <= v2) << std::endl;
	std::cout << " >= " << std::boolalpha << (v1 >= v2) << std::endl;
}

void vector_tests(void)
{
	std::cout << std::endl;
	vect_iterators();
	std::cout << std::endl;
	vect_capacity();
	vect_access();
	vect_modifiers();
	vect_op(); 
}