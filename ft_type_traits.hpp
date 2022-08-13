#pragma once

#include <type_traits>

namespace ft
{
	template <class> // что эт значит
	struct __void_t
	{
		typedef void type;
	};

	template<bool B, class T = void>
	struct enable_if {};

	template <class T>
	struct enable_if<true, T>
	{
		typedef T type;
	};

	template <class T, T v> // что за синтаксис...
	struct integral_constant
	{
		static const T value = v;
		typedef T value_type;
		typedef integral_constant<T, v> type;
		operator value_type() const
		{
			return (value);
		}
	};

	typedef integral_constant<bool, true> true_type;

	typedef integral_constant<bool, false> false_type;

	// че за фигня......
	template <class T> struct is_integral: public false type {};
	template <> struct is_integral<bool>: public true_type {}; // что за синтаксис...
	template <> struct is_integral<char>: public true_type {};
	template <> struct is_integral<signed char>: public true_type {};
	template <> struct is_integral<unsigned char>: public true_type {};
	template <> struct is_integral<wchar_t>: public true_type {};
	template <> struct is_integral<char16_t>: public true_type {};
	template <> struct is_integral<char32_t>: public true_type {};
	template <> struct is_integral<short>: public true_type {};
	template <> struct is_integral<unsigned short>: public true_type {};
	template <> struct is_integral<int>: public true_type {};
	template <> struct is_integral<unsigned int>: public true_type {};
	template <> struct is_integral<long>: public true_type {};
	template <> struct is_integral<unsigned long>: public true_type {};
	template <> struct is_integral<long long>: public true_type {};
	template <> struct is_integral<unsigned long long>: public true_type {};
}

