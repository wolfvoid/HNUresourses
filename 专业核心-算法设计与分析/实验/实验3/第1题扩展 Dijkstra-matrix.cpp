#include <iostream>
#include <cstring>
using namespace std;

const int N = 510;
int n, m;
int g[N][N];// 邻接矩阵
int dist[N];// 距离
bool st[N];// 是否已经确定了最短路径

int dijkstra()
{
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;// 初始化第一个节点
    for(int i = 0; i < n - 1; i++)// 循环n - 1次
    {
        int t = -1;// 找最小节点
        for(int j = 1; j <= n; j++)
        {
            if(!st[j] && (t == -1 || dist[j] < dist[t]))
            {
                t = j;
            }
        }
        st[t] = true;
        // 更新其他节点
        for(int j = 1; j <= n; j++)
        {
            dist[j] = min(dist[j], dist[t] + g[t][j]);
        }
    }
    if(dist[n] == 0x3f3f3f3f) return -1;
    else return 0;
}

int main()
{
    memset(g, 0x3f, sizeof g);
    cin >> n >> m;
    int a, b, c;
    while(m--)
    {
        cin >> a >> b >> c;
        g[a][b] = min(g[a][b], c);
    }
    cout << dijkstra() << endl;
    for(int i = 1; i <= n; i++) cout<<dist[i]<<" ";
    return 0;
}
