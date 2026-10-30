/*
40. Hollow Square Pattern

For n = 4, print:

****
*  *
*  *
****
*/

#include <iostream>
using namespace std;

int main()
{
    int n;
    cin >> n;

    if (n <= 0)
        return 0;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (i == 1 || i == n || j == 1 || j == n)
                cout << "* ";
            else
                cout << "  ";
        }

        cout << '\n';
    }
}