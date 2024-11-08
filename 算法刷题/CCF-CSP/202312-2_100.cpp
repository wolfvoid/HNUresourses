// -*- coding:utf-8 -*-

// File    :   202312-2.cpp
// Time    :   2024/03/27
// Author  :   wolf

#include <iostream>
#include <math.h>
#define ll long long
const int N = 1e5;
using namespace std;

int main()
{
    int q;
    cin >> q;
    while (q--)
    {
        ll n, k;
        ll ans = 1;
        cin >> n >> k;
        ll p = 2;
        while (p * p <= n)
        {
            ll pt = p;
            ll t = 0;
            while (n % pt == 0)
            {
                pt *= p;
                t++;
            }
            pt /= p;
            n /= pt;
            if (t >= k)
                ans *= pt;
            // cout << p << " " << t << " " << n << endl;
            p++;
        }
        cout << ans << endl;
    }
    return 0;
}
