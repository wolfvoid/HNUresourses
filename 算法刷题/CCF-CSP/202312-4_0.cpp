// -*- coding:utf-8 -*-

// File    :   202312-4.cpp
// Time    :   2024/03/28
// Author  :   wolf

#include <deque>
#include <iostream>
#include <vector>
#define DEBUG 0
#define ll long long
const int mod = 998244353;
// 可参考https://blog.csdn.net/Power_up_H_/article/details/134947028

struct matrix
{
    ll c11, c12, c21, c22;
    matrix(ll c11, ll c12, ll c21, ll c22)
    {
        this->c11 = c11;
        this->c12 = c12;
        this->c21 = c21;
        this->c22 = c22;
    }
    matrix(){};
};

using namespace std;
struct node
{
    int type;
    int order;
    struct matrix m;
    node(int type, ll c11, ll c12, ll c21, ll c22, int order)
    {
        this->type = type;
        this->m.c11 = c11;
        this->m.c12 = c12;
        this->m.c21 = c21;
        this->m.c22 = c22;
        this->order = order;
    }
};
vector<node> v;
deque<node> d;

struct matrix calculate(matrix m, matrix n)
{
    struct matrix a;
    a.c11 = (m.c11 * n.c11 + m.c12 * n.c21) % mod;
    a.c12 = (m.c11 * n.c12 + m.c12 * n.c22) % mod;
    a.c21 = (m.c21 * n.c11 + m.c22 * n.c21) % mod;
    a.c22 = (m.c21 * n.c12 + m.c22 * n.c22) % mod;
    return a;
}

int main()
{
    int n, m;
    cin >> n >> m;
    while (n--)
    {
        int type;
        cin >> type;
        if (type == 1 || type == 2)
        {
            ll c11, c12, c21, c22;
            cin >> c11 >> c12 >> c21 >> c22;
            node newnode(type, c11, c12, c21, c22, 0);
            v.push_back(newnode);
        }
        else if (type == 3)
        {
            node newnode(type, 0, 0, 0, 0, 0);
            v.push_back(newnode);
        }
    }
    while (m--)
    {
        int optype;
        cin >> optype;
        if (optype == 2)
        {
            int left, right;
            cin >> left >> right;
            d.clear();
            int order = 0;
            for (int i = left - 1; i <= right - 1; i++)
            {
                if (DEBUG)
                    cout << "process: " << v[i].type << " " << v[i].m.c11 << " " << v[i].m.c12 << " " << v[i].m.c21 << " " << v[i].m.c22 << endl;
                if (v[i].type == 1)
                {
                    struct node temp = v[i];
                    temp.order = order;
                    order++;
                    d.push_front(temp);
                }
                else if (v[i].type == 2)
                {
                    struct node temp = v[i];
                    temp.order = order;
                    order++;
                    d.push_back(temp);
                }
                else if (v[i].type == 3)
                {
                    if (d.size())
                    {
                        int front = d.front().order;
                        int back = d.back().order;
                        if (front > back)
                        {
                            order--;
                            d.pop_front();
                        }
                        else if (front < back)
                        {
                            order--;
                            d.pop_back();
                        }
                    }
                }
            }
            matrix m(1, 0, 0, 1);
            for (unsigned int i = 0; i < d.size(); i++)
            {
                if (DEBUG)
                    cout << "excute: " << d[i].m.c11 << " " << d[i].m.c12 << " " << d[i].m.c21 << " " << d[i].m.c22 << endl;
                m = calculate(m, d[i].m);
            }
            cout << m.c11 << " " << m.c12 << " " << m.c21 << " " << m.c22 << endl;
        }
        else if (optype == 1)
        {
            int change_pos;
            cin >> change_pos;
            int type;
            cin >> type;
            if (type == 1 || type == 2)
            {
                ll c11, c12, c21, c22;
                cin >> c11 >> c12 >> c21 >> c22;
                node newnode(type, c11, c12, c21, c22, 0);
                v[change_pos - 1] = newnode;
            }
            else if (type == 3)
            {
                node newnode(type, 0, 0, 0, 0, 0);
                v[change_pos - 1] = newnode;
            }
        }
    }

    return 0;
}

// 3 8
// 1 2 3 9 3
// 2 6 9 4 2
// 2 2 8 2 1
// 2 2 3
// 1 2 1 3 1 0 1
// 1 3 3
// 2 1 3
// 2 2 3
// 1 2 1 3 1 0 1
// 1 3 3
// 2 1 3
