#include <cstdio>
#include <iostream>
#include <string>
using namespace std;
int n;
string s[1000];
int ans[1000];
int f[27][7];
int g[7];

int func(int i, int k)
{
    if (k == 1)
    {
        f[i][k] = 1;
        return 1;
    }
    int total = 0;
    for (int j = i + 1; j <= 26; j++)
        total += (f[j][k - 1]) ? f[j][k - 1] : func(j, k - 1);
        //如果已经存在，就不用再算一遍了，记忆化搜索
    f[i][k] = total;
    return total;
}

int main()
{
    // build table
    //初始化
    for (int i = 0; i < 27; i++)
        for (int j = 0; j < 7; j++)
            f[i][j] = 0;
    for (int i = 0; i < 7; i++)
        g[i] = 0;

    //填表
    for (int i = 1; i <= 26; i++)
    {
        for (int j = 1; j <= 6; j++)
            if (f[i][j] == 0)
                func(i, j);
    }
    // 计算每种长度字符串的个数放在g[i]
    for (int k = 1; k <= 6; k++)
        for (int i = 1; i <= 26; i++)
            g[k] += f[i][k];

    // check
    /*
    for (int i = 1; i <= 26; i++)
    {
        for (int j = 1; j <= 6; j++)
            cout << f[i][j] << " ";
        cout << endl;
    }
    cout << endl;
    for (int i = 1; i <= 6; i++)
        cout << g[i] << " ";
    */

    // process problem
    cin >> n;
    for (int i = 0; i < n; i++)
        ans[i] = 0;
    for (int i = 0; i < n; i++)
        cin >> s[i];
    for (int i = 0; i < n; i++)
    {
        int length = s[i].size();
        int total = 0;
        int a0 = s[i][0] - 'a' + 1;

        // 比该字符串长度小的字符串个数直接加上（之前计算过每种长度字符串的个数放在g[i]）
        for (int j = 1; j < length; j++)
            total += g[j];

        // 与该字符串长度相同，但是首字母不一样的，加上
        // 例如该串首字母d开头，则前面可能有a,b,c开头的，这些需要加上去
        for (int j = 1; j < a0; j++)
            total += f[j][length];

        // 与该字符串相同长度，相同首字母，但每个位置都有可能因为不是紧挨着的而留出别的可能
        // 例如abcde和afghi和afjkl，abcde和afghi之间在第二个位置上留有可能，要考虑b/c/d/e的可能，
        // 故要加上f[2][4],f[3][4],f[4][4],f[5][4],是length-k而不是k因为第二位置引导4位长度的字符串。
        // afghi只有第二个位置存在问题，而afjkl在第二个位置和第三个位置都存在问题，
        // afjkl还需要额外加上f[7][3],f[8][3],f[9][3]这三个，即ghi在第三个位置产生的问题
        // 后面的位置也是同理可得
        for (int k = 1; k < length; k++)
        {
            for (int j = (s[i][k - 1] - 'a' + 1) + 1; j < (s[i][k] - 'a' + 1); j++)
                total += f[j][length - k];
        }

        //前面统计的是到目前为止已有的序号，求自身的序号要+1
        total += 1;

        ans[i] = total;
    }
    for (int i = 0; i < n; i++)
    {
        cout << ans[i] << " ";
    }
}
