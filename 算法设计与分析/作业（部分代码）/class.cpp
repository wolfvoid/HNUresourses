#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;
    int s[n], f[n], ans[n], ans_total = 0;
    for (int i = 0; i < n; i++)
        cin >> s[i];
    for (int i = 0; i < n; i++)
        cin >> f[i];

    for (int i = 0; i < n; i++)
    {
        int total = 0;
        int temp[n];
        for (int j = 0; j < n; j++)
        {
            if (f[j] <= s[i] || f[i] <= s[j])
            {
                temp[k++] = j;
                total++;
            }
        }
        if (total > ans_total)
        {
            ans_total = total;
            for (int j = 0; j < k; j++)
                ans[j] = temp[j];
        }
    }
}
