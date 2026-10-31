/*
10. Move All Zeros to the End

Move zeros to the end while preserving the relative order of nonzero elements.
*/

#include<iostream>

void moveZeroToEnd(int arr[], int n){
    int insertPos = 0;
    for (int i = 0; i < n;i++){
        if(arr[i] !=  0){
            int temp = arr[i];
            arr[i] = arr[insertPos];
            arr[insertPos] = temp;

            insertPos++;
        }
    }
}

int main(){

    int arr[] = {0, 1, 0, 3, 13, 0, 8, 9};

    int n = sizeof(arr) / sizeof(arr[0]);

    std::cout << "Original array: ";
    for(int num : arr){
        std::cout << num << " ";
    }
    std::cout << std::endl;

    moveZeroToEnd(arr, n);

    std::cout << "Zeros Moved : ";
    for (int i = 0; i < n;i++){
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}