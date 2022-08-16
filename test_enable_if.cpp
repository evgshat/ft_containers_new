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

int main()
{
    std::cout << Factorial<3>::f << std::endl;
}
