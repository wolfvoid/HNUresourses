#include <iostream>
using namespace std;
#define ll long long
int main()
{
    ll x1, y1, x2, y2, x3, y3, x4, y4;
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
    ll ans = 0;
    if (!(x1 < x4 && y1 < y4) || !(x3 < x2 && y3 < y2))
    {
        // 没有重叠区域
        ans = (y4 - y3) * (x4 - x3) + (y2 - y1) * (x2 - x1);
    }
    else
    {
        // 在内部
        if (x1 >= x3 && y1 >= y3 && x2 <= x4 && y2 <= y4)
        {
            ans = (y4 - y3) * (x4 - x3);
        }
        else if (x3 >= x1 && y3 >= y1 && x4 <= x2 && y4 <= y2)
        {
            ans = (y2 - y1) * (x2 - x1);
        }
        //
    }
    cout << ans << endl;
    return 0;
}
