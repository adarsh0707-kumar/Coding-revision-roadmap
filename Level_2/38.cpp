/*
38. Binary Search Iteratively

Find a target in a sorted array using binary search.
*/

#include<iostream>
#include<vector>

int binarySearch(const std::vector<int>& arr, int target){

    int low = 0;
    int high = arr.size() - 1;

    while(low <= high){
        int mid = low + (high - low) / 2;

        if(arr[mid] == target){
            return mid;
        }
        else if(arr[mid] < target){
            low = mid + 1;
        }
        else{
            high = mid - 1;
        }
    }

    return -1;
}

int main(){
    std::vector<int> arr = {1, 3, 4, 5, 6, 7, 8, 12, 45, 66, 87, 99, 123};

    int target = 12;

    int index = binarySearch(arr, target);

    if(index != -1){
        std::cout << "Element found at index : " << index << std::endl;
    }
    else{
        std::cout << "Element not found!" << std::endl;
    }
    return 0;
}