/*
17. Palindrome Number

Check whether a non-negative integer reads the same forward and backward. Example: 1221.
*/

#include <iostream>
using namespace std;

int main()
{
    int n;
    cin >> n;

    if (n < 0)
    {
        cout << "Not a palindrome\n";
        return 0;
    }

    int original = n;
    long long reversed = 0;

    while (n > 0)
    {
        reversed = reversed * 10 + n % 10;
        n /= 10;
    }

    cout << (reversed == original ? "Palindrome" : "Not a palindrome")
         << '\n';
}