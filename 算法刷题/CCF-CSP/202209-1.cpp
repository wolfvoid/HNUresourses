#include<bits/stdc++.h>
using namespace std;
int main()
{
	long long n,m;
	cin>>n>>m;
	int a[n+1],b[n+1],c[n+1];
	c[0]=1;
	int sum=0;
	for (int i=1;i<=n;i++)
	{
		cin>>a[i];
		c[i]=c[i-1]*a[i];
//		cout<<"c["<<i<<"]="<<c[i]<<endl;
		int temp=m%c[i];
//		cout<<"temp="<<temp<<endl;
		b[i]=(temp-sum)/c[i-1];
//		cout<<"b["<<i<<"]="<<b[i]<<endl;
		sum=temp;
//		cout<<"sum="<<sum<<endl;
	}
	for (int i=1;i<=n;i++) cout<<b[i]<<" ";


  return 0;
}

