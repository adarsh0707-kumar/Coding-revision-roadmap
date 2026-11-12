/*
35. Calculate Power Recursively

Calculate \(a^b\) recursively for a non-negative exponent.
*/

#include <iostream>

double powerFast(double x, unsigned long long n)
{
    if (n == 0)
        return 1.0;

    double half = powerFast(x, n / 2);

    if (n % 2 == 0)
        return half * half;

    return x * half * half;
}

int main()
{
    double base;
    long long exponent;

    std::cout << "Enter base and non-negative exponent: ";

    if (!(std::cin >> base >> exponent))
    {
        std::cerr << "Invalid input.\n";
        return 1;
    }

    if (exponent < 0)
    {
        std::cerr << "Negative exponent is not allowed.\n";
        return 1;
    }

    std::cout << base << "^" << exponent
              << " = "
              << powerFast(base,
                           static_cast<unsigned long long>(exponent))
              << '\n';

    return 0;
}