#include <bits/stdc++.h>
using namespace std;
int main()
{
	// 70分代码的思路我们是站在人的角度处理问题，即按照他的思路（即题目要求）一步一步处理问题，
	// 优先解决人的需求；
	// 100分代码思路中，我们优先处理场所需求，即判断出进入该场所需要的最早时间核酸报告（left）
	// 和最晚时间核酸报告（right）后考虑人的需求，即人在left～right这个时间范围内进入场所都是符合要求的，
	// 可将问题转化为对区间的处理：核酸检测的时间t+等待核酸检测的时间k所在的点有多少个满足条件的场所
	int n, m, k;
	cin >> n >> m >> k;
	int t[n], c[n];
	int maxt = 0;
	for (int i = 0; i < n; i++)
	{
		cin >> t[i] >> c[i];
		maxt = max(t[i], maxt);
	}

	const int maxnum = 300000;
	// 测试数据中有qm>tm的数据（qm范围到200000，写到200000可得70分）
	// 还需要考虑到qm+k有可能最大到达300000，写到300000可得100分
	int count[maxnum + 1];
	for (int i = 0; i <= maxnum; i++)
		count[i] = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = max(0, t[i] - c[i] + 1); j <= t[i]; j++)
			count[j]++;
	}
	//	for (int i=0;i<=maxt;i++) cout<<count[i]<<" ";
	//	cout<<endl;
	for (int i = 0; i < m; i++)
	{
		int temp;
		cin >> temp;
		cout << count[temp + k] << endl;
	}
	return 0;
}
