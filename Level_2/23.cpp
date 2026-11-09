/*
23. Swap Using References

Write a function that swaps two integers using reference parameters.
*/

#include<iostream>

void swapByReference(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

int main()
{

    int x, y;
    std::cout << "Enter the two number : ";
    std::cin >> x >> y;

    std::cout << "Initial values in main: x = " << x << ", y = " << y << "\n\n";

    std::cout << "--- Calling swapByReference ---" << std::endl;
    swapByReference(x, y);
    std::cout << "After swapByReference in main: x = " << x << ", y = " << y << "\n";

    return 0;
}