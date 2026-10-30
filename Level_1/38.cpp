/*
38. Diamond Pattern

Print a symmetric diamond made of stars for a given height. Define whether the height is odd or even and handle it consistently.

			*
		* * *
	* * * * *
* * * * * * *
	* * * * *
		* * *
			*
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
		for (int j = 0; j < n - i; j++)
			cout << ' ';

		for (int j = 0; j < 2 * i - 1; j++)
			cout << '*';

		cout << '\n';
	}

	for (int i = n - 1; i >= 1; i--)
	{
		for (int j = 0; j < n - i; j++)
			cout << ' ';

		for (int j = 0; j < 2 * i - 1; j++)
			cout << '*';

		cout << '\n';
	}
}