#include "ft_containers.hpp"

void test_for_vector()
{
    std::cout << "hello_vector" << std::endl;
    ft::vector<int> a;
    a.size();
    a.empty();
    std::cout << "is empty? - " << (a.empty()) << std::endl;
}

void test_for_stack()
{
    std::vector<int> a(1);
    a.push_back(1);
    // std::stack<int> b;
    ft::stack<int, std::vector<int> > b(a);
    std::cout << "top element in b - " << b.top() << std::endl;
    b.push(2); 
    b.pop();
    std::cout << "top element in b- " << b.top() << std::endl;
    b.push(2);
    std::cout << "size in b? - " << b.size() << std::endl;
    std::cout << "is empty in b? - " << b.empty() << std::endl;

    // операторы сравнения:
    ft::stack<int, std::vector<int> > c(b);
    std::cout << "is b == c? - " << (b == c) << std::endl;
    std::cout << "is b != c? - " << (b != c) << std::endl;
    c.push(3);
    std::cout << "top element in c - " << c.top() << std::endl;
    std::cout << "is b == c? - " << (b == c) << std::endl;
    std::cout << "is b > c? - " << (b > c) << std::endl;
    std::cout << "is b < c? - " << (b < c) << std::endl;
    std::cout << "is b >= c? - " << (b >= c) << std::endl;
    std::cout << "is b <= c? - " << (b <= c) << std::endl;

    // еще пару контейнеров
    ft::stack<int> d;
    std::cout << "is empty in d? - " << d.empty() << std::endl;
    // ft::stack<int> e(); // так не могу написать
}

int main()
{
    // std::cout << "hello_main" << std::endl;
    // test_for_stack();
    test_for_vector();
}