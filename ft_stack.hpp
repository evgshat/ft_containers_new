#ifndef FT_STACK_HPP
#define FT_STACK_HPP

#include <deque>

namespace ft
{
	template <class T, class Container = std::deque<T> >
	class stack
	{
		public:
			typedef T			value_type;
			typedef Container	container_type;
			typedef size_t		size_type;
		protected:
			container_type c;
		public:
			explicit stack(const container_type& ct = container_type()): c(ct) {}
			bool empty() const
			{
				return c.empty();
			}
			size_type size() const
			{
				return c.size();
			}
			value_type& top()
			{
				return c.back();
			}
			const value_type& top() const
			{
				return c.back();
			}
			void push(const value_type& el)
			{
				return c.push_back(el);
			}
			void pop()
			{
				return c.pop_back();
			}

			template <class T1, class Container1>
			friend bool operator== (const stack<T1, Container1>& st1, const stack<T1, Container1>& st2);

			template <class T1, class Container1>
			friend bool operator< (const stack<T1, Container1>& st1, const stack<T1, Container1>& st2);
	};

	template <class T1, class Container1>
	bool operator== (const stack<T1, Container1>& st1, const stack<T1, Container1>& st2)
	{
		return st1.c == st2.c;
	}

	template <class T1, class Container1>
	bool operator!= (const stack<T1, Container1>& st1, const stack<T1, Container1>& st2)
	{
		return !(st1 == st2);
	}

	template <class T1, class Container1>
	bool operator< (const stack<T1, Container1>& st1, const stack<T1, Container1>& st2)
	{
		return st1.c < st2.c;
	}

	template <class T1, class Container1>
	bool operator<= (const stack<T1, Container1>& st1, const stack<T1, Container1>& st2)
	{
		return !(st2 < st1);
	}

	template <class T1, class Container1>
	bool operator> (const stack<T1, Container1>& st1, const stack<T1, Container1>& st2)
	{
		return st2 < st1; 
	}

	template <class T1, class Container1>
	bool operator>= (const stack<T1, Container1>& st1, const stack<T1, Container1>& st2)
	{
		return !(st1 < st2); 
	}
} // namespace ft end

#endif
