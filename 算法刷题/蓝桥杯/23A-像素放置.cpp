#include <iostream>
#include <map>
using namespace std;
const int N = 5 + 1;
int mymap[N][N];
int number[N][N];
int n, m;
map<pair<int, int>, int> check;

bool judge(int row, int col, int num)
{
    int sum = 0;
    if (row == 0 && col == 0)
    {
        // 左上角
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                sum += mymap[row + i][col + j];
            }
        }
    }
    else if (row == 0 && col == m - 1)
    {
        // 右上角
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                sum += mymap[row + i][col - j];
            }
        }
    }
    else if (row == n - 1 && col == 0)
    {
        // 左下角
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                sum += mymap[row - i][col + j];
            }
        }
    }
    else if (row == n - 1 && col == m - 1)
    {
        // 右下角
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                sum += mymap[row - i][col - j];
            }
        }
    }
    else if (row == 0)
    {
        // 第一行
        for (int i = 0; i <= 1; i++)
        {
            for (int j = -1; j <= 1; j++)
            {
                sum += mymap[row + i][col + j];
            }
        }
    }
    else if (row == n - 1)
    {
        // 最后一行
        for (int i = -1; i <= 0; i++)
        {
            for (int j = -1; j <= 1; j++)
            {
                sum += mymap[row + i][col + j];
            }
        }
    }
    else if (col == 0)
    {
        // 第一列
        for (int i = -1; i <= 1; i++)
        {
            for (int j = 0; j <= 1; j++)
            {
                sum += mymap[row + i][col + j];
            }
        }
    }
    else if (col == m - 1)
    {
        // 最后一列
        for (int i = -1; i <= 1; i++)
        {
            for (int j = -1; j <= 0; j++)
            {
                sum += mymap[row + i][col + j];
            }
        }
    }
    else
    {
        // 中间点
        for (int i = -1; i <= 1; i++)
        {
            for (int j = -1; j <= 1; j++)
            {
                sum += mymap[row + i][col + j];
            }
        }
    }
    if (sum != num)
        return 0;
    else
        return 1;
}

void printout()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << mymap[i][j];
        }
        cout << endl;
    }
}

void dfs(int depth, bool place)
{
    int row = depth / m;
    int col = depth % m;
    if (place)
        mymap[row][col] = 1;
    else
        mymap[row][col] = 0;
    if (depth == n * m - 1)
    {
        bool flag = true;
        for (auto it = check.begin(); it != check.end(); it++)
        {
            if (judge(it->first.first, it->first.second, it->second) != 1)
            {
                flag = false;
                break;
            }
        }
        if (flag)
            printout();
    }
    else
    {
        dfs(depth + 1, 0);
        dfs(depth + 1, 1);
    }
}
int main()
{
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        string temp;
        cin >> temp;
        for (int j = 0; j < m; j++)
        {
            if (temp[j] != '_')
            {
                int store = temp[j] - '0';
                check.insert(make_pair(make_pair(i, j), store));
                number[i][j] = store;
            }
            else
            {
                check.insert(make_pair(make_pair(i, j), 0));
                number[i][j] = 0;
            }
        }
    }
    dfs(-1, 0);
    return 0;
}
