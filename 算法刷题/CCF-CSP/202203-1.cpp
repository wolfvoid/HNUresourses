#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,k;
	cin>>n>>k;
	int m[n+1];
	for (int i=0;i<=n;i++) m[i]=0;
	int count=0;
	for (int i=0;i<k;i++) 
	{
		int xi,yi;
		cin>>xi>>yi;
		if (!yi==0 && m[yi]==0) count++;
		m[xi]=1;
	}
	cout<<count<<endl;


  return 0;
}

