// -*- coding:utf-8 -*-

// File    :   P1678 烦恼的高考志愿（二分）.cpp
// Time    :   2023/12/14
// Author  :   wolf

#include <algorithm>
#include <iostream>
#include <math.h>

using namespace std;
int x[100001];

int binary_search(int left, int right, int target)
{
    int ret;
    if (left == right)
        return abs(target - x[left]);
    int mid = (left + right) / 2;
    ret = min(abs(target - x[mid]), abs(target - x[mid + 1]));
    if (target <= x[mid])
        ret = min(ret, binary_search(left, mid, target));
    else if (target >= x[mid + 1])
        ret = min(ret, binary_search(mid + 1, right, target));
    return ret;
}

bool cmp(int a, int b)
{
    return a < b;
}
int main()
{
    int m, n;
    cin >> m >> n;

    for (int i = 0; i < m; i++)
    {
        cin >> x[i];
    }
    sort(x, x + m, cmp);
    int temp, ans = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> temp;
        ans += binary_search(0, m, temp);
    }
    cout << ans << endl;

    return 0;
}
