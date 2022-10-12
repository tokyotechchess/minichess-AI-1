square root of a number

// code

// A C++ program to find floor(sqrt(x)
#include <bits/stdc++.h>
using namespace std;

int floorSqrt(int x)
{
	// Base cases
	if (x == 0 || x == 1)
		return x;

	int i = 1, result = 1;
	while (result <= x) {
		i++;
		result = i * i;
	}
	return i - 1;
}
int main()
{
	int x = 11;
	cout << floorSqrt(x) << endl;
	return 0;
}
