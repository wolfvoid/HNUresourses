#include <bits/stdc++.h>
using namespace std;
// 70分
int main()
{
	int n, L, S;
	cin >> n >> L >> S;
	vector<pair<int, int>> tree;
	bool mapl[L + 1][L + 1];
	bool maps[S + 1][S + 1];
	fill(mapl[0], mapl[0] + (L + 1) * (L + 1), 0);
	for (int i = 0; i < n; i++)
	{
		int x, y;
		cin >> x >> y;
		mapl[L - x][y] = 1;
		pair<int, int> temp(L - x, y);
		tree.push_back(temp);
	}
	vector<pair<int, int>> treasure;
	int tsnum = 0;
	for (int i = 0; i <= S; i++)
	{
		for (int j = 0; j <= S; j++)
		{
			cin >> maps[i][j];
			if (maps[i][j] == 1)
			{
				pair<int, int> temp(i, j);
				treasure.push_back(temp);
				tsnum++;
			}
		}
	}
	int ans = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < tsnum; j++)
		{
			int x = tree[i].first, y = tree[i].second;
			int a = treasure[j].first, b = treasure[j].second;
			//			cout<<"x,y "<<x<<" "<<y<<endl;
			//			cout<<"a,b "<<a<<" "<<b<<endl;
			//			cout<<x-a<<" "<<x+S-a<<" "<<y-b<<" "<<y+S-b<<endl;
			if (x - a >= 0 && x + S - a <= L && y - b >= 0 && y + S - b <= L)
			{
				//				for(int kx=0;kx<=S;kx++)
				//				{
				//					for (int ky=0;ky<=S;ky++)
				//					{ cout<<mapl[x-a+kx][y-b+ky]<<" ";}
				//					cout<<endl;
				//			    }
				//			    cout<<endl;
				//			    for(int kx=0;kx<=S;kx++)
				//				{
				//					for (int ky=0;ky<=S;ky++)
				//					{ cout<<maps[kx][ky]<<" ";}
				//					cout<<endl;
				//			    }
				int flag = 1;
				for (int kx = 0; kx <= S; kx++)
				{
					for (int ky = 0; ky <= S; ky++)
					{
						if (mapl[x - a + kx][y - b + ky] != maps[kx][ky])
						{
							flag = 0;
							break;
						}
					}
					if (flag == 0)
						break;
				}
				if (flag == 1)
					ans++;
			}
			//			cout<<endl;
		}
	}
	cout << ans / tsnum << endl;

	return 0;
}
