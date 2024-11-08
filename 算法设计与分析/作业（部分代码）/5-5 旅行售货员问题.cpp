// -*- coding:utf-8 -*-

// File    :   5-5 旅行售货员问题.cpp
// Time    :   2023/12/30
// Author  :   wolf

#include <iostream>

using namespace std;
int const MAXINT = 99999;
int map[1000][1000];
int v, e, best_cost = MAXINT, now_cost = 0;
int now_order[1000]; // 储存当前排列解向量
int ans[1000];       // 储存结果排列解向量
int upbound;

void swap(int a, int b)
{
    int temp = now_order[a];
    now_order[a] = now_order[b];
    now_order[b] = temp;
};

void backtrack(int depth)
{
    if (depth == v - 1) // 到达答案层
    {
        if (map[now_order[depth]][now_order[0]] != -1) // 能跟第一个相连
        {
            now_cost += map[now_order[depth]][now_order[0]];
            if (now_cost < best_cost) // 更优，保存结果
            {
                best_cost = now_cost;
                for (int i = 0; i < v; i++)
                {
                    ans[i] = now_order[i];
                }
            }
            now_cost -= map[now_order[depth]][now_order[0]];
        }
    }
    else
    {
        for (int i = depth; i < v; i++) // 生成排列树当前向量中depth位置的节点编号（第depth个访问哪个节点）
        {
            if (map[now_order[depth - 1]][now_order[i]] != -1) // 前一节点到当前的这个节点有可达边
            {
                if (now_cost + map[now_order[depth - 1]][now_order[i]] <= upbound)
                // 剪枝：若当前步骤使得费用和就大于上界了，不必继续
                {
                    swap(i, depth);
                    now_cost += map[now_order[depth - 1]]
                                   [now_order[depth]];
                    backtrack(depth + 1);
                    now_cost -= map[now_order[depth - 1]]
                                   [now_order[depth]];
                    swap(i, depth);
                }
            }
        }
    }
    return;
}
int main()
{
    cin >> v >> e;
    for (int i = 0; i < v; i++)
        for (int j = 0; j < v; j++)
            map[i][j] = -1;
    for (int i = 0; i < e; i++)
    {
        int a, b, weight;
        cin >> a >> b >> weight;
        map[a][b] = weight;
        map[b][a] = weight;
    }
    // 剪枝预备：
    for (int i = 0; i < v; i++)
    {
        int i_out_max = 0; // 存储从i节点向外
        for (int j = 0; j < v; j++)
        {
            i_out_max = max(i_out_max, map[i][j]);
        }
        upbound += i_out_max;
    }

    // 指定从0号节点开始遍历
    // 反正最后每一个节点都需要遍历过
    for (int i = 0; i < v; i++)
        now_order[i] = i; // 初始按照递增顺序（初始顺序是无所谓的，只要保证都能遍历一遍就可以）
    backtrack(1);         // 0号节点已固定，搜索从1号节点开始的全排列
    cout << best_cost << endl;
    return 0;
}
