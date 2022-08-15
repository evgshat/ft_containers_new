// полезная инфа
// 1. pointer pend указывает не на последний эл-т в векторе, а на область за ним

#ifndef FT_VECTOR_HPP
#define FT_VECTOR_HPP

#include "ft_containers.hpp"

namespace ft
{
    template <class T, class Alloc = std::allocator<T> >
    class vector
    {
        public:
            typedef T       value_type;
            typedef Alloc   allocator_type;
            typedef typename allocator_type::reference       reference;
            typedef typename allocator_type::const_reference const_reference;
            typedef typename allocator_type::pointer         pointer;
            typedef typename allocator_type::const_pointer   const_pointer;
            typedef typename std::size_t size_type;
            // дописать итераторы
        private:
				pointer			pbegin;
				pointer			pend;
				pointer			pcapacity;
				allocator_type	alloc;
        public:
                
            explicit vector (const allocator_type& alloc = allocator_type()): pbegin(0), pend(0), pcapacity(0), alloc(alloc) {};
            explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type());
            template <class InputIterator>
                     vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());
                     vector (const vector& x);
        
            // ~vector ();
                    
            vector& operator= (const vector& x);

            size_type size() const;
            bool empty() const;
            size_type max_size() const;
    };

                // реализация функций
    template <class T, class Allocator>
    typename vector<T, Allocator>::size_type vector<T, Allocator>::size() const // перепроверить реализацию
    {
        pointer temp = this->pbegin;
        size_type res = 0;
        for (; temp < this->pend; temp++)
            res++;
        return (res);
    }

    template <class T, class Allocator>
    bool vector<T, Allocator>::empty() const // перепроверить реализацию
    {
        if (this->pbegin == 0)
            return 1;
        else 
            return 0;
    }

    template <class T, class Allocator>
    typename vector<T, Allocator>::size_type vector<T, Allocator>::max_size() const
    {
        // попробовать максимально аллоцировать память и посмотреть, сколько вернется
        // как аллоцировать память
    }

}
#endif