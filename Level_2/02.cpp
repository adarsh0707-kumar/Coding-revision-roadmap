/*
2. Find the Smallest Element

Find the minimum element in an array.
*/

#include<iostream>

int main(){
    int arr[] = {4, 7, 9, 9, 0, 7, -2,-1, 67, 6};

    int smallest = arr[0];

    for (int i = 1; i < sizeof(arr)/sizeof(arr[0]); i++){
        if(arr[i] < smallest){
            smallest = arr[i];
        }
    }

    std::cout << "Smallest element of an array : " << smallest << std::endl;
    return 0;
}