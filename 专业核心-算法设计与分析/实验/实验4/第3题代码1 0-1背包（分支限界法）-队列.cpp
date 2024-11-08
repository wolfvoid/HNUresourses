// -*- coding:utf-8 -*-

// File    :   0-1背包（分支限界法）-队列.cpp
// Time    :   2023/12/21
// Author  :   wolf

#include <iostream>
#include <queue>
using namespace std;

int w[5000];
int v[5000];
int rest_v[5000];
int maxw, n, bestv = 0;

// 节点：表示解空间树上的一个节点
struct Node
{
    int now_w;
    int now_v;
    int depth;
    Node(int _now_w, int _now_v, int _depth)
    {
        now_w = _now_w;
        now_v = _now_v;
        depth = _depth;
    }
};

// 建立队列
queue<Node *> q;

void BFS()
{
    Node *root = new Node(0, 0, -1);
    q.push(root);
    while (!q.empty())
    {
        Node *now = nullptr;
        now = q.front();
        q.pop();
        if (now->depth == n) // 到达答案层
        {
            if (now->now_v > bestv && now->now_w < maxw)
            {
                bestv = now->now_v;
            }
        }
        else
        {
            Node *fetch = new Node(now->now_w + w[now->depth + 1], now->now_v + v[now->depth + 1], now->depth + 1); // 取
            Node *drop = new Node(now->now_w, now->now_v, now->depth + 1);                                          // 不取
            // 分支限界：剪枝：剪掉“不可行解”与“非最优解”

            // 对于“取”，若取之后w已经大于maxw，这是不可行解，就舍去
            if (fetch->now_w <= maxw)
                q.push(fetch);

            // 对于“不取”，可能产生非最优解，若到现在的价值加上剩余价值和都不可能达到最优，这是非最优解，舍去
            if (drop->now_v + rest_v[drop->depth] > bestv)
                q.push(drop);
        }
        delete (now);
    }
}

int main()
{
    cin >> maxw >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> w[i] >> v[i];
    }
    for (int i = n - 1; i >= 0; i--)
    {
        if (i == n - 1)
            rest_v[i] = 0;
        else
            rest_v[i] = v[i + 1] + rest_v[i + 1];
    } // 预先产生第i个物品之后所有物品和的总价值
    BFS();
    cout << bestv << endl;
    return 0;
}
