// -*- coding:utf-8 -*-

// File    :   202006-1.cpp
// Time    :   2024/03/26
// Author  :   wolf

#include <iostream>
#include <vector>
const int N = 1e8 + 10;
using namespace std;
vector<pair<int, int>> A, B;
#define ll long long

// 判断该点在直线的哪一侧
int func(ll t0, ll t1, ll t2, ll x, ll y)
{
    return (t0 + t1 * x + t2 * y) > 0 ? 1 : -1;
}

int main()
{
    int n, m;
    cin >> n >> m;
    // 读入n个点，使用两个vector进行存储
    for (int i = 0; i < n; i++)
    {
        ll x, y;
        char type;
        cin >> x >> y >> type;
        if (type == 'A')
            A.push_back(make_pair(x, y));
        else if (type == 'B')
            B.push_back(make_pair(x, y));
    }
    while (m--)
    {
        ll t0, t1, t2;
        cin >> t0 >> t1 >> t2;
        bool ans = true; // 标记，假设是满足的
        int A_std, B_std;
        // 设定A标准 B标准，就是在A集合和B集合各自随便抓一个点，代表它们集合中的点应该在直线哪边
        // 当且仅当A集合内的点都和A标准相等，B集合内的点都和B标准相等，再A标准不等于B标准，才满足题意
        A_std = func(t0, t1, t2, A[0].first, A[0].second);
        for (unsigned int i = 0; i < A.size(); i++)
        {
            if (func(t0, t1, t2, A[i].first, A[i].second) != A_std)
            {
                ans = false;
                break;
            }
        }
        B_std = func(t0, t1, t2, B[0].first, B[0].second);
        for (unsigned int i = 0; i < B.size(); i++)
        {
            if (func(t0, t1, t2, B[i].first, B[i].second) != B_std)
            {
                ans = false;
                break;
            }
        }
        if (A_std != B_std && ans == true)
            cout << "Yes" << endl;
        else
            cout << "No" << endl;
    }
    return 0;
}

// 9 3
// 1 1 A
// 1 0 A
// 1 -1 A
// 2 2 B
// 2 3 B
// 0 1 A
// 3 1 B
// 1 3 B
// 2 0 A
// 0 2 -3
// -3 0 2
// -3 1 1
