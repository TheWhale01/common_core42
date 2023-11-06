#include "classes.hpp"

void test_random(void)
{
	Base obj;
	Base *ptr = obj.generate();

	std::cout << "ptr: ";
	obj.identify(ptr);
	std::cout << "ref: ";
	obj.identify(*ptr);
	delete ptr;
}

void test_a(void)
{
	Base *ptr = new A();

	std::cout << "ptr: ";
	ptr->identify(ptr);
	std::cout << "ref: ";
	ptr->identify(*ptr);
	delete ptr;
}

void test_b(void)
{
	Base *ptr = new B();

	std::cout << "ptr: ";
	ptr->identify(ptr);
	std::cout << "ref: ";
	ptr->identify(*ptr);
	delete ptr;
}

void test_c(void)
{
	Base *ptr = new C();

	std::cout << "ptr: ";
	ptr->identify(ptr);
	std::cout << "ref: ";
	ptr->identify(*ptr);
	delete ptr;
}

int main(void)
{
	test_random();
	std::cout << std::endl;
	test_a();
	std::cout << std::endl;
	test_b();
	std::cout << std::endl;
	test_c();
	return (0);
}