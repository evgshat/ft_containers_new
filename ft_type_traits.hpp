#pragma once

namespace ft
{
	template <bool B, class T = void>
	class enable_if {};

	template <class T>
	class enable_if<true, T> {typedef T type};

	template <class T, T v> // ?
	class integral_constant
	{
		public:
			typedef T						value_type;
			typedef integral_constant<T, v> type;

			static const T value = v;

			operator value_type() const
			{
				return value;
			}
	};

	typedef ft::integral_constant<bool, true> true_type;
	typedef ft::integral_constant<bool, false> false_type;

	template <class T>
	class is_integral : public ft::integral_const // ?
	{
		public:
			typedef bool										value_type;
			typedef typename ft::integral_constant<bool, type>  type;

			static bool value;

			operator value_type()
			{
				return value;
			}	
	};
}