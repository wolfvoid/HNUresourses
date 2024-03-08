// -*- coding:utf-8 -*-

// File    :   P1159 运动员最佳匹配问题.cpp
// Time    :   2023/12/20
// Author  :   wolf

#include <iostream>

using namespace std;

int p[20][20], q[20][20], r[20][20];
int greedy_maxnow[20], greedy_maxrest[20];
int girl_num[20];
int n, bestv = 0, nowv = 0;

void swap(int a, int b)
{
    int temp;
    temp = girl_num[a];
    girl_num[a] = girl_num[b];
    girl_num[b] = temp;
}

void backtrack(int depth)
{
    if (depth == n) // 如果到达答案层
    {
        bestv = max(nowv, bestv);
    }
    else
    {
        if (nowv + greedy_maxrest[depth] <= bestv)
            return;                     // 剪枝：若此层与后面所有贪心价值加起来都达不到最大值，直接退出
        for (int i = depth; i < n; i++) // 排列树检索
        {
            swap(depth, i);
            nowv += r[depth][girl_num[depth]];
            backtrack(depth + 1);
            nowv -= r[depth][girl_num[depth]];
            swap(depth, i);
        }
    }
    return;
}

int main()
{
    cin >> n;
    // 读入
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> p[i][j];
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> q[i][j];
        }
    }
    // 预处理
    for (int i = 0; i < n; i++)
    {
        int maxnow = 0;
        for (int j = 0; j < n; j++)
        {
            r[i][j] = p[i][j] * q[j][i]; // r[i][j]表示男i和女j配对的价值
            maxnow = max(maxnow, r[i][j]);
        }
        greedy_maxnow[i] = maxnow; // greedy_maxnow[i]表示男i和最优的女配对的贪心价值
    }
    // 预处理：剪枝优化
    for (int i = n - 1; i >= 0; i--)
    {
        if (i == n - 1)
            greedy_maxrest[i] = greedy_maxnow[i]; // greedy_maxrest[i]表示剩下男i，男i+1，……，一直到男n-1都和最优的女配对的贪心价值
        else
            greedy_maxrest[i] = greedy_maxrest[i + 1] + greedy_maxnow[i];
    }
    for (int i = 0; i < n; i++)
        girl_num[i] = i;
    backtrack(0);
    cout << bestv << endl;
    return 0;
}
