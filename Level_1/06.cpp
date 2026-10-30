/*
6. Simple calculator switch
· EasySimple calculator
Read two numbers and an operator (+, -, *, /), then print the result. Handle division by zero.Example
Input: 10 2 /
Output: 5
*/

#include <iostream>

int main()
{

    char op;
    std::cout << "Enter the operator(+, -, *, /): ";
    std::cin >> op;

    int a, b;
    std::cout << "Enter the two number's: ";
    std::cin >> a >> b;

    switch (op)
    {
    case '+':
        std::cout << a << " + " << b << " = " << a + b << std::endl;
        break;

    case '-':
        std::cout << a << " - " << b << " = " << a - b << std::endl;
        break;

    case '*':
        std::cout << a << " * " << b << " = " << a * b << std::endl;
        break;

    case '/':
        if (b == 0)
        {
            std::cout << "Anything divided by zero (0) is not allowed" << std::endl;
        }
        else
        {
            std::cout << a << " / " << b << " = " << static_cast<double>(a) / b << std::endl;
        }
        break;

    default:
        std::cout << "Invalid operator " << op << std::endl;
    }

    return 0;
}