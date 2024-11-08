// 电路板排列问题
#include <bits/stdc++.h>
using namespace std;
class Board
{
    friend int ArrangeBoards(int **, int, int, int *);

private:
    void Backtrack(int i);
    int len(int ii);
    int n,      // 电路板数
        m,      // 连接块数
        *x,     // 当前解
        *bestx, // 当前最优解
        bestd,  // 当前最优密度
        *low,   //
        *high,  //
        **B;    // 连接块数组
};
int Board::len(int ii)
{
    for (int i = 0; i <= m; i++)
    {
        high[i] = 0;
        low[i] = n + 1;
    }
    for (int i = 1; i <= ii; i++)
    {
        for (int k = 1; k <= m; k++)
        {
            if (B[x[i]][k])
            {
                if (i < low[k])
                    low[k] = i;
                if (i > high[k])
                    high[k] = i;
            }
        }
    }
    int tmp = 0;
    for (int k = 1; k <= m; k++)
    {
        if (low[k] <= n && high[k] > 0 && tmp < high[k] - low[k])
            tmp = high[k] - low[k];
    }
    return tmp;
}
void Board::Backtrack(int i) // 回溯搜索排列树
{
    if (i == n) // 到达排列树终点
    {
        int tmp = len(i);
        if (tmp < bestd)
        {
            bestd = tmp;
            for (int j = 1; j <= n; j++)
                bestx[j] = x[j];
        }
    }
    else
    {
        for (int j = i; j <= n; j++) // 选择x[j]为下一块电路板
        {
            swap(x[i], x[j]);
            int ld = len(i);
            if (ld < bestd)
                Backtrack(i + 1);
            swap(x[i], x[j]);
        }
    }
}
int ArrangeBoards(int **B, int n, int m, int *bestx)
{
    Board X;
    // 初始化X
    X.x = new int[n + 1];
    X.low = new int[m + 1];
    X.high = new int[m + 1];
    X.B = B;
    X.n = n;
    X.m = m;
    X.bestx = bestx;
    X.bestd = n + 1;
    // 初始化total和now
    for (int i = 1; i <= n; i++)
    {
        X.x[i] = i;
    }
    X.Backtrack(1);
    delete[] X.x;
    delete[] X.low;
    delete[] X.high;
    return X.bestd;
}
int main()
{
    int n, m;
    cin >> n >> m;
    int **B = new int *[n + 1];
    for (int i = 0; i <= n; i++)
        B[i] = new int[m + 1];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> B[i][j];
    int *bestx = new int[n + 1];
    for (int i = 1; i <= n; i++)
        bestx[i] = 0;
    int ans = ArrangeBoards(B, n, m, bestx);
    cout << ans << endl;
    for (int i = 1; i <= n; i++)
        cout << bestx[i] << " ";
    cout << endl;
    return 0;
}
