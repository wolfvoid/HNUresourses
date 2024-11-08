// -*- coding:utf-8 -*-

// File    :   202309-1.cpp
// Time    :   2024/03/24
// Author  :   wolf

#include <iostream>

using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;
    int x = 0, y = 0;
    while (n--)
    {
        int a, b;
        cin >> a >> b;
        x += a;
        y += b;
    }
    while (m--)
    {
        int a, b;
        cin >> a >> b;
        cout << a + x << " " << b + y << endl;
    }
    return 0;
}
