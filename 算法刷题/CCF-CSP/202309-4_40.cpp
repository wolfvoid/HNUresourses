// -*- coding:utf-8 -*-

// File    :   202309-4.cpp
// Time    :   2024/03/24
// Author  :   wolf

#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

const int d[8][2] = {
    {1, 0},
    {1, 1},
    {0, 1},
    {-1, 1},
    {-1, 0},
    {-1, -1},
    {0, -1},
    {1, -1}};
int n, m, p, q;

pair<int, int> visit(int x, int y)
{
    return make_pair(m + 1 - y, x);
}

int main()
{
    cin >> n >> m >> p >> q;
    vector<pair<int, int>> staff_pos;
    // n<=1000 m<=1000
    int mymap[m + 1][n + 1];
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            mymap[i][j] = 0;
    staff_pos.push_back(make_pair(0, 0)); // 占位，无用
    for (int i = 1; i <= p; i++)
    {
        int a, b;
        cin >> a >> b;
        mymap[visit(a, b).first][visit(a, b).second] = i;
        staff_pos.push_back(make_pair(a, b));
    }
    // // test
    // cout << "origin matrix: " << endl;
    // for (int j = 1; j <= m; j++)
    // {
    //     for (int k = 1; k <= n; k++)
    //     {
    //         cout << mymap[j][k] << " ";
    //     }
    //     cout << endl;
    // }
    // cout << endl;
    // // test
    for (int i = 0; i < q; i++)
    {
        int u, v, t;
        cin >> u >> v >> t;

        // 求k值
        int k2 = min(u - 1, min(v - 1, min(n - u, m - v)));
        int k1 = min(n, m); // 假设初始k1很大，看后面是否能被更小值覆盖
        int k = 0;
        for (int j = 1; j <= m; j++) // 竖方向
        {
            if (mymap[visit(u, j).first][visit(u, j).second] != 0 && j != v)
            {
                k1 = min(k1, abs(j - v));
            }
            // cout << "visit: " << mymap[visit(u, j).first][visit(u, j).second] << endl;
        }
        for (int j = 1; j <= n; j++) // 横方向以及斜方向
        {
            // 横方向 (j,v)
            if (mymap[visit(j, v).first][visit(j, v).second] != 0 && j != u)
            {
                k1 = min(k1, abs(j - u));
            }
            // 斜方向y=-x (j,-j+u+v)
            if (-j + u + v >= 1 && -j + u + v <= m && mymap[visit(j, -j + u + v).first][visit(j, -j + u + v).second] != 0 && j != u)
            {
                k1 = min(k1, abs(j - u));
            }
            // 斜方向y=x (j,j+v-u)
            if (j + v - u >= 1 && j + v - u <= m && mymap[visit(j, j + v - u).first][visit(j, j + v - u).second] != 0 && j != u)
            {
                k1 = min(k1, abs(j - u));
            }
            // cout << "横 visit: " << mymap[visit(j, v).first][visit(j, v).second] << endl;
            // cout << "y=-x visit: " << mymap[visit(j, -j + u + v).first][visit(j, -j + u + v).second] << endl;
            // cout << "y=x visit: " << mymap[visit(j, j + v - u).first][visit(j, j + v - u).second] << endl;
        }
        if (k1 <= k2)
            k = k1;
        else
            k = 0;

        // cout << "k1= " << k1 << endl;
        // cout << "k2= " << k2 << endl;
        // cout << "k= " << k << endl;
        //  位置变换
        if (k > 0)
        {
            struct change_node
            {
                int x;
                int y;
                int num;
                change_node(int x, int y, int num)
                {
                    this->x = x;
                    this->y = y;
                    this->num = num;
                }
            };
            vector<change_node> change;
            for (int j = 0; j < 8; j++)
            {
                int visit_x = visit(u + k * d[j][0], v + k * d[j][1]).first;
                int visit_y = visit(u + k * d[j][0], v + k * d[j][1]).second;

                if (mymap[visit_x][visit_y] != 0)
                {
                    int staff = mymap[visit_x][visit_y];
                    int new_pos = (j + t) % 8;
                    change_node c(u + k * d[new_pos][0], v + k * d[new_pos][1], staff);
                    change.push_back(c);
                    mymap[visit_x][visit_y] = 0;
                }
            }
            for (unsigned int j = 0; j < change.size(); j++)
            {
                int visit_x = visit(change[j].x, change[j].y).first;
                int visit_y = visit(change[j].x, change[j].y).second;
                mymap[visit_x][visit_y] = change[j].num;
                staff_pos[change[j].num].first = change[j].x;
                staff_pos[change[j].num].second = change[j].y;
            }
        }
        // // test
        // for (int j = 1; j <= m; j++)
        // {
        //     for (int k = 1; k <= n; k++)
        //     {
        //         cout << mymap[j][k] << " ";
        //     }
        //     cout << endl;
        // }
        // cout << endl;
        // //test
    }
    // for (int i = 1; i <= p; i++)
    //     cout << staff_pos[i].first << " " << staff_pos[i].second << endl;
    int ans = staff_pos[1].first + staff_pos[1].second;
    for (int i = 2; i <= p; i++)
    {
        ans ^= (i * staff_pos[i].first + staff_pos[i].second);
    }
    cout << ans << endl;
    return 0;
}

// 5 4 4 1
// 3 4
// 3 3
// 2 3
// 2 2
// 3 2 1
