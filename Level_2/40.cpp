/*
40. Selection Sort

Sort an array using selection sort.
*/

#include<iostream>
#include<vector>

void selectionSort(std::vector<int>& arr){

    int arrSize = arr.size();

    for (int i = 0; i < arrSize -1; i++)
    {
        int minIndex = i;

        for (int j = i + 1; j < arrSize ; ++j){
            if(arr[j] < arr[minIndex]){
                minIndex = j;
            }
        }

        int temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
    }
}

int main(){
    std::vector<int> nums = {62, 13, 65, 0, 34, 76, 2, 6, 98, 9};

    std::cout << "Original Array : ";
    for (int num : nums)
    {
        std::cout << num << " ";
    }
    std::cout << "\n";

    selectionSort(nums);

    std::cout << "Sorted array: ";
    for(int num : nums){
        std::cout << num << " ";
    }

    return 0;
}