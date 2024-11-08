// -*- coding:utf-8 -*-

// File    :   202009-2.cpp
// Time    :   2024/03/23
// Author  :   wolf

#include <iostream>

using namespace std;

int main()
{
    int n, k, t, x1, y1, x2, y2;
    scanf("%d %d %d %d %d %d %d", &n, &k, &t, &x1, &y1, &x2, &y2);
    int pass = 0;
    int stay = 0;
    for (int i = 0; i < n; i++)
    {
        bool if_pass = 0;
        bool if_stay = 0;
        int stay_time = 0;
        for (int j = 0; j < t; j++)
        {
            int x, y;
            scanf("%d %d", &x, &y);
            if (x >= x1 && y >= y1 && x <= x2 && y <= y2)
            {
                if_pass = 1;
                stay_time++;
            }
            else
            {
                stay_time = 0;
            }
            if (stay_time >= k)
                if_stay = 1;
        }
        if (if_pass)
            pass++;
        if (if_stay)
            stay++;
    }
    printf("%d\n%d", pass, stay);
    return 0;
}
