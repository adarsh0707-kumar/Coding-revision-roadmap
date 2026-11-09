/*
20. GCD and LCM Functions

Implement separate functions to calculate the GCD and LCM of two integers.
*/


#include<iostream>
#include <cstdint>
#include <limits>
#include <optional>
/*
19. Build a Calculator Using Functions

Implement addition, subtraction, multiplication, and division in separate functions.
*/

#include <iostream>

void addition(int a, int b)
{
    long long sum = static_cast<long long>(a) + b;
    std::cout << "Sum of : " << a << " + " << b << " is " << sum << std::endl;
}

void subtraction(int a, int b)
{
    long long sub = static_cast<long long>(a) - b;
    std::cout << "Sub of : " << a << " - " << b << " is " << sub << std::endl;
}

void multiplication(int a, int b)
{

    long long mul = static_cast<long long>(a) * b;

    std::cout << "Multiply of : " << a << " X " << b << " is " << mul << std::endl;
}

void division(int a, int b)
{

    if (b == 0)
    {
        std::cout << "Error: Division by zero is undefined!" << std::endl;
        return;
    }

    double result = static_cast<double>(a) / b;

    std::cout << "Division of : " << a << " / " << b << " is " << result << std::endl;
}

int main()
{

    int a, b;
    char op;

    std::cout << "Enter the operator : ";
    std::cin >> op;

    std::cout << "Enter the number for calculation(+,-,*,/) : ";
    std::cin >> a >> b;

    switch (op)
    {

    case '+':
        addition(a, b);
        break;
    case '-':
        subtraction(a, b);
        break;
    case '*':
        multiplication(a, b);
        break;

    case '/':
        division(a, b);
        break;
    default:
        std::cout << "Error: Invalid operator ('" << op << "')" << std::endl;
    }

    return 0;
}
using ULL = unsigned long long;

ULL magnitude(long long n)
{
    return n < 0
               ? static_cast<ULL>(-(n + 1)) + 1
               : static_cast<ULL>(n);
}

ULL gcdValue(ULL a, ULL b)
{
    while (b != 0)
    {
        ULL r = a % b;
        a = b;
        b = r;
    }
    return a;
}

std::optional<long long> lcmValue(long long a, long long b)
{
    ULL x = magnitude(a);
    ULL y = magnitude(b);

    if (x == 0 || y == 0)
        return 0LL;

    ULL g = gcdValue(x, y);
    ULL reduced = x / g;

    const ULL maxValue =
        static_cast<ULL>(std::numeric_limits<long long>::max());

    if (reduced > maxValue / y)
        return std::nullopt;

    return static_cast<long long>(reduced * y);
}

int main()
{
    long long a, b;
    std::cout << "Enter two integers: ";
    if (!(std::cin >> a >> b))
        return 0;

    std::cout << "GCD(" << a << ", " << b << ") = " << gcdValue(magnitude(a), magnitude(b)) << "\n";

    auto lcmResult = lcmValue(a, b);
    if (lcmResult.has_value())
    {
        std::cout << "LCM(" << a << ", " << b << ") = "
                  << *lcmResult << '\n';
    }
    else
    {
        std::cout << "LCM exceeds the long long range.\n";
    }

    return 0;
}