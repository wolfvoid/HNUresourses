// -*- coding:utf-8 -*-

// File    :   202312-3.cpp
// Time    :   2024/03/27
// Author  :   wolf

#include <iostream>
#include <vector>
#define DEBUG 0
#define ll long long
const int N = 2010;
using namespace std;
int n, m;

// 通过全局变量传递答案
ll w_total;
int choose_number;
ll w_min;
vector<int> remain;

struct node
{
    int number;
    ll w;
    vector<int> child;
    node(int number, ll w)
    {
        this->number = number;
        this->w = w;
    };
};

vector<node> nodelist; // 从1开始
bool flag[N];

// visit模板
void visit(int now)
{
    cout << nodelist[now].number << " ";
    if (nodelist[now].child.size() == 0)
        return;
    for (unsigned int i = 0; i < nodelist[now].child.size(); i++)
    {
        visit(nodelist[now].child[i]);
    }
    return;
}

// 遍历子树并染色
void visit_mark(int now, bool tf)
{
    flag[now] = tf;
    for (unsigned int i = 0; i < nodelist[now].child.size(); i++)
    {
        if (flag[nodelist[now].child[i]])
        {
            visit_mark(nodelist[now].child[i], tf);
        }
    }
    return;
}

// 判断test是否从属now
bool belong(int test, int now)
{
    if (test == now)
        return 1;
    for (unsigned int i = 0; i < nodelist[now].child.size(); i++)
    {
        if (flag[nodelist[now].child[i]])
        {
            if (belong(test, nodelist[now].child[i]) == 1)
            {
                return 1;
            }
        }
    }
    return 0;
}

// 遍历全树，计算w值，选择询问对象
ll calculate_choose(int now)
{
    ll w_sum = 0;
    for (unsigned int i = 0; i < nodelist[now].child.size(); i++)
    {
        if (flag[nodelist[now].child[i]])
        {
            w_sum += calculate_choose(nodelist[now].child[i]);
        }
    }
    w_sum += nodelist[now].w;
    ll wd = abs(w_sum - (w_total - w_sum));
    if (wd < w_min || (wd == w_min && now < choose_number))
    {
        choose_number = now;
        w_min = wd;
    }
    if (DEBUG)
        cout << "now: " << now << " wd= " << wd << endl;
    return w_sum;
}

// 遍历全树，计算w值
ll calculate(int now)
{
    ll w_sum = 0;
    for (unsigned int i = 0; i < nodelist[now].child.size(); i++)
    {
        if (flag[nodelist[now].child[i]])
        {
            w_sum += calculate(nodelist[now].child[i]);
        }
    }
    w_sum += nodelist[now].w;
    return w_sum;
}

// 遍历该节点子树，并将其存活子节点放入remain中
void visit_child(int now)
{
    remain.push_back(now);
    for (unsigned int i = 0; i < nodelist[now].child.size(); i++)
    {
        if (flag[nodelist[now].child[i]])
        {
            visit_child(nodelist[now].child[i]);
        }
    }
    return;
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
    x[0].second = 1;
    for (int i = 1; i < n; i++)
        cin >> x[i].second;

    // 构造nodelist，从1-n
    struct node none(0, 0);
    nodelist.push_back(none);
    struct node root(x[0].second, x[0].first);
    nodelist.push_back(root);
    // 问题写法，运行时错误 20分
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
        for (int j = 1; j <= n; j++)
        {
            flag[j] = 1;
        }

        int now = 1; // 20->70 改动点：now的转移
        // 执行算法，直到只剩一个
        while (true)
        {
            if (DEBUG)
                cout << "epoch: " << endl;
            choose_number = 2010;
            w_min = 0x3f3f3f3f;
            int count = 0;

            // 计数存活节点数，重新指定根节点
            if (DEBUG)
                cout << "flag: ";
            for (int j = 1; j <= n; j++)
            {
                if (DEBUG)
                    cout << flag[j] << " ";
                if (flag[j] == 1)
                {
                    count++;
                }
            }
            if (DEBUG)
                cout << endl;
            if (DEBUG)
                cout << "root= " << now << endl;

            // 若存活节点只剩1个，则退出
            if (count == 1)
                break;

            // 计算当前总w值
            w_total = calculate(now);
            if (DEBUG)
                cout << "w_total= " << w_total << endl;

            // 计算并选择当前情况下询问节点，全局choose_number传递答案
            int none = calculate_choose(now);
            if (DEBUG)
                cout << "choose number= " << choose_number << endl;
            cout << choose_number << " ";

            // 根据用户回答对当前树进行删除
            if (belong(test, choose_number) == 1)
            {
                if (DEBUG)
                    cout << "保留" << choose_number << endl;
                // 仅保留该类别及其后代类别
                remain.clear();
                visit_child(choose_number);
                for (int j = 1; j <= n; j++)
                {
                    flag[j] = 0;
                }
                for (unsigned int j = 0; j < remain.size(); j++)
                {
                    flag[remain[j]] = 1;
                }
                // 不可以直接用这种方法，想想看会导致什么问题？
                // 子节点先被全部删了
                // for (int j = 1; j <= n; j++)
                // {
                //     flag[j] = 0;
                // }
                // visit_mark(choose_number, 1);
                now = choose_number; // 20->70 改动点：now的转移
            }
            else
            {
                if (DEBUG)
                    cout << "删除" << choose_number << endl;
                // 仅保留其余类别
                visit_mark(choose_number, 0);
            }
        }
        cout << endl;
    }
    // visit(1);
    return 0;
}
