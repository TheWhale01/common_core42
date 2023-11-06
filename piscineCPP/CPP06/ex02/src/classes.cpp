#include "classes.hpp"

Base::~Base(void)
{
	return ;
}

A::A(void)
{
	return ;
}

B::B(void)
{
	return ;
}

C::C(void)
{
	return ;
}

/* FUNCTION MEMBERS */

Base *Base::generate(void)
{
	srand(time(NULL));
	int number = rand();

	if (!(number % 3))
		return (new A());
	else if (number % 3 == 1)
		return (new B());
	return (new C());
}

void Base::identify(Base *p)
{
	Base *ptr;

	ptr = dynamic_cast<A *>(p);
	if (ptr)
	{
		std::cout << "Class type: A" << std::endl;
		return ;
	}
	ptr = dynamic_cast<B *>(p);
	if (ptr)
	{
		std::cout << "Class type: B" << std::endl;
		return ;
	}
	ptr = dynamic_cast<C *>(p);
	if (ptr)
	{
		std::cout << "Class type: C" << std::endl;
		return ;
	}
}

void Base::identify(Base &p)
{
	try
	{
		Base &ref = dynamic_cast<A &>(p);
		(void)ref;
		std::cout << "Class type: A" << std::endl;
		return ;
	}
	catch (std::exception const &e){}
	try
	{
		Base &ref = dynamic_cast<B &>(p);
		(void)ref;
		std::cout << "Class type: B" << std::endl;
		return ;
	}
	catch (std::exception const &e){}
	try
	{
		Base &ref = dynamic_cast<C &>(p);
		(void)ref;
		std::cout << "Class type: C" << std::endl;
		return ;
	}
	catch (std::exception const &e){}
}