#include <iostream>
using namespace std;

int main()
{
    const long long int inf = 1e10;
    long long n, ans=-inf, mini=inf, temp;
    //维持一个到当前的最小值，每次读入值都与之作差求出当前Ai-Aj，
    //若当前读入的是最小值，就更新
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> temp;
        if (temp - mini > ans) ans = temp - mini;
        if (temp < mini) mini = temp;
        //考虑到可能有所有都是负数的情况，所以temp的更新必须放在后面
        //否则0将覆盖负数解
    }
    cout << ans << endl;
}