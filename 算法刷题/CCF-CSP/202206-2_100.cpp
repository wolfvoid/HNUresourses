// -*- coding:utf-8 -*-

// File    :   202206-2.cpp
// Time    :   2024/03/23
// Author  :   wolf

#include <bits/stdc++.h>
#include <iostream>
#include <utility>
#include <vector>
#define ll long long

using namespace std;
// 时间复杂度n^2 或 n*s^2 最多在2*10^6,属于可接受范围
int main()
{
    ll n, L, S;
    scanf("%lld %lld %lld", &n, &L, &S);
    vector<pair<ll, ll>> green;
    int treasure[51][51];
    int temp[51][51];
    for (int i = 0; i < n; i++)
    {
        ll a, b;
        scanf("%lld %lld", &a, &b);
        green.push_back(make_pair(a, b));
    }
    for (int i = 0; i <= S; i++)
    {
        for (int j = 0; j <= S; j++)
        {
            scanf("%d", &treasure[S - i][j]);
        }
    }
    int ans = 0;
    for (unsigned int i = 0; i < green.size(); i++)
    {
        ll x = green[i].first;
        ll y = green[i].second;
        if (x + S > L || y + S > L)
            continue;
        for (int i1 = 0; i1 <= S; i1++)
        {
            for (int j1 = 0; j1 <= S; j1++)
            {
                temp[i1][j1] = 0;
            }
        }
        // 构造局部图
        for (unsigned int j = 0; j < green.size(); j++)
        {
            ll d_x = green[j].first;
            ll d_y = green[j].second;
            if (d_x >= x && d_y >= y && d_x <= x + S && d_y <= y + S)
            {
                temp[d_x - x][d_y - y] = 1;
            }
        }
        // 比对局部图
        bool flag = true;
        for (int i1 = 0; i1 <= S; i1++)
        {
            for (int j1 = 0; j1 <= S; j1++)
            {
                if (temp[i1][j1] != treasure[i1][j1])
                {
                    flag = false;
                    break;
                }
            }
            if (flag == false)
                break;
        }
        if (flag == true)
            ans++;
    }
    printf("%d\n", ans);

    return 0;
}
