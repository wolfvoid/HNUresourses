// -*- coding:utf-8 -*-

// File    :   P1279 字串距离（递归）.cpp
// Time    :   2023/12/13
// Author  :   wolf

#include <iostream>
#include <math.h>
#include <string.h>

using namespace std;

int main()
{
    string A, B;
    int k;
    cin >> A >> B >> k;
    int lenA = A.length();
    int lenB = B.length();
    int dp[lenA + 1][lenB + 1];
    for (int i = 1; i <= lenA; i++)
    {
        dp[i][0] = i * k;
    }
    for (int i = 1; i <= lenB; i++)
    {
        dp[0][i] = i * k;
    }
    dp[0][0] = 0;
    for (int i = 1; i <= lenA; i++)
    {
        for (int j = 1; j <= lenB; j++)
        {
            dp[i][j] = min(dp[i - 1][j - 1] + abs(A[i-1] - B[j-1]), min(dp[i - 1][j] + k, dp[i][j - 1] + k));
            //字符串下标从0开始
        }
    }
    cout << dp[lenA][lenB] << endl;

    return 0;
}
