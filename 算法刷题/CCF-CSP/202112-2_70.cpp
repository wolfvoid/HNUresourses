// -*- coding:utf-8 -*-

// File    :   202112-2.cpp
// Time    :   2024/03/26
// Author  :   wolf

#include <iostream>
#include <math.h>
#define ll long long

using namespace std;

int main()
{
    ll n, N;
    cin >> n >> N;
    int a[n + 1];
    int g[N], f[N];
    a[0] = 0;
    int fi = 0;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        while (fi < a[i])
        {
            f[fi] = i - 1;
            fi++;
        }
    }
    while (fi < N)
    {
        f[fi] = n;
        fi++;
    }
    for (int i = 0; i < N; i++)
        cout << f[i] << " ";
    cout << endl;
    int r = floor((double)N / (n + 1));
    for (int i = 0; i < N; i++)
    {
        g[i] = floor((double)i / r);
    }
    for (int i = 0; i < N; i++)
        cout << g[i] << " ";
    ll ans = 0;
    for (int i = 0; i < N; i++)
    {
        ans += (abs(g[i] - f[i]));
        cout << "i= " << i << " | "
             << "ans= " << ans << endl;
    }
    cout << ans << endl;
    return 0;
}
