// // -*- coding:utf-8 -*-

// // File    :   temp.cpp
// // Time    :   2024/03/24
// // Author  :   wolf

// #include <iostream>
// #include <math.h>
// #include <sstream>
// #include <vector>
// #define ll long long
// using namespace std;

// ll my_pow(int x, int y)
// {
//     ll ans = 1;
//     while (y--)
//         ans *= x;
//     return ans;
// }

// struct node
// {
//     int a;
//     vector<int> b;
//     node *tt;
// };

// int main()
// {
//     // cout << my_pow(2, 4) << endl;
//     // string temp = "-100000";
//     // ll c;
//     // stringstream s2;
//     // s2 << temp;
//     // s2 >> c;
//     // cout << c << endl;

//     // node m;
//     // m.b.push_back(3);
//     // m.b.push_back(4);
//     // m.b.push_back(5);
//     // m.tt = &m;
//     // node n;
//     // n = m;
//     // cout << n.tt;
//     // for (int i = 0; i < n.b.size(); i++)
//     // {
//     //     cout << n.b[i] << " ";
//     // }
//     // cout << m.tt;
//     // vector<int> n;
//     // for (unsigned int i = 0; i < n.size(); i++)
//     // {
//     //     cout << n[i] << endl;
//     // }
//     // cout << "ok"<<endl;
//     int N = 66;
//     int n = 3;
//     int r = floor((double)N / (n + 1));
//     cout << (double)N / (n + 1) << endl;
//     cout << r << endl;
//     return 0;
// }

#include <bitset>
#include <cmath>
#include <iomanip>
#include <iostream>
using namespace std;
void printFloatBinary(float num)
{
    // 将浮点数的地址强制转换为整数的指针，以便访问其二进制表示
    int *intPtr = reinterpret_cast<int *>(&num);

    // 通过取地址转换后，使用bitset打印浮点数的二进制表示
    cout << bitset<sizeof(float) * 8>(*intPtr) << endl;
}

void printIntBinary(int num)
{
    // 将浮点数的地址强制转换为整数的指针，以便访问其二进制表示
    int *intPtr = reinterpret_cast<int *>(&num);

    // 通过取地址转换后，使用bitset打印浮点数的二进制表示
    cout << bitset<sizeof(int) * 8>(*intPtr) << endl;
}

int main()
{
    float a = 0.0;
    int b = 0;
    double c = 0;
    // 土豪A
    for (int i = 0; i < 100000000; i++)
    {

        a += 1;
        b += 1;
        if (a != b) // b >= 16777215 && b < 16777220
        {
            cout << fixed << setprecision(8) << a << "   " << b << endl;
            printFloatBinary(a);
            printIntBinary(b);
            cout << (double)(b - a) << endl;
            break;
        }
    }
}
