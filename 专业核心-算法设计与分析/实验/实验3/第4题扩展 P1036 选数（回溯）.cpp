// -*- coding:utf-8 -*-

// File    :   P1036 选数（回溯）.cpp
// Time    :   2023/12/13
// Author  :   wolf

#include <iostream>
#include <math.h>
using namespace std;

int x[5000000];
int total = 0;
int ans = 0;
int n, k;

bool is_prime(int a)
{
    if (a <= 1)
        return 0;
    for (int i = 2; i <= sqrt(a); i++)
    {
        if (a % i == 0)
            return 0;
    }
    return 1;
}

void backtrace(int k, int depth)
{
    if (depth == n) // 到达第n层：答案
    {
        if (k == 0)
        {
            // cout << total << endl;
            if (is_prime(total))
                ans++;
        }
        return;
    }
    if (depth < n && k < 0)
        return; // 剪枝
    // 取这个数字
    total += x[depth];
    backtrace(k - 1, depth + 1);
    total -= x[depth];
    // 不取这个数字
    backtrace(k, depth + 1);
    return;
}

int main()
{
    cin >> n >> k;
    for (int i = 0; i < n; i++)
    {
        cin >> x[i];
    }
    backtrace(k, 0);
    cout << ans << endl;
    return 0;
}
