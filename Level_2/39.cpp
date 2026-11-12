/*
39. Bubble Sort

Sort an array in ascending order using bubble sort.
*/

#include<iostream>
#include<vector>

void bubbleSort(std::vector<int>& arr){
    int arrSize = arr.size();

    for (int i = 0; i < arrSize - 1; i++){

        for (int j = 0; j < arrSize - i - 1; j++){
            if(arr[j]> arr[j+1]){
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main(){
    std::vector<int> arr = {23, 42, 24, 63, 334, 53, 0, 43};

    std::cout << "Original array: ";
    for(int i : arr){
        std::cout << i << " ";
    }
    std::cout << "\n";

    bubbleSort(arr);
    std::cout << "Sorted array: ";
    for(int i : arr){
        std::cout << i << " ";
    }
    std::cout << "\n";
    return 0;
}