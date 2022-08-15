#include <iostream>
#include "Test.hpp"

template<class T>
Test<T>::Test() {std::cout << "test_constructor" << std::endl;}

template <class T>
Test<T>::~Test() {std::cout << "test_destructor" << std::endl;}

void Test<T>::fun_test(T val) {std::cout << "test.cpp" << val << std::endl;}