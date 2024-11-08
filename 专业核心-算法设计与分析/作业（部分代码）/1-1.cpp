#include<cstdio>
using namespace std;

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    long long n;
    scanf("%lld",&n);
    int ans[10];
    for (int i = 0; i <= 9; i++)
        ans[i] = 0;
    for (int i = 0; i <= 9; i++)
    {
        long long m = 1;
        while (m < n)
        {
            long long a = n / (m * 10);
            long long b = n / m % 10;
            long long c = n % m;
            if (i)
            {
                if (b > i)
                    ans[i] += ((a + 1) * m);
                else if (b == i)
                    ans[i] += (a * m + c + 1);
                else if (b < i)
                    ans[i] += (a * m);
            }
            else
            {
                if (b == 0)
                    ans[i] += ((a - 1) * m + c + 1);
                else if (b)
                    ans[i] += (a * m);
            }
            m *= 10;
        }
    }
    for (int i = 0; i <= 9; i++)
        printf("%d\n",ans[i]);
}
