/*
14. Fibonacci Sequence

Print the first n Fibonacci numbers using iteration.
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
        cout << "Enter a non-negative number\n";
        return 0;
    }

    long long a = 0, b = 1;

    for (int i = 0; i < n; i++)
    {
        cout << a << ' ';

        if (i < n - 1)
        {
            if (a > LLONG_MAX - b)
            {
                cout << "\nOverflow\n";
                return 0;
            }

            long long next = a + b;
            a = b;
            b = next;
        }
    }

    cout << '\n';
}