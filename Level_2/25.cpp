/*
25. Pointer Basics

Declare an integer and a pointer to it. Print the value, address, and dereferenced value.
*/


#include<iostream>

int main(){
    int val = 100;
    int *ptr = &val;

    std::cout << "Memory Address: " << ptr << "\n";      // e.g., 0x7ff7bfe0
    std::cout << "Dereferenced Value: " << *ptr << "\n"; // Output: 100

    *ptr = 250; // Modify val through the pointer
    std::cout << "Updated val: " << val << "\n"; // Output: 250

    // Always reset unused raw pointers to nullptr
    int *empty_ptr = nullptr;

    return 0;
}