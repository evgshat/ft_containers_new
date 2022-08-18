#include <iostream>
#include <type_traits>

template<int n>
struct Factorial
{
    static const int f = Factorial<n-1>::f * n;
};

template<>
struct Factorial<0>
{
    static const int f = 1;
};

template<bool B, class T = void>
struct enable_if
{
    typedef T type;
};
 
template<class T>
struct enable_if<false, T> 
{};

template <class T>
typename enable_if<std::is_integral<T>::value,bool>::type
  is_odd (T i) {return bool(i%2);}

// 2. the second template argument is only valid if T is an integral type:
template < class T,
           class = typename enable_if<std::is_integral<T>::value>::type>
bool is_even (T i) {return !bool(i%2);}

int main()
{
    short int i = 1;    // code does not compile if type of i is not integral

  std::cout << std::boolalpha;
  std::cout << "i is odd: " << is_odd(i) << std::endl;
  std::cout << "i is even: " << is_even(i) << std::endl;
    std::cout << Factorial<3>::f << std::endl;
}
