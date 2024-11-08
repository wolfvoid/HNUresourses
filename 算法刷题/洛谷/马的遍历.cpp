#include <iostream>
using namespace std;
int const inf = 999999;
int const dir[8][2] = {
    {-1, 2},
    {1, 2},
    {-1, -2},
    {1, -2},
    {-2, 1},
    {2, 1},
    {-2, -1},
    {2, -1},
};
int ans[400][400];

void dfs(int n, int m, int x, int y, int depth)
{
    ans[x][y] = min(ans[x][y], depth);
    for (int i = 0; i < 8; i++)
    {
        int new_x = x + dir[i][0];
        int new_y = y + dir[i][1];
        cout << new_x << " " << new_y << endl;
        if (new_x >= 0 && new_x <= n && new_y >= 0 && new_y <= m)
            dfs(n, m, new_x, new_y, depth + 1);
    }
    return;
}

int main()
{
    int n, m, x, y;
    cin >> n >> m >> x >> y;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            ans[i][j] = inf;
    cout << 1;
    dfs(n - 1, m - 1, x - 1, y - 1, 0);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            cout << ans[i][j] << " ";
            if (j == m - 1)
                cout << endl;
        }
}
