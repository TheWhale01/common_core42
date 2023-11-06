#include "Iter.hpp"

void addOne(int &nb)
{
	nb++;
}

template<typename T>
void print(T const &item)
{
	std::cout << item << std::endl;
}

int main(void)
{
	size_t length = 4;
	int *array = new int[length];

	iter(array, length, print<int>);
	std::cout << std::endl;

	iter(array, length, addOne);
	iter(array, length, print<int>);
	std::cout << std::endl;

	iter(array, length, add_one<int>);
	iter(array, length, print<int>);
	delete [] array;
	return (0);
}

// class Awesome
// {
//   public:
//     Awesome( void ) : _n( 42 ) { return; }
//     int get( void ) const { return this->_n; }
//   private:
//     int _n;
// };

// std::ostream & operator<<( std::ostream & o, Awesome const & rhs ) { o << rhs.get(); return o; }

// template< typename T >
// void print( T const & x ) { std::cout << x << std::endl; return; }

// int main() {
//   int tab[] = { 0, 1, 2, 3, 4 };  // <--- I never understood why you can't write int[] tab. Wouldn't that make more sense?
//   Awesome tab2[5];

//   iter(tab, 5, print<int>);
//   iter(tab2, 5, print<Awesome>);

//   return 0;
// }