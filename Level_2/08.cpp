/*
8. Remove Duplicates from a Sorted Array

Modify a sorted array in place so each distinct value appears once.
*/

#include <iostream>

int main()
{
    int arr[] = {0, 0, 2, 2, 3, 4, 4, 6, 6, 8};

    int n = sizeof(arr) / sizeof(arr[0]);

    if (n == 0)
        return 0;

    int j = 1;

    for (int i = 1; i < n; i++)
    {
        if (arr[i] != arr[j - 1])
        {
            arr[j] = arr[i];
            j++;
        }
    }

    std::cout << "Unique elements: ";

    for (int i = 0; i < j; i++)
    {
        std::cout << arr[i] << " ";
    }

    return 0;
}