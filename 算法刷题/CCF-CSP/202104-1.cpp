#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,m,L;
	cin>>n>>m>>L;
	int x[L];
	for (int i=0;i<L;i++) x[i]=0;
	int temp;
	for (int i=0;i<n;i++)
	   for (int j=0;j<m;j++) 
	   	{
	   		cin>>temp;
	   		x[temp]++;
		}
	for (int i=0;i<L;i++) cout<<x[i]<<" ";


  return 0;
}

