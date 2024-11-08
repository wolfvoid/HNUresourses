// -*- coding:utf-8 -*-

// File    :   202312-3.cpp
// Time    :   2024/03/27
// Author  :   wolf

#include <iostream>
#include <vector>
#define ll long long
using namespace std;
ll w_sum = 0;

struct node
{
    int number;
    ll w;
    ll w_child;
    node *parent;
    vector<node *> child;
    node(int number, ll w, node *parent)
    {
        this->number = number;
        this->w = w;
        this->parent = parent;
    };
};

vector<node *> nodelist; // 从0开始

void visit(node *now)
{
    cout << now->number << " ";
    if (now->child.size() == 0)
        return;
    for (unsigned int i = 0; i < now->child.size(); i++)
    {
        visit(now->child[i]);
    }
    return;
}

int main()
{
    int n, m;
    cin >> n >> m;
    pair<ll, int> x[n];
    for (int i = 0; i < n; i++)
    {
        cin >> x[i].first;
        w_sum += x[i].first;
    }
    x[0].second = 0;
    for (int i = 1; i < n; i++)
        cin >> x[i].second;
    struct node *root = new node(1, x[0].first, NULL);
    nodelist.push_back(root);
    for (int i = 1; i < n; i++)
    {
        struct node *newnode = new node(i + 1, x[i].first, nodelist[x[i].second - 1]);
        nodelist[x[i].second - 1]->child.push_back(newnode);
        nodelist.push_back(newnode);
    }
    visit(root);
    for (int i = 1; i < n; i++)
    {
    }
    return 0;
}
