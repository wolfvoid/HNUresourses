// -*- coding:utf-8 -*-

// File    :   5-7 n色方柱问题.cpp
// Time    :   2023/12/27
// Author  :   wolf

#include <iostream>

using namespace std;
char color[28]; // 用来储存输入的数字对应的颜色（只在输出的时候转换为字符，在做题时使用数字存储）
int box[28][6]; // box[i][j]用来储存第i个立方体各个面（即第j面）的颜色
int n;
int count = 1; //  标记这是第几个输出的；可能结果
const int place[24][6] = {
    // 转动立方体的映射函数，使用box[depth+1][j]=origin[place[method][j]]来获取第method种方法下下一层的摆放方式
    // place[i][j]为第i种转换方法下该立方体该层的第j面应该变换为place[i][j]
    {0, 1, 2, 3, 4, 5},
    {4, 5, 2, 3, 1, 0},
    {1, 0, 2, 3, 5, 4},
    {5, 4, 2, 3, 0, 1}, // 2为底面，3为顶面

    {0, 1, 3, 2, 4, 5},
    {4, 5, 3, 2, 1, 0},
    {1, 0, 3, 2, 5, 4},
    {5, 4, 3, 2, 0, 1}, // 3为底面，2为顶面

    {3, 2, 0, 1, 4, 5},
    {4, 5, 0, 1, 2, 3},
    {2, 3, 0, 1, 5, 4},
    {5, 4, 0, 1, 3, 2}, //  0为底面，1为顶面

    {3, 2, 1, 0, 4, 5},
    {4, 5, 1, 0, 2, 3},
    {2, 3, 1, 0, 5, 4},
    {5, 4, 1, 0, 3, 2}, //  1为底面，0为顶面

    {1, 0, 4, 5, 3, 2},
    {3, 2, 4, 5, 0, 1},
    {0, 1, 4, 5, 2, 3},
    {2, 3, 4, 5, 1, 0}, //  4为底面，5为顶面

    {1, 0, 5, 4, 3, 2},
    {3, 2, 5, 4, 0, 1},
    {0, 1, 5, 4, 2, 3},
    {2, 3, 5, 4, 1, 0}, //  5为底面，4为顶面
};

void backtrack(int depth)
{
    // cout << "depth=" << depth << endl;
    if (depth == n - 1) // 到达答案层
    {
        cout << "Possible Solution " << count << " : " << endl;
        count++;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < 6; j++)
            {
                cout << color[box[i][j]] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
    else
    {
        int process = depth + 1;
        int origin[6];
        // 【使用origin[]数组先保存原始情况，可以省去整体恢复原状的步骤，24次for循环每次都是新的开始】
        for (int i = 0; i < 6; i++)      // 保存待处理层初始存放的颜色
            origin[i] = box[process][i]; // origin[i]表示该层初始第i个面存放的颜色
        // cout << "origin=" << endl;
        // for (int i = 0; i < 6; i++)
        //     cout << origin[i] << " ";
        // cout << endl;
        for (int i = 0; i < 24; i++) // 列举子集树，每个立方体有24种放法,第i种方法
        {
            // cout << "method = " << i << endl;
            for (int j = 0; j < 6; j++) // 按照该种方案的映射，把处理的该层立方体先摆好
            {
                box[process][j] = origin[place[i][j]];
            }
            // 接下来看这种摆法是否可行
            int flag = 1; // 初始标记，表示可行
            // 表示遍历某个侧面时，是否出现重复颜色，used_i[j]标记第i个侧面第j号颜色是否被用过，初始清零
            int used_0[n];
            int used_1[n];
            int used_2[n];
            int used_3[n];
            for (int i = 0; i < n; i++) //
            {
                used_0[i] = 0;
                used_1[i] = 0;
                used_2[i] = 0;
                used_3[i] = 0;
            }
            for (int i = 0; i <= process; i++) // 遍历到现在所有已经放好的立方体，查看每个侧面是否有重复的颜色
            {
                used_0[box[i][0]]++;
                used_1[box[i][1]]++;
                used_2[box[i][2]]++;
                used_3[box[i][3]]++;
                if (used_0[box[i][0]] > 1 || used_1[box[i][1]] > 1 || used_2[box[i][2]] > 1 || used_3[box[i][3]] > 1)
                // 题目要求是最后摆好的整个立方体条的每个侧面都要有n种颜色
                // 但因为n个立方体摆出的，该侧面条有n种颜色，所以相当于每个立方体在该侧面的颜色都不一样
                // 即某个侧面条上每种颜色只能使用一次，这里转换了题目的条件
                // 某个侧面条上某个颜色用了不止一次，不符合条件，该方案以及该方案的子树剪掉
                {
                    flag = 0;
                    // cout << used_0[box[i][0]] << " " << used_1[box[i][1]] << " " << used_2[box[i][2]] << " " << used_3[box[i][3]] << endl;
                    break;
                }
            }
            if (flag == 1) // 目前所有已经摆好的立方体的每个侧面都没有重复的颜色，符合要求，可以继续放下一个立方体
                backtrack(depth + 1);
        }
    }
    return;
}

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> color[i];
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            cin >> box[i][j];
        }
    }
    cout << endl
         << "ans = " << endl;
    backtrack(-1);
    return 0;
}
