#include<bits/stdc++.h>
using namespace std;
//CCF202209-2
const int MAXN=300002;
int value[MAXN];
int a[31];

//01�������⣬ÿ���鱾�ļ�ֵ��������һ����
//״̬ת�Ʒ���dp[j]=max(dp[j],dp[j-a[i]]+a[i])
//dp[j]Ϊһ������Ϊj�ı��������ջ����ļ�ֵ 
int main()
{
	int n,m;
	cin>>n>>m;
	for (int i=0;i<MAXN;i++) value[i]=0; 
	for (int i=0;i<n;i++) cin>>a[i];
	for (int i=0;i<n;i++)
	{
		for (int j=MAXN-1;j>=a[i];j--)
		{
			value[j]=max(value[j],value[j-a[i]]+a[i]);
		}
	}
	for (int i=m;;i++) 
	{
		if (value[i]>=m) 
		{
			cout<<value[i]<<endl;
			break;
		}
	}

  return 0;
}

