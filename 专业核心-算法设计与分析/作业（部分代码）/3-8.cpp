#include <iostream>
using namespace std;

int dp[500][500];
int t[500];
void solve(int n, int m)
{
    int i, j, k, temp, maxt;
    for (i = 1; i <= n; i++)
        dp[i][1] = dp[i - 1][1] + t[i];
    for (j = 2; j <= m; j++)
    {
        for (i = j; i <= n; i++)
        {
            for (k = 1, temp = INT_MAX; k < i; k++)
            {
                maxt = max(dp[i][1] - dp[k][1], dp[k][j - 1]);
                if (temp > maxt)
                    temp = maxt;
            }
            dp[i][j] = temp;
        }
    }
}

int main()
{
    int n, m;
    cin >> n >> m;
    if ((n < m) || (n == 0))
    {
        cout << 0 << endl;
        return 0;
    }
    for (int i = 1; i <= n; i++)
        cin >> t[i];
    solve(n, m);
    cout << dp[n][m] << endl;
}
