/*
25. Swap Two Numbers

Swap two variables, first using a temporary variable and then without one.
*/

#include <iostream>
using namespace std;

void swapNumbers(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

int main()
{
    int a, b;
    cin >> a >> b;

    swapNumbers(a, b);

    cout << "a = " << a << '\n';
    cout << "b = " << b << '\n';
}