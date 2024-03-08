// -*- coding:utf-8 -*-

// File    :   0-1背包（分支限界法）-队列2.cpp
// Time    :   2023/12/21
// Author  :   wolf

#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int rest_v[5000];
int maxw, n, bestv = 0;

// 商品：使用sort函数排序，商品价值与重量要带着走不方便，用结构体来保证
struct goods
{
    int w;
    int v;
    double vpw;
} goods[5000];
// sort函数的排序依据：性价比较高的排在前面
bool cmp_goods(struct goods a, struct goods b)
{
    return a.vpw > b.vpw;
}

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

queue<Node *> q;

// 计算一个节点的总贪心价值
double get_greedy_v(int now_w, int now_v, int depth)
{
    int wleft = maxw - now_w; // 剩余容量
    int greedy_v = now_v;     // 价值上界,函数返回值
    // 以物品单位价值递减顺序排列
    depth++;
    while (depth < n && goods[depth].w <= wleft)
    {
        greedy_v += goods[depth].v;
        wleft -= goods[depth].w;
        depth++;
    }
    if (depth < n)
        greedy_v += goods[depth].vpw * wleft;
    return greedy_v;
}

void BFS()
{
    Node *root = new Node(0, 0, -1);
    q.push(root);
    while (!q.empty())
    {
        Node *now = nullptr;
        now = q.front();
        q.pop();
        // cout << "now:" << now->depth << endl;
        if (now->depth == n) // 到达答案层
        {
            if (now->now_v > bestv)
                bestv = now->now_v;
        }
        else
        {
            // Node(int _now_w, int _now_v, int _depth, double _rest_greedy_v)
            int w = now->now_w;
            int v = now->now_v;
            int depth = now->depth;
            // 分别计算已有的加上后面的贪心价值，这是这个节点的总贪心价值，也是优先队列的排序依据
            // double fetch_greedy_v = get_greedy_v(w + goods[depth + 1].w, v + goods[depth + 1].v, depth + 1);
            double drop_greedy_v = get_greedy_v(w, now->now_v, depth + 1);
            if (w + goods[depth + 1].w <= maxw) // 剪枝：约束函数：排除不可行解（超重）（只需对左子树考虑）
            {
                if (v + goods[depth + 1].v > bestv)
                {
                    bestv = v + goods[depth + 1].v; // 更新最优价值
                }
                Node *fetch = new Node(w + goods[depth + 1].w, v + goods[depth + 1].v, depth + 1);
                q.push(fetch); // 取
            }
            if (drop_greedy_v > bestv) // 剪枝：约束函数：排除非最优解（只需对右子树考虑）
            {
                Node *drop = new Node(w, v, depth + 1);
                q.push(drop); // 不取
            }
            delete (now); // 释放空间
            // cout << "fetch:" << fetch_greedy_v << endl
            //      << "drop:" << drop_greedy_v << endl
            //      << endl;
        }
    }
}

int main()
{
    cin >> maxw >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> goods[i].w >> goods[i].v;
        goods[i].vpw = (double)(goods[i].v) / goods[i].w; // 计算性价比
    }
    sort(goods, goods + n, cmp_goods); // 预排序，使性价比较高的靠前
    BFS();
    cout << bestv << endl;
    return 0;
}
