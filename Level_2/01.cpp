/*
1. Find the Largest Element

Given an array of integers, find the largest element without sorting the array.
*/

#include<iostream>

using namespace std;

int main(){
    int arr[] = {1, 3, 4, 5, 9, 4, 6, 4, 0, 3};

    int size = sizeof(arr) / sizeof(arr[0]);
    int largest = arr[0];

    for (int i = 1; i < size;i++){
        if(arr[i] > largest){
            largest = arr[i];
        }
    }

    cout << "Largest element of an array is " << largest << endl;
    return 0;
}