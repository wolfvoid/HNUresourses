#include <bits/stdc++.h>
using namespace std;

// from
// https://blog.csdn.net/qq_61828116/article/details/135945147

vector<long long> wi, temp;
vector<vector<int>> ls;
set<int> yes, no;

void dfs(int pre)
{
    yes.insert(pre);
    for (int i : ls[pre])
    {
        if (no.find(i) == no.end())
        {
            dfs(i);
            wi[pre] += wi[i];
        }
    }
}

int getMinIdx(int pre)
{
    long long minDiff = LLONG_MAX;
    int idx = 1;
    for (int j : yes)
    {
        long long wj = abs(wi[pre] - 2 * wi[j]);
        if (minDiff > wj)
        {
            minDiff = wj;
            idx = j;
        }
    }
    return idx;
}

bool check(int idx, int t)
{
    if (idx == t)
        return true;
    for (int i : ls[idx])
    {
        if (no.find(i) != no.end())
            continue;
        if (check(i, t))
            return true;
    }
    return false;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    temp.resize(n + 1);
    ls.resize(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> temp[i];
    for (int i = 1; i <= n; i++)
        ls[i] = vector<int>();
    for (int i = 2; i <= n; i++)
    {
        int parent;
        cin >> parent;
        ls[parent].push_back(i);
    }

    for (int i = 0; i < m; i++)
    {
        int t, pre = 1;
        cin >> t;
        no.clear();
        while (true)
        {
            wi = temp;
            yes.clear();
            dfs(pre);
            if (yes.size() == 1)
                break;
            int idx = getMinIdx(pre);
            if (check(idx, t))
                pre = idx;
            else
                no.insert(idx);
            cout << idx << " ";
        }
        cout << endl;
    }

    return 0;
}
