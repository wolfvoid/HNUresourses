#include <cstring> // 包含用于 'strlen' 函数的头文件
#include <iostream>

using namespace std;

void LCSlength(int m, int n, const char *x, const char *y, int c[][15], int b[][15])
{
    for (int i = 0; i <= m; i++)
    {
        c[i][0] = 0;
    }
    for (int i = 0; i <= n; i++)
    {
        c[0][i] = 0;
    }
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (x[i - 1] == y[j - 1])
            { // 修正数组索引问题
                c[i][j] = c[i - 1][j - 1] + 1;
                b[i][j] = 1;
            }
            else
            {
                c[i][j] = max(c[i - 1][j], c[i][j - 1]);
                if (c[i - 1][j] >= c[i][j - 1])
                {
                    b[i][j] = 2;
                }
                else
                {
                    b[i][j] = 3;
                }
            }
        }
    }
}

int main()
{
    const char *x = "abcdefg"; // 使用双引号表示字符串文字
    const char *y = "acfghi";
    int m = strlen(x); // 使用 'strlen' 获取字符串的长度
    int n = strlen(y);

    int c[15][15];
    int b[15][15];
    LCSlength(m, n, x, y, c, b);
    cout << c[7][6];
}
