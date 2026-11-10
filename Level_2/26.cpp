/*
26. Modify a Variable Through a Pointer

Write a function that changes a variable's value using a pointer parameter.
*/

#include<iostream>

void modifyVariable(int &a){
    int *ptr = &a;

    std::cout << "Memory Address: " << ptr << std::endl;
    std::cout << "Original value: " << *ptr << std::endl;

    *ptr = 230043;
    std::cout << "Modify value: " << *ptr << std::endl;

    int *empty_ptr = nullptr;
}

int main(){
    int value = 100;

    modifyVariable(value);

    return 0;
}