// -*- coding:utf-8 -*-

// File    :   202403-3.cpp
// Time    :   2024/03/31
// Author  :   wolf

#include <algorithm>
#include <cstring> //memset
#include <iostream>
#include <map>
#include <string>
#define DEBUG 1
#define ll long long
using namespace std;
const int maxnum = 0x3f3f3f3f;
const int N = 41;

struct matrix
{
    int m[N][N];
    int yuansu;
    int wuzhi;
};

bool solve(struct matrix m)
{
    int yuansu = m.yuansu;
    int wuzhi = m.wuzhi;
    if (yuansu < wuzhi)
        return 1;
    if (yuansu <= 2 && wuzhi <= 2)
    {
        if (yuansu == 1 && wuzhi == 1)
            return 0;
        if (yuansu == 2 && wuzhi == 1)
            return 0;
        if (yuansu == 2 && wuzhi == 2)
        {
            if (m.m[0][0] * m.m[1][1] == m.m[0][1] * m.m[1][1])
                return 0;
            return 1;
        }
    }
    return 1;
}

int main()
{
    int n;
    cin >> n;
    while (n--)
    {
        int m;
        cin >> m;
        map<string, int> mp;
        int mymatrix[N][N];
        memset(mymatrix, 0, sizeof(mymatrix));
        // 构建元素-物质矩阵
        for (int wuzhi_num = 0; wuzhi_num < m; wuzhi_num++)
        {
            // 对于每一个化学式（物质）
            string temp;
            cin >> temp;
            unsigned int pos = 0;
            while (pos < temp.size())
            {
                // 对于化学式内的每一个元素
                // 分解单个原子与系数
                string yuansu = "";
                string xishu = "";
                while (!(temp[pos] >= '0' && temp[pos] <= '9'))
                {
                    yuansu += temp[pos];
                    pos++;
                }
                while (temp[pos] >= '0' && temp[pos] <= '9')
                {
                    xishu += temp[pos];
                    pos++;
                }
                int xi = stoi(xishu);
                // if (DEBUG)
                //     cout << yuansu << " " << xishu << endl;

                // 查找元素的索引（即该元素是对应哪一行）
                auto yuansu_find = mp.find(yuansu);
                int yuansu_line;
                if (yuansu_find == mp.end())
                {
                    yuansu_line = mp.size();
                    mp.insert(make_pair(yuansu, mp.size()));
                }
                else
                {
                    yuansu_line = yuansu_find->second;
                }
                mymatrix[yuansu_line][wuzhi_num] = xi;
            }
        }
        // 将matrix封装进结构体
        struct matrix origin_matrix;
        origin_matrix.wuzhi = m;
        origin_matrix.yuansu = mp.size();
        for (int i = 0; i < origin_matrix.yuansu; i++)
        {
            for (int j = 0; j < origin_matrix.wuzhi; j++)
            {
                origin_matrix.m[i][j] = mymatrix[i][j];
            }
        }
        if (DEBUG)
        {
            for (int i = 0; i < origin_matrix.yuansu; i++)
            {
                for (int j = 0; j < origin_matrix.wuzhi; j++)
                {
                    cout << origin_matrix.m[i][j] << " ";
                }
                cout << endl;
            }
        }
        if (solve(origin_matrix))
            cout << "Y " << endl;
        else
            cout << "N" << endl;
    }
    return 0;
}

// 5 al2o3 n2o4 c1o2 c1o1 c1s2
