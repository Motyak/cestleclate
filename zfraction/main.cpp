#include "Fraction.h"

#include <iostream>
#include <vector>

void afficher(const char* format) // base function
{
    std::cout << format << '\n';
}
 
template<typename T, typename... Targs>
void afficher(const char* format, T value, Targs... Fargs) // recursive variadic function
{
    for (; *format != '\0'; format++)
    {
        if (*format == '{' && *(format + 1) == '}')
        {
            std::cout << value;
            afficher(format + 2, Fargs...); // recursive call
            return;
        }
        std::cout << *format;
    }
}

// g++ Fraction.cpp main.cpp --std=c++17
int main()
{
    Fraction a(4, 5);
    Fraction b(2);

    afficher("{} + {} = {}", a, b, a + b);
    afficher("{} * {} = {}", a, b, a * b);

    std::cout << a;
    if(a > b) {
    std::cout << " est plus grand que ";
    } else if(a == b) {
        std::cout << " est égal à ";
    } else {
        std::cout << " est plus petit que ";
    }
    std::cout << b << '\n';
}
