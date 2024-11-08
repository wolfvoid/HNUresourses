#include <bits/stdc++.h>
using namespace std;
int main()
{
	int n, m;
	cin >> n >> m;
	int depend[m + 1], cost[m + 1], early[m + 1];
	bool flag[m + 1];
	for (int i = 1; i <= m; i++)
		cin >> depend[i];
	for (int i = 1; i <= m; i++)
		cin >> cost[i];
	for (int i = 1; i <= m; i++)
		flag[i] = 0;
	queue<int> q;
	for (int i = 1; i <= m; i++)
		if (depend[i] == 0)
		{
			q.push(i);
			flag[i] = 1;
			early[i] = 1;
		}
	int maxnum = 0;
	while (!q.empty())
	{
		int now = q.front();
		for (int i = 1; i <= m; i++)
		{
			if (flag[i] == 0 && depend[i] == now)
			{
				q.push(i);
				flag[i] = 1;
				early[i] = early[now] + cost[now];
				maxnum = max(maxnum, early[i] + cost[i]);
				// 本句用来确定最长时间
			}
		}
		q.pop();
	}
	for (int i = 1; i <= m; i++)
		cout << early[i] << " ";
	cout << endl;

	// 以上为70分代码，后30分参考了CSDN
	int add[m + 1];
	for (int i = 1; i <= m; i++)
		add[i] = 0;
	if (maxnum - 1 <= n)
	{
		for (int i = m; i >= 1; i--)
		{
			add[i] += cost[i];
			if (depend[i])
				add[depend[i]] = max(add[depend[i]], add[i]);
			// 若该项存在前导项depend[i]，则其前导项depend[i]的时长需要继承上该项的时间
			// 但考虑到可能存在多个项都以depend[i]为前导项，需要选择一个最大的时间
		}
		for (int i = 1; i <= m; i++)
		{
			cout << n + 1 - add[i] << " ";
		}
	}

	return 0;
}
