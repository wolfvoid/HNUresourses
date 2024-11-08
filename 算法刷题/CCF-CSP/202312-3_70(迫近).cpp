// -*- coding:utf-8 -*-

// File    :   202312-3.cpp
// Time    :   2024/03/27
// Author  :   wolf

#include <iostream>
#include <set>
#include <vector>
#define ll long long
const int N = 2010;
using namespace std;

int n, m;
set<int> yes, no;

// 通过全局变量传递答案
ll w_total;

struct node
{
    int number;
    ll w;
    ll w_sum;
    vector<int> child;
    node(int number, ll w)
    {
        this->number = number;
        this->w = w;
    };
};

vector<node> nodelist; // 从1开始

// 判断test是否从属now
bool belong(int test, int now)
{
    if (test == now)
        return 1;
    for (unsigned int i = 0; i < nodelist[now].child.size(); i++)
    {
        if (no.find(nodelist[now].child[i]) == no.end())
        {
            if (belong(test, nodelist[now].child[i]) == 1)
            {
                return 1;
            }
        }
    }
    return 0;
}

// 计算w值，选择询问对象
int calculate_choose()
{
    int choose_number = 2010;
    ll w_min = 0x3f3f3f3f;
    for (int j : yes) // 自带顺序递增
    {
        ll wd = abs(nodelist[j].w_sum - (w_total - nodelist[j].w_sum));
        if (wd < w_min)
        {
            choose_number = j;
            w_min = wd;
        }
    }
    return choose_number;
}

// 遍历全树，计算w值
ll calculate(int now)
{
    ll w = 0;
    yes.insert(now);
    for (unsigned int i = 0; i < nodelist[now].child.size(); i++)
    {
        if (no.find(nodelist[now].child[i]) == no.end())
        {
            w += calculate(nodelist[now].child[i]);
        }
    }
    w += nodelist[now].w;
    nodelist[now].w_sum = w;
    return w;
}

int main()
{
    // 读入
    cin >> n >> m;
    pair<ll, int> x[n];
    for (int i = 0; i < n; i++)
    {
        cin >> x[i].first;
    }
    x[0].second = 0;
    for (int i = 1; i < n; i++)
        cin >> x[i].second;

    // 构造nodelist，从1-n
    struct node none(0, 0);
    nodelist.push_back(none);
    struct node root(x[0].second, x[0].first);
    nodelist.push_back(root);

    // 问题写法，运行时错误 20分
    // 问题：nodelist不是按照顺序给定的，因此有可能出现序号小的在前，但从属于序号大的。
    // 使用vector而不是数组会可能序号大的还没构造出来，因此访问到了不该访问的地方，运行时错误
    // for (int i = 1; i < n; i++)
    // {
    //     struct node newnode(i + 1, x[i].first);
    //     nodelist[x[i].second].child.push_back(i + 1);
    //     nodelist.push_back(newnode);
    // }
    for (int i = 1; i < n; i++)
    {
        struct node newnode(i + 1, x[i].first);
        nodelist.push_back(newnode);
    }
    for (int i = 1; i < n; i++)
    {
        nodelist[x[i].second].child.push_back(i + 1);
    }

    // excute
    for (int i = 0; i < m; i++)
    {
        int test;
        cin >> test;
        no.clear();
        for (int j = 1; j <= n; j++)
        {
            nodelist[j].w_sum = 0;
        }

        // 执行算法，直到只剩一个
        int now = 1;
        while (true)
        {
            yes.clear();
            w_total = calculate(now);
            if (yes.size() == 1)
                break;
            int choose_number = calculate_choose();
            cout << choose_number << " ";
            if (belong(test, choose_number) == 1)
            {
                now = choose_number;
            }
            else
            {
                no.insert(choose_number);
            }
        }
        cout << endl;
    }
    return 0;
}
