// -*- coding:utf-8 -*-

// File    :   4-9 虚拟汽车加油问题.cpp
// Time    :   2023/12/29
// Author  :   wolf

#include <iostream>

using namespace std;

int main()
{
    int n, k, temp;
    cin >> n >> k;
    int rest_oil = n;
    cin >> temp; // 读入第一个加油站，不做处理
    int ans = 0;
    for (int i = 0; i < k; i++)
    {
        int now_input;
        cin >> now_input;
        if (now_input > n)
        {
            cout << "No Solution" << endl;
            return 0;
            // 到下一加油站的距离超过加满油能行驶的距离，时不可行的。
        }
        if (rest_oil - now_input >= 0)
        {
            rest_oil -= now_input;
        }
        else
        {
            rest_oil = n;
            rest_oil -= now_input;
            ans++;
        }
    }
    cout << ans << endl;

    return 0;
}
