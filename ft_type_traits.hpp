#pragma once

namespace ft
{
	template <bool B, class T = void>
	class enable_if {};

	template <class T>
	class enable_if<true, T> {public: typedef T type;};

	template <class T, T v> // ?
	class integral_constant
	{
		public:
			typedef T						value_type;
			typedef integral_constant<T, v> type;
			static const T value = v;
			operator value_type() const {return value;}
	};

	typedef ft::integral_constant<bool, true> true_type;
	typedef ft::integral_constant<bool, false> false_type;

	// is_integral
	template<class T> struct is_integral: public false_type {};
	template<> struct is_integral<bool>: public true_type {};
	template<> struct is_integral<char>: public true_type {};
	template<> struct is_integral<signed char>: public true_type {};
	template<> struct is_integral<unsigned char>: public true_type {};
	template<> struct is_integral<wchar_t>: public true_type {};
	template<> struct is_integral<char16_t>: public true_type {};
	template<> struct is_integral<char32_t>: public true_type {};
	template<> struct is_integral<short>: public true_type {};
	template<> struct is_integral<unsigned short>: public true_type {};
	template<> struct is_integral<int>: public true_type {};
	template<> struct is_integral<unsigned int>: public true_type {};
	template<> struct is_integral<long>: public true_type {};
	template<> struct is_integral<unsigned long>: public true_type {};
	template<> struct is_integral<long long>: public true_type {};
	template<> struct is_integral<unsigned long long>: public true_type {};
}

