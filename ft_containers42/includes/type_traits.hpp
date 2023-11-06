#ifndef __TYPE_TRAITS_HPP__
# define __TYPE_TRAITS_HPP__

namespace ft
{
	template<bool B, class T = void>
	struct enable_if {};

	template<class T>
	struct enable_if<true, T> {typedef T type;};

	template<class T, bool v>
	struct integral_constant
	{
		static const bool value = v;
		typedef T value_type;
		typedef integral_constant type;
		operator value_type() const {return value;}
	};

	template<class T>
	struct is_integral: public ft::integral_constant<T, false> {};
	template<> struct is_integral<bool>: public ft::integral_constant<bool, true> {};
	template<> struct is_integral<char>: public ft::integral_constant<char, true> {};
	template<> struct is_integral<wchar_t>: public ft::integral_constant<wchar_t, true> {};
	template<> struct is_integral<signed char>: public ft::integral_constant<signed char, true> {};
	template<> struct is_integral<short int>: public ft::integral_constant<short int, true> {};
	template<> struct is_integral<int>: public ft::integral_constant<int, true> {};
	template<> struct is_integral<long int>: public ft::integral_constant<long int, true> {};
	template<> struct is_integral<long long int>: public ft::integral_constant<long long int, true> {};
	template<> struct is_integral<unsigned char>: public ft::integral_constant<unsigned char, true> {};
	template<> struct is_integral<unsigned short int>: public ft::integral_constant<unsigned short int, true> {};
	template<> struct is_integral<unsigned int>: public ft::integral_constant<unsigned int, true> {};
	template<> struct is_integral<unsigned long int>: public ft::integral_constant<unsigned long int, true> {};
	template<> struct is_integral<unsigned long long int>: public ft::integral_constant<unsigned long long int, true> {};
}

#endif