/*
33. Right-Angled Star Triangle

For n = 4, print:
*
**
***
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
        for (int j = 1; j <= i; j++)
            cout << "* ";

        cout << '\n';
    }
}