//                                           полезная инфа:
// 1. pointer pend указывает не на последний эл-т в векторе, а на область за ним

//                                              вопросы:
// заяем функция clear, если есть деструктор? ответ: используется для очищения массива, но классом можно продолжить пользоаватьсч. а если вызвать деструктор - то придется новый класс делать
// допустим, хочу вызвать reserve или size, как понять, this.size  или rhis->size ? путаюсь ответ: this - это указатель сам на себя, поэтому стрелочка. по остальным переменным смотреть, чем они явл (указатель или нет)
// push_back(const T& value) - есть ли разница, использовать T или value_type?
//вместо int лучше size_type?
// почему в for лучше ++i, чем i++?  в for же они вроде работют одинаково. или нет????!
// ответ:
    //  // delete after ++
    //  template <class T, class Allocator>
    //  int vector<T, Allocator>::operator++(int n)
    //  {
    //      int temp = this->i;
    //      this->i = this->i + 1;
    //      return temp;
    //  }

    // // delete before ++
    //  template <class T, class Allocator>
    //  int vector<T, Allocator>::operator++()
    //  {
    //     this->i = this->i + 1;
    //     return this->i;
    //  }
// поле private - allocator_type	alloc; // 

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
            explicit vector (const allocator_type& Alloc = allocator_type()): pbegin(0), pend(0), pcapacity(0), alloc(Alloc) {}; // уже реализован
            explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& Alloc = allocator_type());
            template <class InputIterator> vector (
                        typename ft::enable_if<!is_integral<InputIterator>::value, InputIterator>::type first,
                        InputIterator last, const allocator_type& alloc = allocator_type());
            vector (const vector& x);
            ~vector ();
            vector& operator= (const vector& x);
            size_type size() const;
            bool empty() const;
            size_type max_size() const;
            size_type capacity() const;
            void reserve(size_t n);
            // assign
            void assign(size_type count, const T& value);
            template <class InputIterator> 
            void assign (InputIterator first, InputIterator last);
            void clear();
            void push_back(const value_type& value);
            allocator_type get_allocator() const;
    };

                                            // реализация функций
                                            // constructions
    template<class T, class Allocator>
    vector<T, Allocator>::vector(size_type n, const value_type& val, const allocator_type& Alloc): pbegin(0), pend(0), pcapacity(0), alloc(Alloc)
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

                                            //
    template <class T, class Allocator> // перепроверить реализацию
    template <class InputIterator>
    vector<T, Allocator>::vector (
        typename ft::enable_if<!is_integral<InputIterator>::value, InputIterator>::type first,
        InputIterator last, const allocator_type& Alloc): pbegin(0), pend(0), pcapacity(0), alloc(Alloc)
    {
        InputIterator temp1 = first;
        InputIterator temp2 = first;
        // first, first++ ... last
        size_type size = 0;
        for (; temp1 < last; temp1++)
             size++;
        this->alloc.allocate(size, this->pbegin); 
        for (; temp2 < last; temp2++)
            this->alloc.construct(this->pbegin, temp2); 
    }
                                     //
    template <class T, class Allocator> // перепроверить реализацию
    vector<T, Allocator>::vector (const vector& x): pbegin(0), pend(0), pcapacity(0), alloc(x.alloc)
    {
        size_type new_size = x.size();
        this->alloc.allocate(new_size, this->pbegin);
        for (size_type n = 0; n < new_size; n++, this->pend++)
            this->alloc.construct(this->pend, *(x.pbegin + n));
        this->pcapacity = this->pend;
    }
                                            // destructor
    template <class T, class Allocator>
    vector<T, Allocator>::~vector()
    {
        for (pointer temp = this->pbegin; temp < this->pcapacity; temp++)
            this->alloc.destroy(temp);
        this->alloc.deallocate(this->pbegin, this->capacity());
    }    
                                            // operator=
    template <class T, class Allocator>
    vector<T, Allocator>& vector<T, Allocator>::operator=(const vector& other)
    {
        size_t new_size = other.size();
        if (this != &other)
        {
            for (pointer temp = this->pbegin; temp < this->pcapacity; temp++)
                this->alloc.destroy(temp);
            this->allocate.deallocate(this->pbegin, this->capacity());
            this->pbegin = this->pend = this->pcapacity = 0;
            this->alloc = other.alloc;
            
            this->alloc.allocate(other.size(), this->pbegin);
            this->pend = this->pcapacity = this->pbegin + new_size;
            for (pointer temp = this->pbegin; temp< this->pend; temp++)
                this->alloc.construct(temp, *temp);
        }
        return *this;
     }

                                            // fill_assign
    template <class T, class Allocator>
    void vector<T, Allocator>::assign(size_type count, const T& value)
    {
        this->clear();
        for (int i = 0; i < count; ++i)
            this->push_back(value);
    }
                                            // range_assign
    template <class T, class Allocator>
    template <class InputIterator>
    void vector<T, Allocator>::assign(InputIterator first, InputIterator last)
    {
        this->clear();
        for (; first != last; first++)
            this->push_back(*first);
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

    template<class T, class Allocate>
    void vector<T, Allocate>::clear()
    {
        pointer temp = this->pbegin;
        for (; temp < pend; temp++)
        {
            alloc.destroy(temp);
        }
        alloc.deallocate(this->pbegin, this->capacity); // ? 
        this->pbegin = this->pend = this->capacity = 0;
    }

    template<class T, class Allocator>
    void vector<T, Allocator>::push_back(const value_type& value)
    {
        size_type for_new_capacity = this->pcapacity - this->pbegin;
        if (this->pend == this->pcapacity) // может ли каким-то раком pend быть больше capacity?
            this->reserve(2 * (for_new_capacity > 0 ? for_new_capacity : 1)); // если for_new_capacity > 0, то подставляем for_new_capacity, иначе - подставляем 1
        this->alloc.construct(this->pend, value); // надо прибавлять capacity?
        ++this->pend;
    }

    template<class T, class Allocator>
    typename vector<T, Allocator>::allocator_type
    vector<T, Allocator>::get_allocator() const
    {
        return allocator_type(this->alloc); // allocator_type - конструктор копирования аллокатора, allocate - приватная переменная
    }
}
#endif