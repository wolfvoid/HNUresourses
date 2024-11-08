// -*- coding:utf-8 -*-

// File    :   202309-3.cpp
// Time    :   2024/03/24
// Author  :   wolf

#include <iostream>
#include <map>
#include <sstream>
#include <stack>
#include <vector>
using namespace std;
#define ll long long
const ll mod = 1e9 + 7;
// 有参考 https://blog.csdn.net/qq_62571980/article/details/133958027
// 不开longlong见祖宗
struct item
{
    // a * x1^n1 * x2^n2 * ……
    ll coefficient;
    map<int, int> m;
    item(ll coefficient, map<int, int> m)
    {
        this->coefficient = coefficient;
        this->m = m;
    }
    item(){};
};

struct formula
{
    vector<item> v;
    formula(vector<item> v)
    {
        this->v = v;
    }
    formula(){};
};

formula formula_add(formula a, formula b) // a+b
{
    for (unsigned int i = 0; i < b.v.size(); i++)
    {
        a.v.push_back(b.v[i]);
    }
    return a;
}

formula formula_sub(formula a, formula b) // a-b
{
    for (unsigned int i = 0; i < b.v.size(); i++)
    {
        b.v[i].coefficient *= -1;
        a.v.push_back(b.v[i]);
    }
    return a;
}

item item_multiply(item a, item b) // 乘积项乘法
{
    ll coefficient_c = a.coefficient * b.coefficient;
    map<int, int> m_c;
    map<int, int>::iterator it;
    for (it = a.m.begin(); it != a.m.end(); it++)
    {
        m_c[it->first] = a.m[it->first] + b.m[it->first];
        b.m.erase(it->first);
    }
    for (it = b.m.begin(); it != b.m.end(); it++)
    {
        m_c[it->first] = b.m[it->first];
    }
    item new_item(coefficient_c, m_c);
    // cout << "a=" << a.coefficient << endl;
    // cout << "b=" << b.coefficient << endl;
    // cout << "c=" << coefficient_c << endl;
    return new_item;
}

formula formula_multiply(formula a, formula b) // 多项式乘法
{
    vector<item> c_v;
    for (unsigned int i = 0; i < a.v.size(); i++)
    {
        for (unsigned int j = 0; j < b.v.size(); j++)
        {
            c_v.push_back(item_multiply(a.v[i], b.v[j]));
        }
    }
    formula new_formula(c_v);
    return new_formula;
}

ll my_pow(int x, int y)
{
    ll ans = 1;
    while (y--)
    {
        ans *= x;
        ans = ans % mod;
    }
    return ans;
}

ll formula_derive(formula x, int goal, int *a)
{
    ll sum = 0;
    for (unsigned int i = 0; i < x.v.size(); i++)
    {
        item now = x.v[i];
        if (now.m.find(goal) != now.m.end())
        {
            ll mul = 1;
            // 该项存在需求导变量才求导，否则为0
            mul = (now.coefficient * now.m[goal]) % mod;
            now.m[goal]--;
            map<int, int>::iterator it;
            for (it = now.m.begin(); it != now.m.end(); it++)
            {
                mul = (mul * my_pow(a[it->first], it->second)) % mod;
            }
            // test
            // cout << mul << " " << endl;
            sum = (sum + mul) % mod;
        }
    }
    return sum;
}

int main()
{
    int n, m;
    cin >> n >> m;
    getchar();
    string str, temp;
    getline(cin, str);
    stringstream ss(str);
    stack<formula> s;
    while (ss >> temp)
    {
        if (temp == "+" || temp == "-" || temp == "*")
        {
            formula f1 = s.top();
            s.pop();
            formula f2 = s.top();
            s.pop();
            formula ans;
            if (temp == "+")
            {
                ans = formula_add(f1, f2);
            }
            else if (temp == "-")
            {
                ans = formula_sub(f2, f1);
            }
            else if (temp == "*")
            {
                ans = formula_multiply(f1, f2);
            }
            s.push(ans);
        }
        else if (temp[0] == 'x')
        {
            temp = temp.substr(1, temp.size() - 1);
            stringstream s1;
            int i;
            s1 << temp;
            s1 >> i;
            map<int, int> new_m;
            new_m.insert({i, 1});
            item new_item(1, new_m);
            vector<item> new_v;
            new_v.push_back(new_item);
            formula new_formula(new_v);
            s.push(new_formula);
        }
        else
        {
            ll c;
            stringstream s2;
            s2 << temp;
            s2 >> c;
            map<int, int> new_m;
            item new_item(c, new_m);
            vector<item> new_v;
            new_v.push_back(new_item);
            formula new_formula(new_v);
            s.push(new_formula);
        }
    }
    formula now;
    now = s.top();
    s.pop();

    // // test
    // cout << "test:" << endl;
    // for (unsigned int i = 0; i < now.v.size(); i++)
    // {
    //     cout << "num = " << i << " "
    //          << "coefficient = " << now.v[i].coefficient << " | ";
    //     map<int, int>::iterator it;
    //     for (it = now.v[i].m.begin(); it != now.v[i].m.end(); it++)
    //     {
    //         cout << it->first << " " << it->second << " | ";
    //     }
    //     cout << endl;
    // }
    // // test end

    while (m--)
    {
        int opnum;
        cin >> opnum;
        int a[n + 1];
        for (int i = 1; i <= n; i++)
            cin >> a[i];
        ll ans = formula_derive(now, opnum, a);
        cout << ((ans < 0) ? ans + mod : ans) << endl; // 当计算整数n对M的模时，若n为负数,需要注意将结果调整至区间[0,M)内
    }
    return 0;
}
