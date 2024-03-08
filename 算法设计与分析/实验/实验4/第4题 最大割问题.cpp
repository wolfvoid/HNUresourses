// -*- coding:utf-8 -*-

// File    :   实现题6-3.cpp
// Time    :   2023/12/22
// Author  :   wolf

#include <iostream>
#include <queue>
using namespace std;

int n, e;                    // 顶点数和边数
int Graph[200][200];         // 存储图的邻接矩阵
int bestcut = 0;             // 存储最优解：最大割
int bestx[200], status[200]; // 存储最优解：解向量

using namespace std;
struct Node
{
    int depth;
    int now_cut;
    int left_edge;
    int status[200];
    Node(int _depth, int _now_cut, int _left_edge)
    {
        depth = _depth;
        now_cut = _now_cut;
        left_edge = _left_edge;
    }
    // 确定优先队列优先级
    // bool operator<(const Node &node) const
    //{
    //   return now_cut < node.now_cut;
    //}
};
// 优先队列的构造依据
struct cmp_node
{
    bool operator()(Node *a, Node *b)
    {
        return a->now_cut < b->now_cut;
    }
    // 这里的大小方向似乎与正常的要反一下
};

priority_queue<Node *, vector<Node *>, cmp_node> q;

void solve_maxcut()
{
    Node *root = new Node(-1, 0, e);
    for (int i = 0; i < n; i++)
        status[i] = 0;
    for (int i = 0; i < n; i++)
        root->status[i] = status[i];
    q.push(root);
    while (!q.empty())
    {
        Node *now = nullptr;
        now = q.top();
        q.pop();
        int depth = now->depth;
        // cout << depth << endl;
        int now_cut = now->now_cut;
        int left_edge = now->left_edge;
        for (int i = 0; i < n; i++)
            status[i] = now->status[i];
        // 到达答案层
        if (depth == n - 1)
        {
            if (now_cut > bestcut)
            {
                bestcut = now_cut;
                for (int i = 0; i < n; i++)
                    bestx[i] = status[i];
                // for (int i = 0; i < n; i++)
                //     cout << status[i] << " ";
                // cout << endl;
            }
            // break;
        }
        else
        {
            // 不取
            if (now_cut + left_edge > bestcut) // 剪枝
            {
                Node *drop = new Node(depth + 1, now_cut, left_edge);
                for (int i = 0; i < n; i++)
                    drop->status[i] = status[i];
                q.push(drop);
            }

            // 取
            for (int i = 0; i < n; i++)
            {
                if (Graph[depth + 1][i])
                {
                    if (!status[i])
                    {
                        now_cut++;
                        left_edge--;
                    }
                    else
                    {
                        now_cut--;
                    }
                }
            }
            status[depth + 1] = 1;
            Node *fetch = new Node(depth + 1, now_cut, left_edge);
            for (int i = 0; i < n; i++)
                fetch->status[i] = status[i];
            q.push(fetch);
        }
    }
}

int main()
{
    int u, v;
    cin >> n >> e;
    for (int i = 0; i < e; i++)
    {
        cin >> u >> v;
        Graph[u - 1][v - 1] = 1;
        Graph[v - 1][u - 1] = 1;
    }
    cout << "Possible best answers" << endl;
    solve_maxcut();
    cout << "One solution" << endl;
    cout << bestcut << endl;
    for (int i = 0; i < n; i++)
    {
        cout << bestx[i] << " ";
    }
    cout << endl;
    return 0;
}
