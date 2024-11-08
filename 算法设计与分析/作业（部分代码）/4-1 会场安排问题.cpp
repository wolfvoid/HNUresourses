// -*- coding:utf-8 -*-

// File    :   4-1 会场安排问题.cpp
// Time    :   2023/12/29
// Author  :   wolf

#include <algorithm>
#include <iostream>

using namespace std;
struct activity
{
    int start;
    int end;
    bool if_arrange;
} a[10001];

bool cmp(struct activity a, struct activity b)
{
    if (a.start < b.start)
        return 1;
    else if (a.start == b.start)
    {
        if (a.end <= b.end)
            return 1;
    }
    return 0;
}

int main()
{
    int k;
    cin >> k;
    for (int i = 0; i < k; i++)
    {
        cin >> a[i].start >> a[i].end;
        a[i].if_arrange = 0;
    }
    sort(a, a + k, cmp);
    int ok_num = 0;  // 已安排成功的会场数量
    int now_end = 0; // 当前安排的活动的结尾时间
    int ans = 0;     // 要开的会场数目
    while (ok_num < k)
    {
        now_end = 0;
        ans++;
        for (int i = 0; i < k; i++)
        {
            if (a[i].if_arrange == 0)
            {
                if (a[i].start >= now_end) // 相容，可加入
                {
                    a[i].if_arrange = 1;
                    ok_num++;
                    now_end = a[i].end;
                }
            }
        }
    }
    cout << ans << endl;
    return 0;
}
