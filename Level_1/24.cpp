/*
24. Find the First and Last Digit

Extract the first and last digits of a non-negative integer without converting it to a string.
*/

#include <iostream>
using namespace std;

int main()
{
    long long n;
    cin >> n;

    if (n < 0)
    {
        cout << "Enter a non-negative number\n";
        return 0;
    }

    int last = static_cast<int>(n % 10);
    long long temp = n;

    while (temp >= 10)
        temp /= 10;

    cout << "First digit: " << temp << '\n';
    cout << "Last digit: " << last << '\n';
}