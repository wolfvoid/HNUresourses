#include <bits/stdc++.h>
using namespace std;
int main()
{
	int n;
	double i;
	cin >> n >> i;
	//	double m[n+1];
	//	m[0]=1;
	//	double add=1+i;
	//	for (int k=1;k<=n;k++)
	//	{
	//		m[k]=1/add;
	//		add*=add;
	//	}
	// 这里手写代码只能拿到20分，考虑到应该是精度有很大的差异，只能用pow
	double ans = 0;
	for (int k = 0; k <= n; k++)
	{
		double temp;
		scanf("%lf", &temp);
		ans += (temp * pow(1 + i, -k));
	}
	printf("%f", ans);
	return 0;
}
