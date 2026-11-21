/*
Q6. Array of Pointers
Create an array of pointers pointing to different integer variables. Print and modify the original values through those pointers.
*/

#include<iostream>
#include<vector>

int main(){
    int a = 10, b = 20, c = 3, d = 40;

    int *arr[] = {&a, &b, &c, &d};
    int size = sizeof(arr) / sizeof(arr[0]);

    std::cout << "Original values: ";
    for (int i = 0; i < size; ++i){
        std::cout << *arr[i] << " ";
    }

    std::cout << std::endl;

    for (int i = 0; i<size; ++i){
        *arr[i] += 5;
    }

    std::cout << "Modified variables: ";
    for (int i = 0; i < size; ++i){
        std::cout << *arr[i] << " ";
    }

    return 0;
}