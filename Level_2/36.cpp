/*
36. Binary Search Recursively

Implement binary search using recursion on a sorted array.
*/

#include<iostream>
#include<vector>

int binarySearch(const std::vector<int>& arr, int target, int low, int high){
    if(low > high)
        return -1;

    int mid = low + (high - low) / 2;

    if(arr[mid] == target)
        return mid;
    
    else if(arr[mid] > target)
        return binarySearch(arr, target, low, mid - 1);
    
    else
        return binarySearch(arr, target, mid + 1, high);
    
}

int main(){
    std::vector<int> arr = {2, 3, 4, 5, 67, 76, 87, 89, 91, 92, 455, 6345};

    int target = 455;

    int index = binarySearch(arr, target, 0, arr.size() - 1);

    if(index != -1)
        std::cout << "Element found at index " << index << std::endl;
    else
        std::cout << "Element not found" << std::endl;
    return 0;
}