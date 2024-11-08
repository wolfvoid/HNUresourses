// -*- coding:utf-8 -*-

// File    :   202112-2.cpp
// Time    :   2024/03/26
// Author  :   wolf

#include <iostream>
#include <math.h>
#define ll long long

using namespace std;

void print(char c, int f, int g, int fi, int ans)
{
    cout << c << ": ";
    cout << "fi:" << fi << " "
         << " | ";
    cout << "f " << f << " "
         << "g " << g << " | ";
    cout << "ans:" << ans << endl;
}

int main()
{
    ll n, N;
    cin >> n >> N;
    int a[n + 2];
    ll g, f;
    ll ans = 0;

    a[0] = 0;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    a[n + 1] = N;

    int fi = 0;
    int r = floor((double)N / (n + 1));

    for (int i = 1; i <= n + 1; i++)
    {
        // 70分解法1
        // while (fi < a[i])
        // {
        //     f = i - 1;
        //     g = floor((double)fi / r);
        //     ans += (abs(g - f));
        //     fi += 1;
        // }

        // 70分解法2
        // f = i - 1;
        // while (fi < a[i] && fi % r != 0)
        // {
        //     g = floor((double)fi / r);
        //     ans += (abs(g - f));
        //     // print('A', f, g, fi, ans);
        //     fi += 1;
        // }
        // while (fi + r < a[i])
        // {
        //     g = floor((double)fi / r);
        //     ans += r * (abs(g - f));
        //     // print('B', f, g, fi, ans);
        //     fi += r;
        // }
        // while (fi < a[i])
        // {
        //     g = floor((double)fi / r);
        //     ans += (abs(g - f));
        //     // print('C', f, g, fi, ans);
        //     fi += 1;
        // }

        // 解法3
        f = i - 1;
        int left = a[i - 1], right = a[i] - 1; // 该区间内f(i)=i-1
        if (left / r == right / r)
        {
            int gtemp = left / r;
            ans += ((right - left + 1) * abs(gtemp - f));
            // cout << left / r << " " << (right - left) * abs(gtemp - f) << endl;
            continue;
        }
        int temp1 = (left / r + 1) * r;
        int temp2 = (right / r) * r;
        int g1 = left / r;
        int g2 = right / r;
        ans += ((temp1 - left) * abs(g1 - f));
        int point = temp1;
        while (point != temp2)
        {
            int gtemp = point / r;
            ans += (r * abs(gtemp - f));
            point += r;
        }
        ans += ((right + 1 - temp2) * abs(g2 - f));
        // cout << temp1 << " " << temp2 << " " << ans << endl;
    }

    // int j = 0; // 指示当前处理g的值
    // for (int i = 1; i <= n + 1; i++)
    // {
    //     int left = a[i - 1], right = a[i] - 1; // 该区间内f(i)=i-1
    //     int fi = i - 1;
    //     while ((j + 1) * r < right)
    //     {
    //         j++;
    //         ans += ((j - left) *)
    //     }
    // }

    cout << ans << endl;
    return 0;
}
