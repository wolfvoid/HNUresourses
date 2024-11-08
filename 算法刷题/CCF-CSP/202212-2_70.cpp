#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,m;
	cin>>n>>m;
	int depend[m+1],cost[m+1],early[m+1],late[m+1];
	bool flag[m+1];
	for (int i=1;i<=m;i++) cin>>depend[i];
	for (int i=1;i<=m;i++) cin>>cost[i];
	for (int i=1;i<=m;i++) flag[i]=0;
	queue<int> q;
	for (int i=1;i<=m;i++)
		if (depend[i]==0) 
		{
			q.push(i);
			flag[i]=1;
			early[i]=1;
		}
	int maxnum=0;
	while (!q.empty())
	{
		int now=q.front();
		for (int i=1;i<=m;i++)
		{
			if (flag[i]==0 && depend[i]==now)
			{
				q.push(i);
				flag[i]=1;
				early[i]=early[now]+cost[now];
			}
		}
		q.pop();
	}
	for (int i=1;i<=m;i++) cout<<early[i]<<" ";
	cout<<endl;

  return 0;
}

