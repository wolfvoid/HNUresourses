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
// 时间复杂度n^2*s^2,最大会在2.5*10^9，会超一点点时间

int main()
{
    ll n, L, S;
    scanf("%lld %lld %lld", &n, &L, &S);
    vector<pair<ll, ll>> green;
    int treasure[51][51];
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
        bool flag = true; // green上每个节点是否可能作为左下角
        if (green[i].first + S > L || green[i].second + S > L)
            continue; // green图放不下treasure图，显然不可能

        // 对于每一个green图的树节点，假设它就是treasure左下角的树。
        // 接下来对于用treasure图去和green图比较，看能否重合
        for (unsigned int j_x = 0; j_x <= S; j_x++)
        {
            for (unsigned int j_y = 0; j_y <= S; j_y++)
            {
                ll target_x = green[i].first + j_x;
                ll target_y = green[i].second + j_y;
                pair<ll, ll> target = make_pair(target_x, target_y);
                bool weather_find = false;
                if (treasure[j_x][j_y] == 1)
                    weather_find = true;
                bool if_find = false; // treasure图上的每个节点是否都有对应
                for (unsigned int k = 0; k < green.size(); k++)
                {
                    if (target == green[k])
                    {
                        if_find = true;
                        break;
                    }
                }
                if (weather_find != if_find)
                {
                    flag = false;
                    break;
                }
            }
        }
        if (flag == true)
            ans++;
    }
    printf("%d\n", ans);

    return 0;
}
