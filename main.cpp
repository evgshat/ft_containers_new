#include "ft_containers.hpp"

void test_for_vector()
{

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
    std::cout << "size in b? - " << b.size() << std::endl; // ?? почему 3? мы же сделали pop?
    std::cout << "is empty in b? - " << b.empty() << std::endl;

    // операторы сравнения:
    ft::stack<int, std::vector<int> > c(b);
    // std::cout << "is equals? - " << b == c << std::endl; // поч так не могу?
        // alt для сравнения
    int res;
    res = b == c ;
    std::cout << "is b == c? - " << res << std::endl;  
    res = b != c ;
    std::cout << "is b != c? - " << res << std::endl;
    c.push(3);
    std::cout << "top element in c - " << c.top() << std::endl;
    res = b == c ;
    std::cout << "is b == c? - " << res << std::endl; 
    res = b > c ;
    std::cout << "is b > c? - " << res << std::endl; 
    res = b < c ;
    std::cout << "is b < c? - " << res << std::endl; 
    res = b >= c ;
    std::cout << "is b >= c? - " << res << std::endl; 
    res = b <= c ;
    std::cout << "is b <= c? - " << res << std::endl; 
        // end  alt для сравнения

    // еще пару контейнеров
    ft::stack<int> d;
    std::cout << "is empty in d? - " << d.empty() << std::endl;
    // ft::stack<int> e(); // разве нельзя?
}

int main()
{
    std::cout << "hello" << std::endl;
    // test_for_stack();
    test_for_vector();
}