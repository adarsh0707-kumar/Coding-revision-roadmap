/*
7. Linear Search

Find a target element and return its index, or indicate that it is absent.
*/

#include<iostream>
#include <iterator>

int main(){

    int arr[] = {0, 1, 2, 5, 4, 3, 9, 7, 6, 8};
    int target;
    std::cout << "Enter the target element : ";
    std::cin >> target;
    int indexNum = -1;

    for (int i = 0; i < std::size(arr); i++){
        if(arr[i] == target){
            indexNum = i;
            break;
        }
        
    }

    if(indexNum != -1){
        std::cout << "Target element index number : " << indexNum << std::endl;
    }
    else{
        std::cout << "Element not found in this array." << std::endl;
    }

    return 0;
}