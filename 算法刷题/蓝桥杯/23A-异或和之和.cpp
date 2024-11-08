#include <iostream>
using namespace std;
#define ll long long
const int N = 1e5 + 10;
ll A[N + 1], sum[N + 1];
ll ans = 0;
// 90%
int main()
{
    int n;
    cin >> n;
    sum[0] = 0;
    for (int i = 1; i <= n; i++)
    {
        cin >> A[i];
        sum[i] = A[i] ^ sum[i - 1];
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = i; j <= n; j++)
        {
            ans += (sum[j] ^ sum[i - 1]);
        }
    }
    cout << ans << endl;

    return 0;
}
