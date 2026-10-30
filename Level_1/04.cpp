/*
4. Largest of two numbersConditions
· EasyLargest of two numbers
Read two numbers and print the larger one. Handle equal numbers too.Example
Input: 9 9
Output: Equal
*/

#include <iostream>

int main()
{
    int a, b;

    std::cout << "Enter the number 1: ";
    std::cin >> a;
    std::cout << "Enter the number 2: ";
    std::cin >> b;

    if (a > b)
    {
        std::cout << a << " is greater than " << b << std::endl;
    }
    else if (b > a)
    {
        std::cout << b << " is greater than " << a << std::endl;
    }
    else
    {
        std::cout << "Equal" << std::endl;
    }

    return 0;
}