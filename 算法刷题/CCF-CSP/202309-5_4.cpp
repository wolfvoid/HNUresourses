// -*- coding:utf-8 -*-

// File    :   202309-5.cpp
// Time    :   2024/03/25
// Author  :   wolf

#include <iostream>
#include <math.h>
#include <vector>
#define ll long long

using namespace std;
int n, m;
const ll N = 3001;
ll graph[N + 1][N + 1];
vector<ll> nxt[N + 1];
vector<pair<ll, ll>> edge;
vector<ll> W; // 保存收益w
// 推荐参考：https://blog.csdn.net/qq_45123552/article/details/136732056

ll dp1[N], dp2[N];
ll ans;
// 树形DP求树的直径
void dfs(ll u, ll father)
{
    dp1[u] = 0;
    dp2[u] = 0;
    for (unsigned int i = 0; i < nxt[u].size(); i++)
    {
        int v = nxt[u][i];
        if (v == father)
            continue;
        dfs(v, u);

        int temp = dp1[v] + graph[u][v];
        if (temp > dp1[u])
        {
            dp2[u] = dp1[u];
            dp1[u] = temp;
        }
        else if (temp > dp2[u])
        {
            dp2[u] = temp;
        }
    }
    ans = max(ans, dp1[u] + dp2[u]);
    return;
}

int main()
{
    cin >> n >> m;
    for (int i = 0; i < n - 1; i++)
    {
        ll u, v, w, b;
        cin >> u >> v >> w >> b;
        graph[u][v] = b - w;
        graph[v][u] = b - w;
        nxt[u].push_back(v);
        nxt[v].push_back(u);
        edge.push_back(make_pair(u, v));
        W.push_back(w);
    }
    ans = 0;
    dfs(1, 0);
    cout << ans << endl;
    for (int i = 0; i < m; i++)
    {
        ll x, y;
        cin >> x >> y;
        graph[edge[x - 1].first][edge[x - 1].second] += (W[x - 1] - y);
        graph[edge[x - 1].second][edge[x - 1].first] += (W[x - 1] - y);
        W[x - 1] = y;

        ans = 0;
        dfs(1, 0);
        cout << ans << endl;
    }
    return 0;
}
