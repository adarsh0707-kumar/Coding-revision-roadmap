/*
42. Merge Two Sorted Arrays

Merge two sorted arrays into a single sorted array.
*/

#include <iostream>
#include <vector>

void mergeSortedArray(std::vector<int> &arr1, std::vector<int> &arr2)
{

    int arrSize1 = arr1.size();
    int arrSize2 = arr2.size();

    int newArrSize = arrSize1 + arrSize2;

    std::vector<int> newArray(newArrSize);

    int i = 0;
    int j = 0;
    int k = 0;

    while (i < arrSize1 && j < arrSize2)
    {
        if (arr1[i] <= arr2[j])
        {
            newArray[k++] = arr1[i++];
        }
        else
        {
            newArray[k++] = arr2[j++];
        }
    }

    while (i < arrSize1)
    {
        newArray[k++] = arr1[i++];
    }

    while (j < arrSize2)
    {
        newArray[k++] = arr2[j++];
    }

    std::cout << "Merged Array : ";
    for (int num : newArray)
    {
        std::cout << num << " ";
    }
    std::cout << "\n";
}
int main()
{
    std::vector<int> arr1 = {0, 2, 4, 6, 7, 9};
    std::vector<int> arr2 = {1, 3, 5, 8, 10, 11};

    mergeSortedArray(arr1, arr2);
    return 0;
}