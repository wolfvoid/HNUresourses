// -*- coding:utf-8 -*-

// File    :   202006-2.cpp
// Time    :   2024/03/25
// Author  :   wolf

#include <algorithm>
#include <iostream>
#include <vector>
#define ll long long

using namespace std;
vector<pair<int, int>> v1, v2;
bool cmp(pair<int, int> a, pair<int, int> b)
{
    return a.first < b.first;
}

int main()
{
    int n, a, b;
    cin >> n >> a >> b;
    for (int i = 0; i < a; i++)
    {
        int index, value;
        cin >> index >> value;
        v1.push_back(make_pair(index, value));
    }
    for (int i = 0; i < b; i++)
    {
        int index, value;
        cin >> index >> value;
        v2.push_back(make_pair(index, value));
    }
    ll ans = 0;
    // 30分答案
    // for (unsigned int i = 0; i < v1.size(); i++)
    // {
    //     for (unsigned int j = 0; j < v2.size(); j++)
    //     {
    //         if (v1[i].first == v2[j].first)
    //             ans += v1[i].second * v2[j].second;
    //     }
    // }

    // 100分答案
    sort(v1.begin(), v1.end(), cmp);
    sort(v2.begin(), v2.end(), cmp);
    unsigned int v2i = 0;
    for (unsigned int v1i = 0; v1i < v1.size(); v1i++)
    {
        while (v2[v2i].first < v1[v1i].first && v2i < v2.size())
            v2i++;
        if (v1[v1i].first == v2[v2i].first)
            ans += v1[v1i].second * v2[v2i].second;
    }
    cout << ans << endl;
    return 0;
}

// 10 3 4
// 4 5
// 7 -3
// 10 1
// 1 10
// 4 20
// 5 30
// 7 40
