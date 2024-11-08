#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,N;
	cin>>n>>N;
	int a[n+2];
	a[0]=0;
	for (int i=1;i<=n;i++) cin>>a[i];
	a[n+1]=N;
//	for (int i=0;i<=n+1;i++) cout<<a[i]<<" ";
	int ans=0;
	for (int i=1;i<=n+1;i++)
	{
		ans+=((a[i]-a[i-1])*(i-1));
	}
	cout<<ans<<endl;


  return 0;
}

