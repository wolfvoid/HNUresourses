#include <iostream>
#include <stdio.h> //memset
#include <string.h>
using namespace std;

const int N = 5000;
int dp[N + 10][N + 10]; // 以s[i]和s[j]为两边的字串是否可翻转
int ans = 0;
int n;

int main()
{
    string s;
    cin >> s;
    int n = s.size();
    if (n <= 1000)
    {
        // 40%
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                string news = s;
                int left = i, right = j;
                bool flag = false;
                while (true)
                {
                    if (left >= right)
                    {
                        flag = false;
                        break;
                    }
                    if (news[left] > news[right])
                    {
                        flag = true;
                        break;
                    }
                    else if (news[left] < news[right])
                    {
                        flag = false;
                        break;
                    }
                    else
                    {
                        left++;
                        right--;
                    }
                }
                if (flag == true)
                    ans++;
            }
        }
    }
    else
    {
        // 60%
        // 区间dp （注意不能用记忆化搜索，逻辑上还是没改变）
        // dp[i][j]表示以s[i]和s[j]为两边的这个字串是否合法
        // 注意必须由len=2 -> n，以遍历所有子段

        // 本题思路：按位比较两端，如果是大于小于的情况容易处理，但如果是等于的情况需要耗费n的时间复杂度向中间再比较
        // 这样会使得时间复杂度达到n^3，根据测试用例大小可知后面60%跑不了，需要优化到n^2
        // 因此启用动态规划，当比较两端大小相等时，如i,j位,直接根据已经计算过的dp[i+1][j-1]得出结论，时间复杂度为1
        memset(dp, 0, sizeof(dp));
        for (int len = 2; len <= n; len++)
        {
            for (int left = 0; left + len - 1 < n; left++)
            {
                int right = left + len - 1;
                if (s[left] > s[right])
                {
                    dp[left][right] = 1;
                    ans++;
                }
                else if (s[left] < s[right])
                {
                    dp[left][right] = -1;
                }
                else
                {
                    // s[left] == s[right]
                    // 若left+1 == right-1，则dp=0，必然是不可以的
                    if (dp[left + 1][right - 1] == 1)
                    {
                        dp[left][right] = 1;
                        ans++;
                    }
                    else
                    {
                        dp[left][right] = -1;
                    }
                }
            }
        }
    }
    cout << ans << endl;
    return 0;
}
