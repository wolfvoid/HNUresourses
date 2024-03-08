#include <bits/stdc++.h>
using namespace std;

const int maxn = 10001;
const int mod = 998244353;
long long int bell[maxn], T[maxn];

void Bell(int n, int mod) // 求前n项Bell数
{
    bell[0] = bell[1] = 1;
    T[0] = 1;
    T[1] = 2;
    for (int i = 2; i <= n; i++)
    {
        T[i - 1] = bell[i - 1];
        for (int j = i - 2; j >= 0; j--) // 滚动数组
            T[j] = (T[j] + T[j + 1]) % mod;
        bell[i] = T[0];
    }
}

int main()
{
    int n, t;
    scanf("%d", &t);
    Bell(maxn, mod);
    for (int i = 0; i < t; i++)
    {
        scanf("%d", &n);
        if (n > maxn)
            printf("0\n");
        else
            printf("%lld\n", bell[n]);
    }
    // for (int i = 0; i < 100; i++) printf("%d%c", bell[i], (i + 1) % 13 == 0 ? '\n' : ' ');
}
