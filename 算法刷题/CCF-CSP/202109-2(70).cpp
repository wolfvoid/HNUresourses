#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n;
	cin>>n;
	int a[n+1];
	int maxn=0;
	for (int i=0;i<n;i++) 
	{
		cin>>a[i];
		maxn=max(maxn,a[i]);
	}
	a[n]=0;
	int ans=0;
	for (int i=1;i<=maxn;i++)
	{
		for (int j=0;j<n;j++)
		{
			if (a[j]<i) a[j]=0;
		}
		int flag_prev=(a[0] ? 1 : 0);
		int flag_now;
		int count=0;
		for (int j=0;j<=n;j++)
		{
			flag_now=(a[j] ? 1 : 0);
			count+=((flag_prev!=flag_now && flag_prev) ? 1 : 0);
			flag_prev=flag_now;
		}
		ans=max(ans,count);
	}
	cout<<ans<<endl;


  return 0;
}

