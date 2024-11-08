#include <algorithm> //sort
#include <iostream>
#define ll long long
using namespace std;
const int N = 31;
ll melon[N];
ll n, m;
int ans = N;
bool solved = 0;
// 有2个-1的点
// 注意不开long long 见祖宗
// 暴力不剪枝70分

// 剪枝后缀数组
ll restmax[N]; // 当前层以及往后层最大有多少

void dfs(int depth, ll sum, int knife)
{
    // cout << sum << endl;
    if (sum == m)
    {
        ans = min(ans, knife);
        solved = 1;
        return;
    }
    if (depth == n || sum > m)
        return;
    // 剪枝优化
    if (sum + restmax[depth] < m)
        return;
    // excute
    dfs(depth + 1, sum, knife);
    dfs(depth + 1, sum + melon[depth] / 2, knife + 1);
    dfs(depth + 1, sum + melon[depth], knife);
}

bool cmp(int a, int b)
{
    return a > b;
}
int main()
{
    cin >> n >> m;
    m *= 2;
    for (int i = 0; i < n; i++)
    {
        ll temp;
        cin >> temp;
        melon[i] = temp * 2;
    }
    // 剪枝优化
    sort(melon, melon + n, cmp);
    restmax[n - 1] = melon[n - 1];
    for (int i = n - 2; i >= 0; i--)
    {
        restmax[i] = restmax[i + 1] + melon[i];
    }

    dfs(0, 0, 0);
    if (solved == 1)
        cout << ans << endl;
    else
        cout << -1 << endl;
    return 0;
}
