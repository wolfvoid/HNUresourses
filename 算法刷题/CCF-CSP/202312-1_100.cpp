// -*- coding:utf-8 -*-

// File    :   202312-1.cpp
// Time    :   2024/03/27
// Author  :   wolf

#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> d;
    for (int i = 0; i < n; i++)
    {
        vector<int> di;
        for (int j = 0; j < m; j++)
        {
            int temp;
            cin >> temp;
            di.push_back(temp);
        }
        d.push_back(di);
    }
    for (int i = 0; i < n; i++)
    {
        bool flag1 = 0;
        for (int j = 0; j < n; j++)
        {
            bool flag = 1;
            for (int k = 0; k < m; k++)
            {
                if (d[j][k] <= d[i][k])
                {
                    flag = 0;
                    break;
                }
            }
            if (flag == 1)
            {
                cout << j + 1 << endl;
                flag1 = 1;
                break;
            }
        }
        if (flag1 == 0)
            cout << 0 << endl;
    }
    return 0;
}
