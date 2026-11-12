/*
41. Insertion Sort

Implement insertion sort and test it on sorted, reversed, and randomly ordered input.
*/
#include<iostream>
#include<vector>

void insertionSort(std::vector<int>& arr){

    int arrSize = arr.size();

    for (int i = 1; i < arrSize; i++){
        int key = arr[i];

        int j = i - 1;

        while(j >= 0 && arr[j]> key){
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}


int main(){
    std::vector<int> nums = {62, 13, 65, 0, 34, 76, 2, 6, 98, 9};

    std::cout << "Original Array ";
    for(int num : nums){
        std::cout << num << " ";
    }
    std::cout << "\n";

    insertionSort(nums);

    std::cout << "Sorted Array : ";
    for (int num : nums)
    {
        std::cout << num << " ";
    }
    std::cout << "\n";

    return 0;
}