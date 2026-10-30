/*
13. Factorial of a Number

Calculate \(n!\) using a loop. Handle 0! = 1 and consider integer overflow.
*/

#include <iostream>
#include <climits>
using namespace std;

int main()
{
    int n;
    cin >> n;

    if (n < 0)
    {
        cout << "Factorial is undefined for negative numbers\n";
        return 0;
    }

    long long fact = 1;

    for (int i = 2; i <= n; i++)
    {
        if (fact > LLONG_MAX / i)
        {
            cout << "Overflow\n";
            return 0;
        }
        fact *= i;
    }

    cout << fact << '\n';
}