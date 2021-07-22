#include "Fraction.h"

#include <iostream>

// g++ Fraction.cpp main.cpp --std=c++17
int main()
{
    Fraction a(4, 5), b(2), c, d; // c et d valent 0 par défaut

    c = a + b;
    d = a * b;

    std::cout << a << " + " << b << " = " << c << std::endl;
    std::cout << a << " * " << b << " = " << d << std::endl;

    if(a > b)
        std::cout << "a est plus grand que b" << std::endl;
    else if(a == b)
        std::cout << "a est égal à b" << std::endl;
    else
        std::cout << "a est plus petit que b" << std::endl;
}
