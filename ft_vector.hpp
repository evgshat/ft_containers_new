// полезная инфа
// 1. pointer pend указывает не на последний эл-т в векторе, а на область за ним

#ifndef FT_VECTOR_HPP
#define FT_VECTOR_HPP

#include "ft_containers.hpp"

namespace ft
{
    template <class T, class Allocator = std::allocator<T> >
    class vector
    {
        public:
            typedef T                                                       value_type;
            typedef Allocator                                               allocator_type;
            typedef typename allocator_type::reference                      reference;
            typedef typename allocator_type::const_reference                const_reference;
            typedef typename allocator_type::pointer                        pointer;
            typedef typename allocator_type::const_pointer                  const_pointer; 
            typedef typename std::size_t                                    size_type;
            typedef typename ft::iterator_traits<pointer>::pointer          iterator;
            typedef typename ft::iterator_traits<const_pointer>::pointer    const_iterator;
            
        private:
				pointer			pbegin;
				pointer			pend;
				pointer			pcapacity;
				allocator_type	alloc;
        public:
                
            explicit vector (const allocator_type& Alloc = allocator_type()): pbegin(0), pend(0), pcapacity(0), alloc(Alloc) {};
            explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& Alloc = allocator_type());
            template <class InputIterator>
                     vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());
                     vector (const vector& x);
        
            // ~vector ();
                    
            vector& operator= (const vector& x);

            size_type size() const;
            bool empty() const;
            size_type max_size() const;
            size_type capacity() const;
            void reserve(size_t n);
    };

                // реализация функций
                                            // constructions
    template<class T, class Allocator>
    vector<T, Allocator>::vector(size_type n, const value_type& val, const allocator_type& Alloc): alloc(Alloc)
    {
        if (n > this->max_size())
            throw std::length_error("New value more than max size");
        this->pbegin = this->alloc.allocate(n);
        int i = 0;
        for(; n != 0; n--)
        {
            this->alloc.construct(this->pbegin + i, val);
            i++;
        }
        this->pend = this->pcapacity = this->pbegin + i;
    }

                                            // capacity
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
    typename vector<T, Allocator>::size_type vector<T, Allocator>::max_size() const // перепроверить реализацию
    {
        return this->alloc.max_size(); // можно ли оставить так?
        // return std::min<T>(this->alloc.max_size(), std::numeric_limits<int>::max()); // у Дани: std::numeric_limits<difference_type>::max() - поч?
    }

    template <class T, class Allocator>
    typename vector<T, Allocator>::size_type vector<T, Allocator>::capacity() const // перепроверить реализацию
    {
        return static_cast<size_type>(this->pcapacity - this->pbegin);
    }

    template <class T, class Allocator> // у Дани вообще не так, перепроверить, у него какой-то vdeallocate непонятный
    void vector<T, Allocator>::reserve(size_t n) // сначала надо походу конструктор сделать, чтобы понять, каким раком выделяется память
    {
        if (n > this->max_size() )
            throw std::length_error("New value more than max size");
        else if (n > this->capacity() )
        {
            pointer new_pbegin;
            size_t size_for_construct = this->size();
            size_t size_for_destruct = size_for_construct;
            size_t size_for_capacity = size_for_construct;

            new_pbegin = this->alloc.allocate(n);
            int i = 0;
            for (; size_for_construct != 0; size_for_construct--)
            {
                this->alloc.construct(new_pbegin + i, *(this->pbegin + i));
                i++;
            }
            for (; size_for_destruct != 0; size_for_destruct--)
                this->alloc.destroy(this->pbegin + size_for_destruct);
            this->alloc.deallocate(this->pbegin, this->capacity());
            this->pbegin = new_pbegin;
            this->pend = new_pbegin + size_for_capacity;
            this->pcapacity = new_pbegin + n; 
        }
    }

}
#endif