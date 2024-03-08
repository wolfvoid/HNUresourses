#include <bits/stdc++.h>
#include <iostream>
#define ll long long
const int N = 1000;
const int mod = 998244353;
using namespace std;

ll C[N][N];
ll B[N];

void Combinations() // 处理组合数
{
    C[0][0] = 1;
    for (int i = 1; i <= N - 1; i++)
    {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++)
        {
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod;
        }
    }
}

long long Bell(int n)
{
    if (n == 0)
        return 1;
    ll ans = 0;
    for (int k = 0; k <= n - 1; k++)
    {
        if (B[k] == 0)
            B[k] = Bell(k);
        ans += (C[n - 1][k] * B[k] % mod);
    }
    return ans % mod;
}
int main()
{
    Combinations(); // 记忆化搜索求所有C(n,m)
    for (int i = 0; i < N; i++)
        B[i] = 0;
    B[0] = 1;

    int n, T;
    scanf("%d", &T);
    for (int i = 0; i < T; i++)
    {
        scanf("%d", &n);
        printf("ans = %lld\n", Bell(n));
    }
    return 0;
}
