/*
5. Find the Second-Largest Element

Find the second-largest distinct element without sorting.
*/

#include <iostream>
#include <iterator>
#include <climits>

int main()
{
    int arr[] = {5, INT_MIN};
    int n = std::size(arr);

    if (n < 2)
    {
        std::cout << "Array needs at least two elements\n";
        return 0;
    }

    int largest = INT_MIN;
    int secondLargest = INT_MIN;
    bool foundSecond = false;

    for (int num : arr)
    {
        if (num > largest)
        {
            secondLargest = largest;
            largest = num;
            foundSecond = true;
        }
        else if (num < largest &&
                 (!foundSecond || num > secondLargest))
        {
            secondLargest = num;
            foundSecond = true;
        }
    }

    if (foundSecond)
    {
        std::cout << "Second largest: " << secondLargest << '\n';
    }
    else
    {
        std::cout << "No distinct second-largest element\n";
    }

    return 0;
}