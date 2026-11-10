/*
28. Find the Largest Element Using Pointers

Find the maximum array element using pointers.
*/

#include<iostream>

int main(){
    int arr[] = {10, 30, 20, 43, 34, 32, 3, 42, 0, 44, 1};

    int arrSize = sizeof(arr) / sizeof(arr[0]);

    int largest = arr[0];
    int *ptr = arr;

    for (int i = 0; i < arrSize; i++){
        if(*(ptr + i) > largest)
            largest = *(ptr + i);
    }

    std::cout << "Largest element in arr: " << largest << std::endl;

    return 0;
}