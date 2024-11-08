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
    vector<pair<int, double>> v;
    while (n--)
    {
        int a;
        double b;
        cin >> a >> b;
        v.push_back(make_pair(a, b));
    }
    while (m--)
    {
        int a, b;
        double x, y;
        cin >> a >> b >> x >> y;
        for (int i = a - 1; i <= b - 1; i++)
        {
            if (v[i].first == 1)
            {
                x *= v[i].second;
                y *= v[i].second;
            }
            else if (v[i].first == 2)
            {
                double x_new, y_new;
                x_new = x * cos(v[i].second) - y * sin(v[i].second);
                y_new = x * sin(v[i].second) + y * cos(v[i].second);
                x = x_new;
                y = y_new;
            }
        }
        cout << fixed << setprecision(3) << x << " " << y << endl;
    }
    return 0;
}
