/*
31. Check Whether a Number Is a Power of Two

Determine whether a positive integer is a power of two. Bonus: use a bitwise operation.
*/

#include <iostream>
using namespace std;

int main()
{
    int n;
    cin >> n;

    bool result = n > 0 && (n & (n - 1)) == 0;

    cout << (result ? "Power of two" : "Not a power of two")
         << '\n';
}