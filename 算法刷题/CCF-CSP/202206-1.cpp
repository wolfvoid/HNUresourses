#include <bits/stdc++.h>
using namespace std;
int main()
{
	int n;
	cin >> n;
	double a[n];
	double sum = 0;
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
		sum += a[i];
	}
	double average = sum / n;
	double dtotal = 0;
	for (int i = 0; i < n; i++)
	{
		dtotal += (a[i] - average) * (a[i] - average);
	}
	dtotal /= n;
	for (int i = 0; i < n; i++)
	{
		cout << (a[i] - average) / sqrt(dtotal) << endl;
	}
	return 0;
}
