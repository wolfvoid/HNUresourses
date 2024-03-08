#include <bits/stdc++.h>
#include <iostream>
using namespace std;
typedef long long ll;
typedef int itn;
const int N = 5000;
const int mod = 998244353;
int n, m, k;
ll S[N][N];
ll B[N];

int solve_S(int n, int k)
{
    S[0][0] = 1;
    S[n][0] = 0;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= k; ++j)
        {
            S[i][j] = (S[i - 1][j - 1] + 1ll * j * S[i - 1][j]) % mod; // 公式中的 k 是当前的 k
        }
    }
    return 0;
}

ll Bell(int n)
{
    if (n == 0)
        return 1;
    ll ans = 0;
    for (int k = 0; k <= n; k++)
    {
        if (!S[n][k])
            solve_S(n, k);
        ans += S[n][k];
        ans = ans % mod;
    }
    return ans;
}
int main()
{
    for (int i = 0; i < N; i++)
        B[i] = 0;
    B[0] = 1;

    int n, T;
    scanf("%d", &T);
    for (int i = 0; i < T; i++)
    {
        scanf("%d", &n);
        // printf("ans = %lld\n", Bell(n));
        printf("%lld\n", Bell(n));
    }
    return 0;
}
