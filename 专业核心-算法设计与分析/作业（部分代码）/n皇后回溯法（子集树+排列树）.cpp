/**
 * 回溯法求解n皇后问题
 * x解向量的含义：x[i]表示第i行上皇后的列号
 **/
#include <stdio.h>
#include <stdlib.h>
#define MAX 9

int n = MAX;    // 皇后个数
int x[MAX + 1]; // 当前解向量
int sum = 0;

// 使用子集树
int place1(int k)
{
    for (int j = 1; j < k; j++)
        if (abs(k - j) == abs(x[j] - x[k]) || x[j] == x[k]) // 剪枝函数，排除同列和同一对角线的分支
            return 0;
    return 1;
}

void BackTrack1(int t)
{
    if (t > n)
        sum++; // 当前解已经求出，将总数+1
    else
        for (int i = 1; i <= n; i++)
        {
            x[t] = i;
            if (place1(t))
                BackTrack1(t + 1);
        }
}

// 使用排列树
void swap(int i, int j)
{
    int tmp = x[i];
    x[i] = x[j];
    x[j] = tmp;
}

int place2(int k)
{
    for (int j = 1; j < k; j++)
        if (abs(k - j) == abs(x[j] - x[k])) // 剪枝函数，排除在同一对角线上的情况
            return 0;
    return 1;
}

void BackTrack2(int t)
{
    if (t > n)
        sum++;
    else
        for (int i = t; i <= n; i++)
        {
            swap(t, i);
            if (place2(t))
                BackTrack2(t + 1);
            swap(t, i);
        }
}

int main()
{
    // 构造子集树求解
    sum = 0;
    for (int i = 0; i <= n; i++)
        x[i] = i;
    BackTrack1(1);
    printf("%d\n", sum);

    // 构造排列树求解
    sum = 0;
    for (int i = 0; i <= n; i++)
        x[i] = i;
    BackTrack2(1);
    printf("%d\n", sum);
}
