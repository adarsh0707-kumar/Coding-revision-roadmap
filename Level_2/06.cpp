/*
6. Count Even and Odd Elements

Count the even and odd values in an array.
*/

#include<iostream>

int main(){
    int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9,11};

    int countEven = 0;
    int countOdd = 0;

    for(int num : arr){
        if(num % 2 == 0)
            countEven++;
        else
            countOdd++;
    }

    std::cout << "The number of Even element is " << countEven << std::endl
              << "The number of Odd element is " << countOdd << std::endl;
    return 0;
}