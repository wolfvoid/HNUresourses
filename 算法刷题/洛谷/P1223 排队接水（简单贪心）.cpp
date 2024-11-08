#include <algorithm>
#include <iostream>
using namespace std;
struct s
{
    int num;
    int t;
} s[1001];

bool cmp(struct s a, struct s b)
{
    return a.t < b.t;
}

int main()
{
    int n;
    double ans = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        s[i].num = i;
        scanf("%d", &s[i].t);
    }
    sort(s, s + n, cmp);
    for (int i = 0; i < n; i++)
    {
        printf("%d", s[i].num + 1);
        if (i != n - 1)
            printf(" ");
        ans += ((n - i - 1) * s[i].t);
    }
    ans /= n;
    printf("\n%.2lf", ans);
}
