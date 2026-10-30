/*
Question 11: Count the Digits
Difficulty: Easy

Write a C++ program that counts the number of digits in a given non-negative integer without converting it to a string.

Examples:
Input: 12345
Output: 5


Input: 7
Output: 1


Input: 0
Output: 1


Requirements
- Use a loop and arithmetic operations.
- Handle 0 correctly.
- Do not convert the number to a string.
- Bonus: Handle negative integers too, counting only their digits (not the minus sign).
*/

#include <iostream>
using namespace std;

int main()
{
    long long num;
    cin >> num;

    int count = 0;

    do
    {
        count++;
        num /= 10;
    } while (num != 0);

    cout << count << '\n';
}