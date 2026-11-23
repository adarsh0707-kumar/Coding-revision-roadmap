/*
Q8. Dynamic Integer Array
Allocate an integer array dynamically using new[], initialize it, calculate its sum and release memory correctly.
*/

#include<iostream>

int main(){
    int arrSize = 10;

    int *arr = new int[arrSize];

    for (int i = 0; i < arrSize; ++i){
        *(arr + i) = (i + 1) * 10;
    }

    std::cout << "Printing the element of the array : \n";
    for (int i = 0; i<arrSize; ++i){
        std::cout << "Element at " << i << " : " << arr[i] << " and it's addresses is " << (arr + i) << "\n";
    }

    int sum = 0;
    for (int i = 0; i < arrSize; ++i)
    {
        sum += *(arr + i);
    }
    std::cout << "Sum of an array: " << sum << std::endl;

    delete[] arr;
    arr = nullptr;
    return 0;
}