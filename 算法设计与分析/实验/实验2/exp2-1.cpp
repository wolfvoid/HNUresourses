#include <stdio.h>
using namespace std;

int max(int a, int b)
{
    return a > b ? a : b;
}

int solve(int n, int maxw, int weight[], int value[])
{
    // weight[]重量
    // value[]价值
    int dp[n][maxw + 1];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < maxw + 1; j++)
        {
            dp[i][j] = 0;
        }
    }
    for (int k = 0; k < maxw + 1; k++)
    {
        if (weight[0] <= k)
            dp[0][k] = value[0];
    }
    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < maxw + 1; j++)
        {
            if (j - weight[i] < 0)
                dp[i][j] = dp[i - 1][j];
            else
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - weight[i]] + value[i]);
        }
    }
    return dp[n - 1][maxw];
}

int main()
{
    int n, maxw;
    scanf("%d %d", &maxw, &n);
    int w[n], v[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d %d", &w[i], &v[i]);
    }
    printf("%d\n", solve(n, maxw, w, v));
}
