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
		public:
			typedef ptrdiff_t difference_type;
			typedef typename Iterator::value_type value_type;
			typedef typename Iterator::pointer pointer;
			typedef typename Iterator::reference reference;
			typedef typename Iterator::iterator_category iterator_category;
	};

	template<class T>
	class iterator_traits<T*>
	{
		public:
			typedef ptrdiff_t difference_type;
			typedef T value_type;
			typedef T* pointer;
			typedef T& reference;
			typedef random_access_iterator_tag iterator_category;
	};

	template<class Iterator>
	class reverse_iterator : public std::iterator<typename ft::iterator_traits<Iterator>::iterator_category,
												  typename ft::iterator_traits<Iterator>::value_type,
												  typename ft::iterator_traits<Iterator>::difference_type,
												  typename ft::iterator_traits<Iterator>::pointer,
												  typename ft::iterator_traits<Iterator>::reference>
	{
		public:
			typedef Iterator	iterator_type;
			// ft::iterator_traits<Iter> поч в <> - Iterator?
			typedef typename ft::iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef typename ft::iterator_traits<Iterator>::value_type			value_type;
			typedef typename ft::iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename ft::iterator_traits<Iterator>::pointer				pointer;
			typedef typename ft::iterator_traits<Iterator>::reference			reference;
		public:
			iterator_type current; // = this->base(); - ?
		public:
			reverse_iterator(): current() {};
			explicit reverse_iterator (iterator_type x): current(x) {};
			template <class U>
			reverse_iterator(const reverse_iterator<U>& other): current(other.current) {};

			iterator_type base() const;
			
			template <class U>
			reverse_iterator& operator= (const reverse_iterator<U>& other);
	};
									// realisation
									
		template <class Iterator>
		typename reverse_iterator<Iterator>::iterator_type reverse_iterator<Iterator>::base() const
		{
			// return this->current - 1;//
			return this->current;
		}

		template <class Iterator>
		template <class U>
		reverse_iterator<Iterator>& reverse_iterator<Iterator>::operator= (const reverse_iterator<U>& other)
		{
			if (*this != other)
				this->current = other.current;
			return *this;
		}

}
