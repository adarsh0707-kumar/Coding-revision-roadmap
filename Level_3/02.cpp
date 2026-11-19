/*
Q2. Pointer to Pointer
Create a pointer to a pointer and demonstrate how to access and modify the original variable through it.
*/

#include<iostream>

int main(){
    int a = 100;

    int *ptr = &a;

    int **ptr2 = &ptr;

    std::cout << "Original variable: " << a << std::endl
    << "Single pointer: " << *ptr << std::endl
    << "Double pointer: " << **ptr2 << std::endl;

    **ptr2 = 200;

    std::cout << "After modification: \n";
    std::cout << "Original variable: " << a << std::endl
              << "Single pointer: " << *ptr << std::endl
              << "Double pointer: " << **ptr2 << std::endl;

    std::cout << "Addresses in all pointer: \n";
    std::cout << "Original variable: " << a << std::endl
              << "Single pointer: " << ptr << std::endl
              << "Double pointer: " << *ptr2 << std::endl;

    return 0;
}