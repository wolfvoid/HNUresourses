#include <iostream>
using namespace std;

long long int solve()
{
    long long int n, x, ans = 0, pre, now;
    scanf("%lld %lld", &n, &x);
    scanf("%lld %lld", &pre, &now);
    if (pre + now > x)
    {
        ans += (pre + now - x);
        now -= ans;
        if (now < 0)
            now = 0;
    }
    for (int i = 2; i < n; i++)
    {
        pre = now;
        scanf("%lld", &now);
        if (pre + now > x)
        {
            ans += (pre + now - x);
            now -= (pre + now - x);
        }
        // printf("%lld %lld %lld\n", pre, now, ans);
    }
    return ans;
}

int main()
{
    printf("%lld", solve());
}
