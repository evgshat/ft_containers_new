#include "ft_containers.hpp"

void test_for_vector()
{
    // std::cout << "hello_vector" << std::endl;
    ft::vector<int> a;
     std::cout << "size? - " << a.size() << std::endl;
    std::cout << "old_capacity - " << a.capacity() << std::endl;
    a.empty();
    std::cout << "is empty? - " << (a.empty()) << std::endl;
    std::cout << "is max_size? - " << a.max_size() << std::endl;
    // try { a.reserve(4611686018427387904); }
    //  catch(const std::exception& e){ std::cerr << e.what() << '\n';} // исключение
    // try { a.reserve(0); }
    //  catch(const std::exception& e){ std::cerr << e.what() << '\n'; } // ничего
    try { a.reserve(150); }
     catch(const std::exception& e){ std::cerr << e.what() << '\n';  } // перераспрделение памяти
    std::cout << "new_capacity - " << a.capacity() << std::endl;
    
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