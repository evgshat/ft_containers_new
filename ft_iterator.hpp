#pragma once

#include <stddef.h>

namespace ft
{
	class input_iterator_tag {};
	class output_iterator_tag {};
	class forward_iterator_tag       : public input_iterator_tag {};
	class bidirectional_iterator_tag : public forward_iterator_tag {};
	class random_access_iterator_tag : public bidirectional_iterator_tag {};

	template<class Iterator>
	class iterator_traits
	{
		typedef ptrdiff_t difference_type;
		typedef typename Iterator::value_type value_type;
		typedef typename Iterator::pointer pointer;
		typedef typename Iterator::reference reference;
		typedef typename Iterator::iterator_category iterator_category;
	};

	template<class T>
	class iterator_traits<T*>
	{
		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;
		typedef random_access_iterator_tag iterator_category;
	};

	template<class Iterator>
	class reverse_iterator : public std::iterator
													<
													ft::iterator_traits<Iterator>::iterator_category,
													ft::iterator_traits<Iterator>::value_type,
													ft::iterator_traits<Iterator>::difference_type,
													ft::iterator_traits<Iterator>::pointer;
													ft::iterator_traits<Iterator>::reference
													>
	{
		
	};
}
