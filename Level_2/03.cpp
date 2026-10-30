/*
3. Calculate Array Sum and Average

Calculate the sum and average of all elements.
*/

#include<iostream>

using namespace std;

int main(){
    int arr[] = {1, 3, 4, 5, 9, 4, 6, 33, 0, 3, -4};

    int arrSize = sizeof(arr) / sizeof(arr[0]);

    int sum = 0;
    float average = 0;

    for (int i = 0; i < arrSize; i++)
    {
        sum += arr[i];
    }

    average = float(sum) / arrSize;

    cout << "Sum of an array: " << sum << endl
         << "Average of an array: " << average << endl;

    return 0;
}