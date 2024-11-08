#include <iostream>
#include <string.h>
using namespace std;

int m[25];
int ans = 0;

void dfs(int depth, int whitesum)
{
    if (depth == 25)
    {
        if (whitesum != 13)
            return;

        // row
        if (m[0] == 0 && m[1] == 0 && m[2] == 0 && m[3] == 0 && m[4] == 0)
            return;
        if (m[5] == 0 && m[6] == 0 && m[7] == 0 && m[8] == 0 && m[9] == 0)
            return;
        if (m[10] == 0 && m[11] == 0 && m[12] == 0 && m[13] == 0 && m[14] == 0)
            return;
        if (m[15] == 0 && m[16] == 0 && m[17] == 0 && m[18] == 0 && m[19] == 0)
            return;
        if (m[20] == 0 && m[21] == 0 && m[22] == 0 && m[23] == 0 && m[24] == 0)
            return;
        // column
        if (m[0] == 0 && m[5] == 0 && m[10] == 0 && m[15] == 0 && m[20] == 0)
            return;
        if (m[1] == 0 && m[6] == 0 && m[11] == 0 && m[16] == 0 && m[21] == 0)
            return;
        if (m[2] == 0 && m[7] == 0 && m[12] == 0 && m[17] == 0 && m[22] == 0)
            return;
        if (m[3] == 0 && m[8] == 0 && m[13] == 0 && m[18] == 0 && m[23] == 0)
            return;
        if (m[4] == 0 && m[9] == 0 && m[14] == 0 && m[19] == 0 && m[24] == 0)
            return;
        // xie
        if (m[0] == 0 && m[6] == 0 && m[12] == 0 && m[18] == 0 && m[24] == 0)
            return;
        if (m[4] == 0 && m[8] == 0 && m[12] == 0 && m[16] == 0 && m[20] == 0)
            return;

        // row
        if (m[0] == 1 && m[1] == 1 && m[2] == 1 && m[3] == 1 && m[4] == 1)
            return;
        if (m[5] == 1 && m[6] == 1 && m[7] == 1 && m[8] == 1 && m[9] == 1)
            return;
        if (m[10] == 1 && m[11] == 1 && m[12] == 1 && m[13] == 1 && m[14] == 1)
            return;
        if (m[15] == 1 && m[16] == 1 && m[17] == 1 && m[18] == 1 && m[19] == 1)
            return;
        if (m[20] == 1 && m[21] == 1 && m[22] == 1 && m[23] == 1 && m[24] == 1)
            return;
        // column
        if (m[0] == 1 && m[5] == 1 && m[10] == 1 && m[15] == 1 && m[20] == 1)
            return;
        if (m[1] == 1 && m[6] == 1 && m[11] == 1 && m[16] == 1 && m[21] == 1)
            return;
        if (m[2] == 1 && m[7] == 1 && m[12] == 1 && m[17] == 1 && m[22] == 1)
            return;
        if (m[3] == 1 && m[8] == 1 && m[13] == 1 && m[18] == 1 && m[23] == 1)
            return;
        if (m[4] == 1 && m[9] == 1 && m[14] == 1 && m[19] == 1 && m[24] == 1)
            return;
        // xie
        if (m[0] == 1 && m[6] == 1 && m[12] == 1 && m[18] == 1 && m[24] == 1)
            return;
        if (m[4] == 1 && m[8] == 1 && m[12] == 1 && m[16] == 1 && m[20] == 1)
            return;

        ans++;
    }
    else
    {
        m[depth] = 0;
        dfs(depth + 1, whitesum);
        m[depth] = 1; // 1为白色
        dfs(depth + 1, whitesum + 1);
    }
    return;
}
int main()
{
    dfs(0, 0);
    cout << ans << endl;
}
