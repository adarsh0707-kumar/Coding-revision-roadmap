/*
26. Modify a Variable Through a Pointer

Write a function that changes a variable's value using a pointer parameter.
*/

#include<iostream>

void modifyVariable(int *ptr)
{
    if (ptr == nullptr)
    {
        std::cout << "Invalid pointer.\n";
        return;
    }

    std::cout << "Memory Address: " << ptr << '\n';
    std::cout << "Original value: " << *ptr << '\n';

    *ptr = 230043;

    std::cout << "Modified value: " << *ptr << '\n';
}

int main(){
    int value = 100;

    modifyVariable(&value);

    return 0;
}