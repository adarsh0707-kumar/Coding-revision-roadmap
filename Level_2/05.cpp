/*
5. Find the Second-Largest Element

Find the second-largest distinct element without sorting.
*/

#include<iostream>
#include<climits>

int main(){

    int arr[] = {0, 3, 1, 9, 5, 7, 4, 6, 8, 9};

    int largest = INT_MIN;
    int secondLargest = INT_MIN;

    int arrSize = std::size(arr);

    if(arrSize < 2)
    {
        std::cout << "Invalid array, size must be greater than 2" << std::endl;
        return 0;
    }

    for(int num : arr){
        if(num > largest){
            secondLargest = largest;
            largest = num;
        }
        else if(num > secondLargest && num != largest){
            secondLargest = num;
        }
    }

    if(secondLargest == INT_MIN){
        std::cout << "No second largest is in this arr (All element might be equal)." << std::endl;
    }else{
        std::cout << "Second Largest of an array is : " << secondLargest << std::endl;
    }
    return 0;
}