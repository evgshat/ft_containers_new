#ifndef FT_VECTOR_HPP
#define FT_VECTOR_HPP

#include <iostream>

// залезть в std::allocator
namespace ft
{
	template <class T, class Allocator = std::allocator<T> >
	class vector
	{
		public:
			typedef T												value_type;
			typedef Allocator										allocator_type;
			typedef std::size_t										size_type;
			typedef std::ptrdiff_t									difference_type; // могу использовать int?
			typedef value_type&										reference;
			typedef const value_type&								const_reference;
			typedef typename Allocator::pointer						pointer; // или правильнее написать allocator_type::pointer pointer? есть ли разница?
			typedef typename Allocator::const_pointer				const_pointer;
			typedef typename std::iterator_traits<pointer>::pointer	iterator;
			// добавить итераторы

											// constructors
			// default constructor
			explicit vector(const allocator_type& alloc = allocator_type()): pbegin(0), pend(0), pcapacity(0), alloc(alloc) {}
			// range construction
			// fill construction
			explicit vector(size_type n, const value_type& el = value_type(), const allocator_type& alloc = allocator_type());
			// copy construction
			vector (const vector& x);
											// destructor
			~vector();

											// capacity
			size_type size() const;
			size_type max_size() const;
			void resize(size_type n, value_type val = value_type());
			size_type capacity() const;
			bool empty() const;
			void reserve(size_type n);
											// operator=
			vector& operator= (const vector& x);

											// access to elements
			reference operator[] (size_type n);
			const_reference operator[] (size_type n) const;
			reference at (size_type n); // ? const_reference?
			reference front();
			const_reference front() const;
			reference back();
			const_reference back() const;
											// modifiers
			template<class InputIterator>
			typename std::enable_if<!std::is_integral<InputIterator>::value, void>::type // синтаксис, у Дани нет std:: перед is_inetgral и перед enable_if
			assign(InputIterator first, InputIterator last);
			// assigns values to the container
			void assign(size_type n, const value_type& val);
			void push_back(const value_type& val);
			void pop_back();
			iterator insert(iterator pos, const value_type& val);
			void insert(iterator pos, size_type n, const value_type& val);
			template<class InputIterator>
			typename std::enable_if<!std::is_integral<InputIterator>::value, void>::type
			insert(iterator pos, InputIterator first, InputIterator last);
			iterator erase(iterator position);
			iterator erase(iterator first, iterator last);
			void swap(vector &x);
			void clear();



			private:
				pointer			pbegin;
				pointer			pend;
				pointer			pcapacity;
				allocator_type	alloc;

			void vallocate(size_type n); // точно надо?
			void construct_at_end(size_type n, const_reference val); // точно надо?
			void vdeallocate(size_type n); // точно надо?

	};
										// realisation
										// constructions
/***********************************************************************************************************************/
	// default construction
	// range construction
	// fill construction
	// copy construction
		template <class T, class Allocator>
		vector<T, Allocator>::vector(const vector& v): pbegin(0), pend(0), pcapacity(0), alloc(v.alloc)
		{
			size_type size_v = v.size();
			pointer v_begin = v.pbegin;

			if (size_v > 0)
			{
				this->vallocate(size_v);
				for (size_type i = 0; i < size_v; ++i, ++this->pend, ++v_begin)
					this->alloc.construct(this->pend, *v_begin);
			}
		}
/***********************************************************************************************************************/
										// destructor
/***********************************************************************************************************************/
		template <class T, class Allocator>
		vector<T, Allocator>::~vector()
		{
			this->clear();
		}
/***********************************************************************************************************************/

										// capacity
		// size
		// почему не пишем возвращаемое значение? или оно в typename?
		template <class T, class Allocator>
		typename vector<T, Allocator>::size_type
		vector<T, Allocator>::size() const
		{
			// почему static_cast?
			return static_cast<size_type>(this->pend - this->pbegin);
		}
		// max_size
		template<class T, class Allocator>
		typename vector<T, Allocator>::size_type
		vector<T, Allocator>::max_size() const
		{
			return std::min<T>(this->alloc.max_size(), std::numeric_limits<difference_type>::max());
		}
		// resize
		template<class T, class Allocator>
		void vector<T, Allocator>::resize(size_type n, value_type val)
		{
			size_t size = this->pend - this->pbegin;
			if (size == n)
				return ;
			if (n > this->capacity())
				this->reserve(n);
			// pointer pend_new;
			// pend_new = this->pbegin + n;
			// this->pend = pend_new;
			for (pointer it = this->pend; it < this->pbegin + n; ++it)
				this->alloc.construct(it, val);
			if (n < static_cast<size_type>(this->pend - this->pbegin))
				for (pointer it = this->pbegin + n; it < this->pend; ++it)
					this->alloc.destroy(it);
				this->pend = this->pbegin + n;
		}
		// capacity
		template <class T, class Allocator>
		typename vector<T, Allocator>::size_type
		vector<T, Allocator>::capacity() const
		{
			return static_cast<size_type>(this->pcapacity - this->pbegin);
		}
		// empty - Test whether vector is empty
		template<class T, class Allocator>
		bool vector<T, Allocator>::empty() const
		{
			return this->pbegin == this->pend;
			// можно ли сделать через проверку начального указателя на налл? или при выделении памяти указатель уже указывает куда-то
		}
		// reserve - Request a change in capacity
		template<class T, class Allocator>
		void vector<T, Allocator>::reserve(size_type n)
		{
			if (n > this->capacity()) // разница между capacity, capacity()
			{
				if (n > this->capacity())
				{
					size_t size = this->pend - this->pbegin;
					pointer new_begin;
					new_begin = this->alloc.allocate(n);
					for (size_t i = 0; i < size; ++i)
						this->alloc.construct(new_begin + i, *(this->pbegin + i));
					this->vdeallocate(this->pcapacity - this->pbegin); // что это значит?
					this->pbegin = new_begin;
					this->pend = this->pegin + size;
					this->pcapacity = this->pbegin + n;
				}
			}
		}
										// operator=
/***********************************************************************************************************************/
		template <class T, class Allocator>
		// я нефига не поняла реализацию
		vector<T, Allocator>& vector<T, Allocator>::operator=(const vector& x) // что означает запись перед "operator="
		{
			if (this != &x)
			{
				this->alloc = x.alloc;
				this->vdeallocate(this->pcapacity - this->pbegin);
				this->pbegin = this->pend = this->capacity = 0;
				for (pointer i = x.pbegin; i < x.pend; ++i)
					this->push_back(*i);
			}
			return *this;
		}
/***********************************************************************************************************************/

										// access to elements
/***********************************************************************************************************************/
		template<class T, class Allocator>
		typename vector<T, Allocator>::reference
		vector<T, Allocator>::operator[](size_type n)
		{
			if (n > this->size()) // у Дани так: this->pend - this->pbegin
				throw std::out_of_range("vector[] index out of bounds");
			return *(this->pbegin + n);
		}
		//
		template<class T, class Allocator>
		typename vector<T, Allocator>::const_reference
		vector<T, Allocator>::operator[](size_type n) const
		{
			if (n > this->size()) // у Дани так: this->pend - this->pbegin
				throw std::out_of_range("vector[] index out of bounds");
			return *(this->pbegin + n);
		}
		// at - ?
		template<class T, class Allocator>
		typename vector<T, Allocator>::reference
		vector<T, Allocator>::at(size_type n)
		{
			if (n >= static_cast<size_type>(this->pend - this->pbegin))
				throw std::out_of_range("vector");
			return this->pbeginp[n]; // как работает?
		}
		//
		template<class T, class Allocator>
		typename vector<T, Allocator>::reference
		vector<T, Allocator>::front()
		{
			return *(this->pbegin);
		}
		//
		template<class T, class Allocator>
		typename vector<T, Allocator>::const_reference
		vector<T, Allocator>::front() const
		{
			return *(this->pbegin);
		}
		//
		template<class T, class Allocator>
		typename vector<T, Allocator>::reference
		vector<T, Allocator>::back()
		{
			return *(this->pend - 1);
		}
		//
		template<class T, class Allocator>
		typename vector<T, Allocator>::const_reference
		vector<T, Allocator>::back() const
		{
			return *(this->pend - 1);
		}
/***********************************************************************************************************************/
										// modifiers
		// assign
		template<class T, class Allocator>
		template<class InputIterator>
		typename std::enable_if<!std::is_integral<InputIterator>::value, void>::type
		vector<T, Allocator>::assign(InputIterator first, InputIterator last) // поч не надо void?
		{
			this->clear();
			for(; first != last; ++first)
				this->push_back(*first);
		}
		// fill assign
		template<class T, class Allocator>
		void vector<T, Allocator>::assign(size_type n, const value_type& val)
		{
			this->clear();
			for (size_type i = 0; i < n; ++i)
				this->push_back(val); // разве не надо так: this->push_back(val[i])?
		}
		// push_back
		template<class T, class Allocator>
		void vector<T, Allocator>::push_back(const value_type& val)
		{
			size_type cap = this->pcapacity - this->pbegin;
			if (this->pend == this->capacity)
				this->reserve(2 * (cap > 0 ? cap : 1));
			this->alloc.construct(this->pend, val);
			++this->pend;
		}
		// pop_back
		template<class T, class Allocator>
		void vector<T, Allocator>::pop_back()
		{
			this->alloc.destroy(this->pend - 1); // как работает destroy?
			--this->pend;
		}
		// // insert
		// template<class T, class Allocator>
		// typename vector<T, Allocator>::iterator // у Дани так: typename vector<T, Allocator>::iterator, почему не так? typename vector<T, Allocator>::iterator iterator
		// vector<T, Allocator>::insert(iterator pos, const value_type& val)
		// {

		// }

/***********************************************************************************************************************/


										// allocator
/***********************************************************************************************************************/
		template<class T, class Allocator>
		void vector<T, Allocator>::vallocate(size_type n)
		{
			if (2 * n > max_size())
				throw std::length_error("vector");
			this->pbegin = this->pend = this->alloc.allocate(2 * n);
			pcapacity = pbegin + 2 * n;
		}
		//
		template<class T, class Allocator>
		void vector<T, Allocator>::construct_at_end(size_type n, const_reference val)
		{
			do
			{
				this->alloc.construct(this->pend, val);
				--n;
				++this->pend;
			} while (n > 0);
		}
		//
		template<class T, class Allocator>
		void vector<T, Allocator>::vdeallocate(size_type n)
		{
			for (size_type i = 0; i < n; ++i)
				this->alloc.destroy(this->pbegin + i);
			this->alloc.deallocate(this->pegin, n);
		}
/***********************************************************************************************************************/
}


#endif
