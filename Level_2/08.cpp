/*
8. Remove Duplicates from a Sorted Array

Modify a sorted array in place so each distinct value appears once.
*/

#include<iostream>
#include<iterator>

void swap(int &a, int &b){
    int temp = a;
    a = b;
    b = temp;
}

int main()
{

    int arr[] = {0, 3, 22, 33, 22, 84, 84, 2, 4, 6, 3, 204, 4, 0};
    int arrSize = std::size(arr);

    // array sort

    for (int i = 0; i < arrSize; i++){
        for (int j = 0; j < arrSize - i -1; j++){
            if(arr[j] > arr[j + 1]){
                swap(arr[j], arr[j + 1]);
            }
        }
    }

    std::cout << "Sorted Array : ";
    for (int num : arr)
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    int j = 0;
    for (int i = 0; i < std::size(arr) - 1; i++){
        if(arr[i] != arr[i+1]){
            arr[j++] = arr[i];
        }
    }
    arr[j++] = arr[std::size(arr) - 1];

    std::cout << "Modified array : ";
    for (int i = 0; i < j; i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}