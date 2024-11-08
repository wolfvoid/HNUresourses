#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i, s, n) for (int i = s; i < n; i++)
#define reb(i, d, n) for (int i = d; i >= n; i--)
const int N = 100;
ll factorial_array[N];
list<int> sup_array; // 辅助数组
ll factorial(int n)
{
    if (factorial_array[n] != 0)
        return factorial_array[n];
    ll res = 1;
    for (int i = 1; i <= n; i++)
        res *= i;
    factorial_array[n] = res; // 记忆，避免重复计算
    return res;
}
ll permutation(int n)
{
    ll res = 1;
    rep(i, 2, n)
        res *= factorial(i);
    return res;
}

ll dictNum(int *data, int size)
{
    // 将数字插入辅助数组中，判断有多少个比其小的数
    int index = 1;
    ll res = 0;
    sup_array.push_back(data[0]);
    res += (data[0] - 1) * factorial(size - 1);
    for (int i = 1; i < size; i++)
    {
        list<int>::iterator p = sup_array.begin();
        int min_nums;
        int j;
        for (j = 0; p != sup_array.end(); p++, j++)
        {
            if (data[i] < *p) // 升序排列 找到位置
            {
                min_nums = (data[i] - j - 1);
                sup_array.insert(p, data[i]);
                break;
            }
        }
        if (p == sup_array.end())
        {
            min_nums = (data[i] - j - 1);
            sup_array.push_back(data[i]);
        }
        res += (min_nums)*factorial(size - i - 1);
    }

    return res;
}

int main()
{
    int n;
    ifstream fin;
    fin.open("input.txt", ios::in);
    if (!fin.is_open())
    {
        cerr << "input.txt not found" << endl;
        return -1;
    }
    ofstream fout;
    fout.open("output.txt", ios::out);

    fin >> n;
    int data[N];
    // cout << factorial(7) + 4 * factorial(6) + 2 * factorial(5) + 2 * factorial(4) + 3 * factorial(3) + 1 << endl;
    rep(i, 0, n)
    {
        fin >> data[i];
    }
    fout << dictNum(data, n) << endl;
    // 寻找下一个，倒着遍历 直到找到第一个比最后一个小的数，然后交换，再把后面排序即可
    bool flag = 0;
    reb(i, n - 2, 0)
    {
        if (data[i] < data[n - 1])
        {
            swap(data[i], data[n - 1]);
            sort(data + i + 1, data + n);
            flag = 1;
            break;
        }
    }
    if (!flag)
        sort(data, data + n);
    rep(i, 0, n)
            fout
        << data[i] << " ";
    fin.close();
    fout.close();

    return 0;
}
