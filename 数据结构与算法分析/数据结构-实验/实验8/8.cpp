#include<bits/stdc++.h>
using namespace std;

long long int jiecheng(int n)
{
	long long int temp=1;
	for (int i=1;i<=n;i++)
	{
		temp*=i;
	}
	return temp;
} 

long long int combination(int n,int m)
{
	return (jiecheng(n)/(jiecheng(m)*jiecheng(n-m)));
}
int main()
{
	int n,m;
	cin>>n>>m;
	cout<<combination(n+m-2,m-1);
  return 0;
}

