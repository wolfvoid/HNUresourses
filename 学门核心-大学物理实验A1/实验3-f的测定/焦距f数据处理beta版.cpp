#include<bits/stdc++.h>
using namespace std;
int main()
{
	while(1)
	{
		cout<<"数据个数："<<endl;
	int n;
	double sum=0,aver=0;
	double m[10];
	cin>>n;
	for (int i=0;i<n;i++)
	{
		cin>>m[i];
		sum+=m[i];
	 } 
	aver=sum/n;
	cout<<endl;
	cout<<"f-average="<<fixed<<setprecision(2)<<aver<<endl;
	double total=0;
	for (int i=0;i<n;i++)
	{
		double temp=m[i]-aver;
		cout<<"Δf"<<i+1<<"="<<temp<<endl;
		total+=(temp*temp);
	 } 
	double zeta=sqrt((total/n/(n-1)));
	cout<<endl;
	cout<<"σf-average="<<fixed<<setprecision(4)<<zeta<<endl;
	cout<<endl;
	cout<<"f=f±σf-average="<<fixed<<setprecision(2)<<aver<<fixed<<setprecision(4)<<"±"<<zeta<<endl;
	system("pause");
	system("cls");
	}
	

  return 0;
}

