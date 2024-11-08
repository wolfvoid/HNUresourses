// -*- coding:utf-8 -*-

// File    :   202309-2.cpp
// Time    :   2024/03/24
// Author  :   wolf

#include <iomanip>
#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;
    vector<pair<double, double>> v;
    v.push_back(make_pair(1, 0));
    int now = 0;
    while (n--)
    {
        int a;
        double b;
        now++;
        cin >> a >> b;
        if (a == 1) // 拉伸
        {
            v.push_back(make_pair(v[now - 1].first * b, v[now - 1].second));
        }
        else if (a == 2) // 旋转
        {
            v.push_back(make_pair(v[now - 1].first, v[now - 1].second + b));
        }
    }
    while (m--)
    {
        int a, b;
        double x, y;
        cin >> a >> b >> x >> y;
        double k = v[b].first / v[a - 1].first;
        double t = v[b].second - v[a - 1].second;
        double x_new, y_new;
        x_new = x * cos(t) - y * sin(t);
        y_new = x * sin(t) + y * cos(t);
        x = x_new * k;
        y = y_new * k;
        cout << fixed << setprecision(3) << x << " " << y << endl;
    }
    return 0;
}
