/*
18. Greatest Common Divisor (GCD)

Find the GCD of two non-negative integers. Try using the Euclidean algorithm.
*/

#include <iostream>
using namespace std;

int main()
{
    long long a, b;
    cin >> a >> b;

    if (a < 0 || b < 0)
    {
        cout << "Enter non-negative numbers\n";
        return 0;
    }

    while (b != 0)
    {
        long long remainder = a % b;
        a = b;
        b = remainder;
    }

    cout << a << '\n';
}