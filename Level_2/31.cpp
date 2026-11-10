/*
31. Factorial Using Recursion

Calculate the factorial of a non-negative integer recursively.
*/


#include <iostream>
#include <limits>

unsigned long long factorial(int n)
{
    if (n <= 1)
        return 1;

    return static_cast<unsigned long long>(n) * factorial(n - 1);
}

int main()
{
    int num;

    std::cout << "Enter the number: ";

    if (!(std::cin >> num))
    {
        std::cerr << "Invalid input.\n";
        return 1;
    }

    constexpr int MAX_FACTORIAL = 20;

    if (num < 0)
    {
        std::cout << "Factorial is not defined for negative numbers.\n";
    }
    else if (num > MAX_FACTORIAL)
    {
        std::cout << "Overflow error: factorial exceeds "
        "unsigned long long capacity.\n";
    }
    else
    {
        std::cout << "Factorial of " << num
                  << " is " << factorial(num) << '\n';
    }

    return 0;
}