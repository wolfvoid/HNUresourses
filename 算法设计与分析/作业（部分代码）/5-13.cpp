// -*- coding:utf-8 -*-

// File    :   5-13.cpp
// Time    :   2023/12/25
// Author  :   wolf

#include <iostream>

using namespace std;
const int MAXNUM = 9999999;
int c[21][21];
int x[21];
int nowcost = 0, mincost = MAXNUM, n;

void swap(int a, int b)
{
    int temp = x[a];
    x[a] = x[b];
    x[b] = temp;
}

void backtrack(int depth)
{
    if (depth == n) // 答案层
    {
        mincost = min(mincost, nowcost);
        // cout << nowcost << endl;
        // 不需要输出解向量，故不用保存解向量
    }
    else
    {
        for (int i = depth; i < n; i++)
        {
            // depth当前人，i为待分发物品序号，人不动，发物品
            nowcost += c[x[i]][depth];
            swap(i, depth);
            backtrack(depth + 1);
            swap(i, depth);
            nowcost -= c[x[i]][depth];
        }
    }
}

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> c[i][j];
        }
    }
    for (int i = 0; i < n; i++)
        x[i] = i;
    backtrack(0);
    cout << mincost << endl;

    return 0;
}
