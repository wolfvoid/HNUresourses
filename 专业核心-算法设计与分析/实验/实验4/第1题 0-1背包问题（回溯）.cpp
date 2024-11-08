// -*- coding:utf-8 -*-

// File    :   01背包问题（回溯）.cpp
// Time    :   2023/12/14
// Author  :   wolf

#include <iostream>
using namespace std;

int w[5000];
int v[5000];
bool flag[5000];
bool ans[5000];
int now_w = 0, now_v = 0;
int n, maxw, bestv = 0;
int rest_v;

void backtrace(int depth)
{
    if (depth == n) // 到达第n层：答案
    {
        if (now_v > bestv && now_w <= maxw) // 答案是需要打印的
        {
            bestv = now_v;
            for (int i = 0; i < n; i++)
            {
                ans[i] = flag[i];
            }
        }
        return;
    }
    if (depth < n && now_w > maxw)
        return; // 剪枝：此时背包已经过重
    if (now_v + rest_v <= bestv)
        return; // 剪枝：此时剩余价值即使全部拾取也无法达到最大价值
    rest_v -= v[depth];
    // 取这个物品
    now_v += v[depth];
    now_w += w[depth];
    flag[depth] = 1;
    backtrace(depth + 1);
    now_v -= v[depth];
    now_w -= w[depth];
    flag[depth] = 0;
    // 不取这个物品
    backtrace(depth + 1);
    rest_v += v[depth];
    return;
}

int main()
{
    cin >> maxw >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> w[i] >> v[i];
        ans[i] = 0;
        flag[i] = 0;
        rest_v += v[i];
    }
    backtrace(0);
    // for (int i = 0; i < n; i++)
    //{
    //     if (ans[i])
    //         cout << i << " ";
    // }
    // cout << endl;
    // cout << "bestv=" << bestv << endl;
    cout << bestv << endl;
    return 0;
}
