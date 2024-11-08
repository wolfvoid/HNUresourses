#include <iostream>
using namespace std;

int ans = 0;
int N = 30;
void dfs(int num, int score)
{
    // 只要满70分就记录，因为有随时有可能放弃作答
    if (score == 70)
    {
        ans++;
    }
    if (num == N + 1)
    {
        return;
    }
    else
    {
        if (score == 100)
            return;
        dfs(num + 1, score + 10);
        dfs(num + 1, 0);
    }
}

int main()
{
    dfs(1, 0);
    cout << ans << endl;
    // 错误答案：4165637
    // 正确答案：8335366
}
