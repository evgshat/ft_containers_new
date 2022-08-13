#ifndef FT_VECTOR_HPP
#define FT_VECTOR_HPP

#include <vector>

namespace ft
{
    template <class T, class Alloc = std::allocator<T> >
    class vector
    {
        public:
            typedef T       value_type;
            typedef Alloc   allocator_type;
            typedef allocator_type::reference       reference;
            typedef allocator_type::const_reference const_reference;
            typedef allocator_type::pointer         pointer;
            typedef allocator_type::const_pointer   const_pointer;
            // дописать итераторы
        private:
				pointer			pbegin;
				pointer			pend;
				pointer			pcapacity;
				allocator_type	alloc;
        public:
                    // конструкторы
                // default (1)
            explicit vector (const allocator_type& alloc = allocator_type());
                // fill (2)
            explicit vector(size_type n, const value_type& val = value_type(),
                            const allocator_type& alloc = allocator_type());
                // range (3)
            template <class InputIterator>
                vector (InpuIterator first, InputIterator last,
                        const allocator_type& alloc = allocator_type());
                // copy (4)
            vector (const vector& x);
                    // деструктор
            ~vector ();
                    // operator=
            vector& operator= (const vector& x);

                    // capacity
            size_type size() const;

                                    // реализация
                                    // конструкторы
            // copy(4)
            vector (const vector& x);
                                    // capacity
            size_type size() const
            {
                pointer temp;
                size_type res = 0;
                temp = this->pbegin;
                for (; temp <= this->pend; temp++)
                    res++;
                return (res);
            }                  


    }

} //end of namespace ft

#endif