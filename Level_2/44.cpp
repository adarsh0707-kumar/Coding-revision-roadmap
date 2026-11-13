/*
44. Quick Sort

Implement quicksort and explain how pivot selection affects performance.

================================================================================
HOW PIVOT SELECTION AFFECTS PERFORMANCE
================================================================================
Quick Sort's speed depends almost entirely on how evenly the pivot splits the
array during each partition step:

1. Balanced Splits - Best & Average Case: O(N log N)
   - When the pivot lands near the median value, the array divides into two
     roughly equal halves.
   - This creates a shallow recursion tree of depth log(N), doing O(N) work
     at each level.

2. Lopsided Splits - Worst Case: O(N^2)
   - When the pivot is consistently the smallest or largest element, one
     partition gets (N - 1) elements and the other gets 0.
   - This creates a skewed recursion chain of depth N, degrading performance
     to O(N^2).

3. The Sorted Array Trap
   - Picking the first or last element hits the O(N^2) worst case on arrays
     that are already sorted or reverse-sorted.

================================================================================
COMMON PIVOT SELECTION STRATEGIES
================================================================================
+--------------------+------------------------------+--------------------------+

| Strategy           | How It Works                 | Impact on Performance    |
+--------------------+------------------------------+--------------------------+

| First / Last       | Always picks arr[low] or     | Simple, but hits O(N^2)  |
| Element            | arr[high].                   | on sorted/reverse inputs.|
+--------------------+------------------------------+--------------------------+

| Random Pivot       | Picks a random index in      | Prevents predictable     |
|                    | [low, high] & swaps to end.  | worst cases; O(N log N). |
+--------------------+------------------------------+--------------------------+

| Median-of-Three    | Uses middle value among      | Avoids worst-case splits |
|                    | arr[low], arr[mid], arr[high]| without RNG overhead.    |
+--------------------+------------------------------+--------------------------+
*/


#include<iostream>
#include<vector>
#include<algorithm>

int partition(std::vector<int>& arr, int low, int high){
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++){
        if(arr[j] <= pivot){
            i++;
            std::swap(arr[i], arr[j]);
        }
    }

    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(std::vector<int>& arr, int low, int high){
    if(low <high){
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main(){
    std::vector<int> arr = {10, 7, 8, 9, 1, 5};
    std::cout << "Original Array : ";
    for(int num : arr){
        std::cout << num << " ";
    }
    std::cout << "\n";

    quickSort(arr, 0, arr.size() - 1);

    std::cout << "Sorted Array : ";
    for (int num : arr)
    {
        std::cout << num << " ";
    }
    std::cout << "\n";
    return 0;
}
