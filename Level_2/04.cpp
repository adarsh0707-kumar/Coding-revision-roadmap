/*
4. Reverse an Array

Reverse an array in place without creating another array.
*/

#include<iostream>

void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

int main(){
    int arr[] = {1, 3, 4, 5, 9, 4, 6, 34, 0, 3};
    int arrSize = sizeof(arr) / sizeof(arr[0]);

    int left = 0;
    int right = arrSize - 1;

    while(left < right){
        swap(arr[left], arr[right]);
        left++;
        right--;
    }

    // print arr;
    for(int num : arr){
        std::cout << num << " ";
    }

    return 0;
}