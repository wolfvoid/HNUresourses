#include <algorithm>
#include <stdio.h>
using namespace std;

struct object
{
    int weight;
    int value;
    double vpw; // value per weight
};

bool cmp(struct object a, struct object b)
{
    return a.vpw > b.vpw;
}

double solve_greedy(int n, int maxw, int weight[], int value[])
{
    // weight[]重量
    // value[]价值
    struct object x[n];
    for (int i = 0; i < n; i++)
    {
        x[i].weight = weight[i];
        x[i].value = value[i];
        x[i].vpw = (double)x[i].value / x[i].weight;
    }
    sort(x, x + n, cmp);

    int total = 0;  // 已放入背包的重量
    double ans = 0; // 放入背包的价值
    for (int i = 0; i < n; i++)
    {
        if (total + x[i].weight <= maxw)
        {
            ans += x[i].value;
            total += x[i].weight;
        }
        else
        {
            ans += (((double)(maxw - total) / x[i].weight) * x[i].value);
            break;
        }
    }
    return ans;
}

int main()
{
    int n, maxw;
    scanf("%d %d", &n, &maxw);
    int w[n], v[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d %d", &w[i], &v[i]);
    }
    printf("%.2lf\n", solve_greedy(n, maxw, w, v));
}
