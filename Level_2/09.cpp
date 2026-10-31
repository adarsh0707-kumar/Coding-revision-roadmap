/*
9. Rotate an Array

Rotate an array to the left & right by k positions.


Right Rotation (Clockwise) by k Steps

To rotate an array to the right by k steps:
1. Normalize k: k = k (mod n)
2. Reverse the entire array (indices 0 to n - 1)
3. Reverse the first k elements (indices 0 to k - 1)
4. Reverse the remaining n - k elements (indices k to n - 1)


Left Rotation (Counterclockwise) by k Steps

To rotate an array to the left by k steps:
1. Normalize k: k = k (mod n)
2. Reverse the first k elements (indices 0 to k - 1)
3. Reverse the last n - k elements (indices k to n - 1)
4. Reverse the entire array (indices 0 to n - 1)

*/

#include<iostream>
#include<iterator>

void reverseArray(int arr[], int start, int end){
    while (start < end)
    {
        int temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }
}

void leftRotation(int k, int arr[], int arrSize){

    k = k % arrSize;

    if(k == 0){
        std::cout << "No rotation need" << std::endl;
        return;
    }

    // step 2
    reverseArray(arr, 0, k - 1);

    //step 3
    reverseArray(arr, k, arrSize - 1);

    // step 4;

    reverseArray(arr, 0, arrSize - 1);

    // print the array;

    std::cout << "Left Rotation : ";
    for (int i = 0; i < arrSize; i++)
    {
        std::cout << arr[i] << " ";
    }

    std::cout << std::endl;
}

void rightRotation(int k, int arr[], int arrSize){

    k = k % arrSize;

    if (k == 0)
    {
        std::cout << "No rotation need" << std::endl;
        return;
    }

    // step 2;
    reverseArray(arr, 0, arrSize - 1);

    // step 3;

    reverseArray(arr, 0, k - 1);

    // step 4;

    reverseArray(arr, k, arrSize - 1);

    // print array;

    std::cout << "Right Rotation : ";
    for (int i = 0; i < arrSize; i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

int main(){
    int k;
    std::cout << "Enter the k position: ";
    std::cin >> k;

    int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int arrSize = sizeof(arr) / sizeof(arr[0]);
    int arr2[10];


    for (int i = 0; i < arrSize; i++)
    {
        arr2[i] = arr[i];
    }

    

    std::cout << "Original arr : ";
    for (int num : arr)
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    leftRotation(k, arr, arrSize);

    rightRotation(k, arr2, arrSize);

    return 0;
}
