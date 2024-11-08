#include <iostream>
using namespace std;
const int N = 1e5 + 10;
int a[N], sum[N];
int n, x;

bool check(int y)
{
    for (int i = 1; i <= n - y; i++)
    {
        if (sum[i + y - 1] - sum[i - 1] < 2 * x)
            return false;
    }
    return true;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> x;
    sum[0] = 0;
    for (int i = 1; i <= n - 1; i++)
    {
        cin >> a[i];
        sum[i] = sum[i - 1] + a[i];
    }
    int left = 1, right = n;
    while (left < right)
    {
        int mid = (left + right) / 2;
        if (check(mid) == 1)
            right = mid;
        else
            left = mid + 1;
    }
    cout << left << endl;
    return 0;
}
