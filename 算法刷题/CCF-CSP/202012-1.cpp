#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n;
	cin>>n;
	int ans=0;
	for (int i=0;i<n;i++) 
	{
		int w,s;
		cin>>w>>s;
		ans+=w*s;
	}
	ans=max(0,ans);
	cout<<ans<<endl;
	



  return 0;
}

