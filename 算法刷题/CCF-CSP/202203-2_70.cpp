#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,m,k;
	cin>>n>>m>>k;
	int t[n],c[n];
	for (int i=0;i<n;i++)
	{
		cin>>t[i]>>c[i];
	} 
	for (int i=0;i<m;i++)
	{
		int now;
		int count=0;
		cin>>now;
		for (int j=0;j<n;j++)
			if ((t[j]-c[j]+1<=now+k) && now+k<=t[j]) count++;
		cout<<count<<endl;
	}
  return 0;
}
