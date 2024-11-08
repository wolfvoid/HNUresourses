#include <bits/stdc++.h>
using namespace std;
int main()
{
	int n, L, r, t;
	cin >> n >> L >> r >> t;
	int num[n + 1][n + 1];
	int sum[n + 1][n + 1];
	memset(num, 0, sizeof(num));
	memset(sum, 0, sizeof(sum));
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
		{
			cin >> num[i][j];
		}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
		{
			sum[i][j] = num[i][j] + sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
		}
	int ans = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
		{
			int now;
			int x1 = max(1, i - r);
			int y1 = max(1, j - r);
			int x2 = min(n, i + r);
			int y2 = min(n, j + r);
			now = sum[x2][y2] - sum[x2][y1 - 1] - sum[x1 - 1][y2] + sum[x1 - 1][y1 - 1];
			int number = (y2 - y1 + 1) * (x2 - x1 + 1);
			if (now <= number * t)
				ans++;
		}
	cout << ans << endl;

	return 0;
}
