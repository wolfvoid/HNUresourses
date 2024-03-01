#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,m;
	cin>>n>>m;
	long long int map[m+1][n+1];
	for (int i=1;i<=m;i++)
		for (int j=1;j<=n;j++) 
		{
			if (i==1 || j==1) map[i][j]=1;
			else map[i][j]=map[i-1][j]+map[i][j-1];
		}
	cout<<map[m][n];


  return 0;
}

