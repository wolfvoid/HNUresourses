#include <bits/stdc++.h>
using namespace std;
#define N 100
int n;
struct node
{
    int vis[N] = {0}, col[N] = {0}, lr[N] = {0}, rl[N] = {0};
    int x, y;
    node(int a, int b) : x(a), y(b) {}
    bool operator<(const node &a) const
    {
        return x < a.x;
    }
};
priority_queue<node> q;
int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        node temp = node(0, i);
        temp.vis[0] = i + 1;
        temp.col[i] = 1;
        temp.rl[temp.x + temp.y] = 1;
        temp.lr[50 + temp.x - temp.y] = 1;
        q.push(temp);
    }
    while (!q.empty())
    {
        node temp = q.top();
        q.pop();
        if (temp.x == n - 1)
        {
            for (int i = 0; i < n; i++)
            {
                cout << temp.vis[i] << " ";
            }
            cout << endl;
            break; // 只需要给出一个答案即可
        }
        if (temp.x < n - 1)
        {
            for (int i = 0; i < n; i++)
            {
                node next = node(temp.x + 1, i);
                if (temp.col[next.y] || temp.lr[50 + next.x - next.y] || temp.rl[next.x + next.y])
                { // 剪枝
                    continue;
                }
                for (int i = 0; i < N; i++)
                {
                    next.lr[i] = temp.lr[i];
                    next.rl[i] = temp.rl[i];
                    next.col[i] = temp.col[i];
                }
                next.col[next.y] = 1;
                next.lr[50 + next.x - next.y] = 1;
                next.rl[next.x + next.y] = 1;
                for (int i = 0; i < next.x; i++)
                {
                    next.vis[i] = temp.vis[i];
                }
                next.vis[next.x] = i + 1;
                q.push(next);
            }
        }
    }
    return 0;
}
