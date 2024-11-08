// -*- coding:utf-8 -*-

// File    :   4-13 非单位时间任务安排问题.cpp
// Time    :   2023/12/30
// Author  :   wolf

#include <algorithm>
#include <iostream>

using namespace std;
int const MAXINT = 99999;
struct task
{
    int t; // cost time
    int d; // deadline
    int w; //  weight
} task[1000];

bool cmp(struct task a, struct task b)
{
    return a.d < b.d;
}

int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> task[i].t >> task[i].d >> task[i].w;
    }
    sort(task, task + n, cmp);
    int maxd = task[n - 1].d;
    int dp[n][maxd + 1]; // dp[i][j] 到第i个任务，截止时间为j时的最小惩罚
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= maxd; j++)
        {
            dp[i][j] = MAXINT;
        }
    }
    for (int j = 0; j <= maxd; j++)
    {
        if (j < task[0].d)
            dp[0][j] = task[0].w;
        else
            dp[0][j] = 0;
    }
    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j <= maxd; j++)
        {
            int drop = dp[i - 1][j] + task[i].w;
            dp[i][j] = drop;
            if (min(j, task[i].d) - task[i].t >= 0)
            {
                int fetch = dp[i - 1][min(j, task[i].d) - task[i].t];
                dp[i][j] = min(drop, fetch);
            }
        }
    }
    cout << dp[n - 1][maxd] << endl;
    // for (int i = 0; i < n; i++)
    // {
    //     for (int j = 0; j <= maxd; j++)
    //     {
    //         cout << dp[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    return 0;
}
