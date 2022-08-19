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
			typedef typename ft::iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef typename ft::iterator_traits<Iterator>::value_type			value_type;
			typedef typename ft::iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename ft::iterator_traits<Iterator>::pointer				pointer;
			typedef typename ft::iterator_traits<Iterator>::reference			reference;
		protected:
			iterator_type current;
		public:
			reverse_iterator(): current() {};
			explicit reverse_iterator (iterator_type x): current(x) {};
			template <class U>
			reverse_iterator(const reverse_iterator<U>& other): current(other.current) {};

			iterator_type base() const;
			
			template <class U>
			reverse_iterator& operator=(const reverse_iterator<U>& other);
			reference operator*() const;
			reverse_iterator operator+(difference_type n) const;
			reverse_iterator& operator++();
			reverse_iterator operator++(int);
			reverse_iterator& operator+= (difference_type n);
			reverse_iterator operator-(difference_type n) const;
			reverse_iterator& operator--();
			reverse_iterator operator--(int);
			reverse_iterator& operator-= (difference_type n);
			pointer operator->() const;
			reference operator[] (difference_type n) const;
	};
									// realisation
									
		template <class Iterator>
		typename reverse_iterator<Iterator>::iterator_type reverse_iterator<Iterator>::base() const
		{
			return this->current + 1; // ?
		}

		template <class Iterator>
		template <class U>
		reverse_iterator<Iterator>& reverse_iterator<Iterator>::operator= (const reverse_iterator<U>& other)
		{
			if (*this != other)
				this->current = other.current;
			return *this;
		}

		template <class Iterator>
		typename reverse_iterator<Iterator>::reference reverse_iterator<Iterator>::operator*() const
		{
			return *(this->base() - 1);
		}

		template <class Iterator>
		reverse_iterator<Iterator> reverse_iterator<Iterator>::operator+ (difference_type n) const
		{
			return reverse_iterator(this->current - n);
		}

		template <class Iterator>
		reverse_iterator<Iterator>& reverse_iterator<Iterator>::operator++() // пре
		{
			this->current = this->current - 1;
			return *this;
		}

		template <class Iterator>
		reverse_iterator<Iterator> reverse_iterator<Iterator>::operator++(int) // пост
		{
			reverse_iterator temp = *this;
			// this->current = this->current - 1;
			// this->operator++();
			++(*this); // (*this).operator++();
			return (temp);
		}

		template <class Iterator>
		reverse_iterator<Iterator>& reverse_iterator<Iterator>::operator+=(difference_type n)
		{
			this->current = this->current - n;
			return *this;
		}

		template <class Iterator>
		reverse_iterator<Iterator> reverse_iterator<Iterator>::operator- (difference_type n) const
		{
			return reverse_iterator(this->current + n);
		}

		template <class Iterator>
		reverse_iterator<Iterator>& reverse_iterator<Iterator>::operator--() // пре
		{
			this->current = this->current + 1;
			return *this;
		}

		template <class Iterator>
		reverse_iterator<Iterator> reverse_iterator<Iterator>::operator--(int) // пост
		{
			reverse_iterator temp = *this;
			this->current = this->current + 1;
			return (temp);
		}

		template <class Iterator>
		reverse_iterator<Iterator>& reverse_iterator<Iterator>::operator-=(difference_type n)
		{
			this->current = this->current + n;
			return *this;
		}

		template <class Iterator>
		typename reverse_iterator<Iterator>::pointer reverse_iterator<Iterator>::operator->() const
		{
			return this->base() - 1;
		}

		template <class Iterator>
		typename reverse_iterator<Iterator>::reference reverse_iterator<Iterator>::operator[] (difference_type n) const
		{
			return *(this->base() - n - 1);
		}

																			// non-member
		template <class Iterator>
		bool operator== (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
		{
			// if (lhs.base() == rhs.base())
			// 	return true
			// else 
			// 	return false;
			return (lhs.base() == rhs.base());
		}

		template <class Iterator>
  		bool operator!= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
		{
			return (lhs.base() != rhs.base());
		}

		template <class Iterator>
 		bool operator<  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
		{
			return (lhs.base() < rhs.base());
		}

		template <class Iterator>
  		bool operator<= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
		{
			return (lhs.base() <= rhs.base());
		} 

		template <class Iterator>
  		bool operator>  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
		{
			return (lhs.base() > rhs.base());
		}

		template <class Iterator>
  		bool operator>= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
		{
			return (lhs.base() >= rhs.base());
		}

		template <class Iterator>
  		reverse_iterator<Iterator> operator+ (typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it)
		{
			return reverse_iterator<Iterator>(rev_it.base() - n);
		}

		template <class Iterator>
  		reverse_iterator<Iterator> operator- (typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it)
		{
			return reverse_iterator<Iterator>(rev_it.base() + n);
		}
}
