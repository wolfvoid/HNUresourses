#include <algorithm>
#include <iostream>
#include <set>
using namespace std;
const int N = 1e5 + 10;
const int N2 = 1e6 + 1e5 + 10;
int A[N], f[N2 + 1];

int n;
// 并查集
int union_find(int x)
{
    if (x != f[x])
        f[x] = union_find(f[x]);
    // 同时进行路径压缩
    return f[x];
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n;

    // 40分答案 暴力
    // set<int> s;
    // for (int i = 0; i < n; i++)
    // {
    //     int input;
    //     cin >> input;
    //     while (s.find(input) != s.end())
    //     {
    //         input++;
    //     }
    //     A[i] = input;
    //     s.insert(input);
    // }
    // for (int i = 0; i < n; i++)
    //     cout << A[i] << " ";

    // 100分答案 并查集
    for (int i = 0; i < N2; i++)
        f[i] = i; // f[i]储存读入的i其所对应的可用的值
    for (int i = 0; i < n; i++)
    {
        int input;
        cin >> input;
        input = union_find(input);
        cout << input << " ";
        f[input] = input + 1;
    }

    return 0;
}
