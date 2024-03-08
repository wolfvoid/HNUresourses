#include <cstring>
#include <iostream>
#include <queue>

using namespace std;

typedef pair<int, int> PII; // 分别表示距离和节点

const int N = 150010;

int n, m;

int h[N], e[N], ne[N], w[N], idx;
bool st[N];
int dist[N];

void add(int a, int b, int c)
{
    e[idx] = b;
    w[idx] = c;
    ne[idx] = h[a];
    h[a] = idx++;
}

int dijkstra()
{
    memset(dist, 0x3f, sizeof dist);
    priority_queue<PII, vector<PII>, greater<PII>> pq;
    pq.push({0, 1});
    dist[1] = 0;
    while (pq.size())
    {
        auto t = pq.top();
        pq.pop();
        int node = t.second, val = t.first;
        if (st[node])
            continue;
        st[node] = true;
        // 更新其他节点
        for (int i = h[node]; i != -1; i = ne[i])
        {
            int j = e[i];
            dist[j] = min(dist[j], w[i] + dist[node]);
            pq.push({dist[j], j});
        }
    }
    if (dist[n] == 0x3f3f3f3f)
        return -1;
    else
        return 0;
}

int main()
{
    memset(h, -1, sizeof h);
    cin >> n >> m;
    int a, b, c;
    while (m--)
    {
        cin >> a >> b >> c;
        add(a, b, c);
    }
    if (dijkstra() == -1)
        cout << "error" << endl;
    else
        for (int i = 1; i <= n; i++)
            cout << dist[i] << " ";
    return 0;
}
