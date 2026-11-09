/*
20. GCD and LCM Functions

Implement separate functions to calculate the GCD and LCM of two integers.
*/

#include <iostream>
#include<climits>
#include<cmath>

using namespace std;

long long gcd(long long a, long long b)
{
    a = abs(a);
    b = abs(b);
    while (b != 0)
    {
        long long r = a % b;
        a = b;
        b = r;
    }
    return a;
}

long long lcm(long long a, long long b){

    if (a == 0 || b == 0)
    {
        cout << 0 << '\n';
        return 0;
    }

    long long g = gcd(a, b);
    long long reduced = a / g;

    if (reduced > LLONG_MAX / abs(b))
    {
        cout << "Error: LCM overflowed 64-bit integer limit.\n";
        return -1;
    }

    return reduced * abs(b);
}

int main()
{
    long long a, b;
    cout << "Enter two integers: ";
    if (!(cin >> a >> b))
        return 0;

    cout << "GCD(" << a << ", " << b << ") = " << gcd(a, b) << "\n";

    long long lcmResult = lcm(a, b);
    if (lcmResult != -1)
    {
        cout << "LCM(" << a << ", " << b << ") = " << lcmResult << "\n";
    }

    return 0;
}