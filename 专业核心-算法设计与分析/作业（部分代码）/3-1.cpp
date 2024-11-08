#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <stack>
#include <vector>
using namespace std;
typedef long long ll;
const int INF = 0x3f3f3f3f;
const int MAXN = 1e6 + 100;
const double eps = 1e-6;
int Data[MAXN];
int a[MAXN], b[MAXN];
int dp[500][1000];
int main()
{
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    int n;
    int maxn = 0;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        maxn += a[i];
    }
    for (int i = 1; i <= n; i++)
        cin >> b[i];
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j <= maxn; j++)
        {
            if (j < a[i])
            {
                dp[i][j] = dp[i - 1][j] + b[i];
            }
            else
            {
                dp[i][j] = min(dp[i - 1][j - a[i]], dp[i - 1][j] + b[i]);
            }
        }
    }
    int ans = INF;
    for (int i = 0; i <= maxn; i++)
    {
        if (i < dp[n][i])
        {
            ans = min(ans, dp[n][i]);
        }
        else
        {
            ans = min(ans, i);
        }
    }
    cout << ans;
    return 0;
}
