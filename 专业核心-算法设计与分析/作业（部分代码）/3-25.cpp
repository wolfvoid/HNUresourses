#include <cmath>
#include <iostream>
using namespace std;

double g[500][500];
double t[500];
int n, m;

double f(int a, int b)
{
    double ret = 0;
    for (int i = a; i <= b; i++)
    {
        ret += (t[i] * t[i]);
    }
    return sqrt(ret);
}

double solve()
{
    int i, j, k;
    double tmp, maxt;
    tmp = f(n - 1, n - 1);
    for (i = n - 1; i >= 0; i--)
    {
        if (f(i, i) > tmp)
            tmp = f(i, i);
        g[i][1] = f(i, n - 1);
        if (n - i <= m)
            g[i][n - i] = tmp;
    }
    for (i = n - 1; i >= 0; i--)
    {
        for (k = 2; k <= m; k++)
        {
            for (j = i, tmp = INT_MAX; j <= n - k; j++)
            {
                maxt = max(f(i, j), g[j + 1][k - 1]);
                if (tmp > maxt)
                    tmp = maxt;
            }
            g[i][k] = tmp;
        }
        for (k = n - i + 1; k <= m; k++)
            g[i][k] = g[i][n - i];
    }
    return g[0][m];
}

int main()
{
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        cin >> t[i];
    }
    cout << solve() << endl;
}
