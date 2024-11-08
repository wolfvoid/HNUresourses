#include<bits/stdc++.h>
using namespace std;
int main()
{
	int m;
	cin>>m;
	int y[m],result[m];
	const int maxsize=10e8+1;
	int ymax=0;
	int ymin=maxsize;
	int *success = new int[maxsize];
	int *fail = new int[maxsize];
	memset(success,0,sizeof(success));
	memset(fail,0,sizeof(fail));
	for (int i=0;i<m;i++)
	{
		cin>>y[i]>>result[i];
		ymax=max(ymax,y[i]);
		ymin=min(ymin,y[i]);
		if (result[i]) success[y[i]]++;
			else fail[y[i]]++;
	}
	
	int *s = new int[ymax+1];//s是success从后往前的差分数组 
	int *f = new int[ymax+1];//f是fail从前往后的差分数组
	memset(s,0,sizeof(s));
	memset(f,0,sizeof(f));
	s[ymax]=success[ymax];
	for (int i=ymax-1;i>=ymin;i--)
	{
		s[i]=success[i]+s[i+1]; 
	}
	f[ymin]=fail[ymin];
	for (int i=ymin+1;i<=ymax;i++)
	{
		f[i]=fail[i]+f[i-1]; 
	}
	int ans=0;
	int maxcount=0;//计数 
//	for (int i=ymin;i<=ymax;i++) cout<<s[i]<<" ";
//	cout<<endl;
//	for (int i=ymin;i<=ymax;i++) cout<<f[i]<<" ";
//	cout<<endl;
	for (int i=0;i<m;i++)
	{
		int now;
		if (y[i]==0) now=s[y[i]];
		else now=(s[y[i]]+f[y[i]-1]);
		if (now>=maxcount)
		{
			if (now==maxcount && y[i]>ans) ans=y[i];
			if (now>maxcount) 
			{
				ans=y[i];
				maxcount=now;
			}
		}
	}
	cout<<ans<<endl;

	return 0;
}

