/*
27. Traverse an Array Using Pointers

Print all array elements using pointer arithmetic instead of array indexing.
*/

#include<iostream>

int main(){

    int arr[] = {0, 2, 1, 3, 5, 4, 6, 9, 8, 7};

    int arrSize = sizeof(arr) / sizeof(arr[0]);

    int *ptr = arr;

    for (int i = 0; i < arrSize; ++i){
        std::cout << *(ptr + i) << " ";
    }
    std::cout << std::endl;
    return 0;
}