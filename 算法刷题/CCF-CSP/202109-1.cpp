#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n;
	cin>>n;
	int a[n];
	for (int i=0;i<n;i++) cin>>a[i];
	 int max=0,min=0;
	int m=a[0]; 
	int flag=0;
	for (int i=0;i<n;i++) 
	{
		max+=a[i];
		if (flag==0 && i && a[i]==a[i-1]) 
		{
			flag=1;
		}
		if (flag==1 && a[i]==a[i-1]) min+=0;
		else min+=a[i];
	}
	cout<<max<<endl<<min<<endl;
  return 0;
}

