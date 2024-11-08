// -*- coding:utf-8 -*-

// File    :   202009-1.cpp
// Time    :   2024/03/23
// Author  :   wolf

#include <iostream>
#include <math.h>

using namespace std;

int main()
{
    // 读入与计算
    int n, x, y;
    scanf("%d %d %d", &n, &x, &y);
    int m[n];
    for (int i = 0; i < n; i++)
    {
        int a, b;
        scanf("%d %d", &a, &b);
        int d = pow(abs(x - a), 2) + pow(abs(y - b), 2);
        m[i] = d;
    }

    // 简单版top_k问题，这里是top3，使用if_choose数组做标记，遍历三次，分别找到单次最小的
    bool if_choose[n];
    for (int i = 0; i < n; i++)
    {
        if_choose[i] = 0;
    }
    for (int k = 0; k < 3; k++)
    {
        int ans;
        int minnum = 8e6 + 1;
        for (int i = 0; i < n; i++)
        {
            if (if_choose[i] == 0 && m[i] < minnum)
            {
                minnum = m[i];
                ans = i;
            }
        }
        if_choose[ans] = 1;
        printf("%d\n", ans + 1);
    }
    return 0;
}
