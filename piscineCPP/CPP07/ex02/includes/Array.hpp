#pragma once
#include <iostream>

template<typename T>
class Array
{
	public:
		Array(void): _data(NULL), _size(0) {}
		Array(unsigned int n): _data(new T[n]()), _size(n) {}
		Array(Array const &rhs): _data(NULL), _size(0) {*this = rhs;}
		~Array(void) {delete [] this->_data;}

		class IndexOutOfRangeException: public std::exception
		{
			public:
				virtual const char *what(void) const throw()
				{
					return ("Index out of range.");
				}
		};
		
		Array &operator=(Array const &rhs)
		{
			if (this == &rhs)
				return (*this);
			if (this->_size > 0)
				delete [] this->_data;
			this->_size = rhs._size;
			this->_data = new T[rhs._size]();
			for (size_t i = 0; i < this->_size; i++)
				this->_data[i] = rhs._data[i];
			return (*this);
		}

		T &operator[](int const index)
		{
			if (index < 0 || (size_t)index >= this->_size)
				throw (Array::IndexOutOfRangeException());
			return (_data[index]);
		}

		size_t size(void) const {return (this->_size);}

	private:
		T *_data;
		size_t _size;
};

template<typename T>
std::ostream &operator<<(std::ostream &stream, Array<T> tab)
{
	stream << "[";
	for (size_t i = 0; i < tab.size(); i++)
		stream << tab[i] << (i < tab.size() - 1 ? ", " : "");
	stream << "]";
	return (stream);
}