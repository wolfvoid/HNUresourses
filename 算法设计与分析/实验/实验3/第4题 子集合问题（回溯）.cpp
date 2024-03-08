// -*- coding:utf-8 -*-

// File    :   子集合问题（回溯）.cpp
// Time    :   2023/12/14
// Author  :   wolf

#include <iostream>
using namespace std;

int x[50000];
bool flag[50000];
int total = 0;
int n, c;

int backtrace(int depth)
{
    int if_ans = 0; // 用来存放是否得到了解
    if (depth == n) // 到达第n层：答案
    {
        if (total == c) // 答案是需要打印的
        {
            for (int i = 0; i < n; i++)
            {
                if (flag[i])
                    cout << x[i] << " ";
            }
            cout << endl;
            return 1;
        }
        return 0;
    }
    if (depth < n && total > c)
        return 0; // 剪枝
    // 取这个数字
    total += x[depth];
    flag[depth] = 1;
    if (backtrace(depth + 1))
        if_ans = 1;
    total -= x[depth];
    flag[depth] = 0;
    if (if_ans)
        return 1;
    // 不取这个数字
    if (backtrace(depth + 1))
        if_ans = 1;
    return if_ans;
}

int main()
{
    cin >> n >> c;
    for (int i = 0; i < n; i++)
    {
        cin >> x[i];
        flag[i] = 0;
    }
    if (!backtrace(0))
        cout << "No Solution!" << endl;
    return 0;
}
