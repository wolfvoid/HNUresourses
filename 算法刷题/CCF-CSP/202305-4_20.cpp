// -*- coding:utf-8 -*-

// File    :   202305-4.cpp
// Time    :   2024/03/25
// Author  :   wolf

#include <iostream>
#include <math.h>

using namespace std;
int n, m, k;
const int N = 10;
const int K = 15;
int station[N][K];
const int M = 50;
int c[N]; // 排列
struct line
{
    int n1, n2;
    int line_cost[K][K];
};
struct line line[M];

int ans = 0x3f3f3f3f;
void find(int depth)
{
    if (depth != n)
    {
        for (int i = 0; i < k; i++)
        {
            c[depth] = i;
            find(depth + 1);
        }
    }
    else if (depth == n) // 已生成变电站排列
    {
        int sum = 0;
        for (int i = 0; i < m; i++)
        {
            sum += line[i].line_cost[c[line[i].n1]][c[line[i].n2]];
        }
        for (int i = 0; i < n; i++)
        {
            sum += station[i][c[i]];
        }
        ans = min(ans, sum);
    }
}
int main()
{
    cin >> n >> m >> k;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < k; j++)
        {
            cin >> station[i][j];
        }
    }
    for (int i = 0; i < m; i++)
    {
        cin >> line[i].n1 >> line[i].n2;
        for (int j1 = 0; j1 < k; j1++)
        {
            for (int j2 = 0; j2 < k; j2++)
            {
                cin >> line[i].line_cost[j1][j2];
            }
        }
    }
    find(0);
    cout << ans;
    return 0;
}
