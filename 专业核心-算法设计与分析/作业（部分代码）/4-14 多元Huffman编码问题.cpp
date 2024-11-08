#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, k, x;                                       // x为每堆石子数
    long long sum1 = 0, sum2 = 0;                      // sum1、sum2分别为最小总费用和最大总费用
    priority_queue<int, vector<int>, greater<int>> q1; // 创建递增的优先队列
    priority_queue<int, vector<int>, less<int>> q2;    // 创建递减的优先队列
    cin >> n >> k;
    for (int i = 0; i < n; i++) // 输入每堆石子数并压入优先队列中
    {
        cin >> x;
        q1.push(x);
        q2.push(x);
    }
    while (q1.size() % (k - 1) != 1) // 判断q1能否每次合并k堆且恰好合并完
        q1.push(0);                  // 不能合并完，就要压入“0”
    while (q1.size() > 1)
    {
        long long sum = 0;
        for (int i = 0; i < k; i++) // 每次都是队首前k堆合并
        {
            sum += q1.top(); // 前k堆每堆的费用加入到临时变量sum中
            q1.pop();        // 队首的这堆石子合并后，将它弹出队列
        }
        sum1 += sum;  // 将前k堆的费用加入到总费用中
        q1.push(sum); // 这个前k堆的费用压入队列中
    }

    while (q2.size() > 1)
    {
        long long sum = 0;
        for (int i = 0; i < 2; i++)
        {
            sum += q2.top();
            q2.pop();
        }
        sum2 += sum;
        q2.push(sum);
    }
    cout << sum2 << " " << sum1 << endl;
    return 0;
}
