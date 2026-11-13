/*
43. Merge Sort

Implement merge sort using divide and conquer.
*/

#include<iostream>
#include<vector>

void merge(std::vector<int>& arr, int left, int mid, int right){
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<int> leftArr(n1);
    std::vector<int> rightArr(n2);

    for (int i = 0; i < n1; i++){
        leftArr[i] = arr[left + i];
    }

    for (int j = 0; j < n2; j++){
        rightArr[j] = arr[mid + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = left;

    while(i <n1 && j<n2){
        if(leftArr[i] <= rightArr[j]){
            arr[k++] = leftArr[i++];
        }else{
            arr[k++] = rightArr[j++];
        }
    }

    while(i < n1){
        arr[k++] = leftArr[i++];
    }

    while(j < n2){
        arr[k++] = rightArr[j++];
    }
}

void mergeSort(std::vector<int>& arr, int left, int right){
    if(left >= right){
        return;
    }

    int mid = left + (right - left) / 2;

    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);

    merge(arr, left, mid, right);
}

int main(){
    std::vector<int> arr = {38, 27, 43, 3, 9, 82, 10};

    std::cout << "Original Array : ";
    for(int num : arr){
        std::cout << num << " ";
    }
    std::cout << "\n";

    mergeSort(arr, 0, arr.size() - 1);

    std::cout << "Sorted Array : ";
    for (int num : arr)
    {
        std::cout << num << " ";
    }
    std::cout << "\n";

    return 0;
}