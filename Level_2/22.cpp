/*
22. Pass by Value vs. Pass by Reference

Write a program that demonstrates the difference between passing arguments by value and by reference.
*/

#include<iostream>

void swapByValue(int a, int b){
    int temp = a;
    a = b;
    b = temp;
}

void swapByReference(int& a, int& b){
    int temp = a;
    a = b;
    b = temp;
}

int main(){

    int x, y;
    std::cout << "Enter the two number : ";
    std::cin >> x >> y;

    std::cout << "Initial values in main: x = " << x << ", y = " << y << "\n\n";

    // 1. Pass by Value Test
    std::cout << "--- Calling swapByValue ---" << std::endl;
    swapByValue(x, y);
    std::cout << "After swapByValue in main:  x = " << x << ", y = " << y << "\n\n";

    // 2. Pass by Reference Test
    std::cout << "--- Calling swapByReference ---" << std::endl;
    swapByReference(x, y);
    std::cout << "After swapByReference in main: x = " << x << ", y = " << y << "\n";

    return 0;
}