// -*- coding:utf-8 -*-

// File    :   202206-3.cpp
// Time    :   2024/03/26
// Author  :   wolf

#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <unordered_set>
#include <vector>
// 有参考https://blog.csdn.net/Andy_Xie007/article/details/133800502
const int N = 501;

using namespace std;
struct character
{
    string name;
    set<string> op;    // 操作
    set<string> rtype; // 资源种类
    set<string> rname; // 资源名称
    // 使用unordered_set会加快速度：2.984s -> 2.39s
    // unordered_set<string> op;    / 操作
    // unordered_set<string> rtype; // 资源种类
    // unordered_set<string> rname; // 资源名称
};

map<string, character> c; // 角色名称 - 角色本体映射
// 使用find进行检索O(n)时间复杂度，比数组快

// 判断cnow角色是否有对(query_op,query_rtype,query_rname)的访问权限
// 使用&传递地址而不是参复制，节省大量时间，否则超时
int check(const character &cnow, const string &query_op, const string &query_rtype, const string &query_rname)
{
    if (cnow.op.count(query_op) == 0 && cnow.op.count("*") == 0)
        return 0;
    if (cnow.rtype.count(query_rtype) == 0 && cnow.rtype.count("*") == 0)
        return 0;
    if (cnow.rname.count(query_rname) == 0 && !cnow.rname.empty())
        return 0;
    return 1;
}

int main()
{
    // 关闭同步
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    // 加了以上三句话，由90->100
    int n, m, q;
    cin >> n >> m >> q;
    for (int i = 0; i < n; i++)
    {
        struct character ctemp;
        string temp;
        int nv, no, nn;
        cin >> ctemp.name;
        cin >> nv;
        for (int j = 0; j < nv; j++)
        {
            cin >> temp;
            ctemp.op.insert(temp);
        }
        cin >> no;
        for (int j = 0; j < no; j++)
        {
            cin >> temp;
            ctemp.rtype.insert(temp);
        }
        cin >> nn;
        for (int j = 0; j < nn; j++)
        {
            cin >> temp;
            ctemp.rname.insert(temp);
        }
        c.insert(make_pair(ctemp.name, ctemp));
    }

    // 使用多元map保存用户，用户组和角色之间的关联关系，查找会很快
    multimap<string, string> relative_u; // user - character
    multimap<string, string> relative_g; // group - character

    for (int i = 0; i < m; i++)
    {
        string cname;
        cin >> cname;
        int ns;
        cin >> ns;
        for (int j = 0; j < ns; j++)
        {
            string ug, ugname;
            cin >> ug >> ugname;
            if (ug == "u")
            {
                relative_u.insert(make_pair(ugname, cname));
            }
            else if (ug == "g")
            {
                relative_g.insert(make_pair(ugname, cname));
            }
            else
            {
                cout << "error" << endl;
            }
        }
    }
    for (int i = 0; i < q; i++)
    {
        string query_user;
        cin >> query_user;
        int ng;
        cin >> ng;
        vector<string> query_ugroup;
        for (int j = 0; j < ng; j++)
        {
            string uboxtemp;
            cin >> uboxtemp;
            query_ugroup.push_back(uboxtemp);
        }

        string query_op, query_rtype, query_rname;
        cin >> query_op >> query_rtype >> query_rname;

        // excute
        int flag = 0;
        vector<character> target_c;

        // u
        pair<multimap<string, string>::iterator, multimap<string, string>::iterator> range_u = relative_u.equal_range(query_user);
        // auto range_u = relative_u.equal_range(query_user);
        for (auto it = range_u.first; it != range_u.second; it++)
        {
            if (check(c.find(it->second)->second, query_op, query_rtype, query_rname))
            {
                flag = 1;
                break;
            }
        }
        if (flag == 1)
        {
            cout << 1 << endl;
            continue;
        }

        // g
        for (unsigned int j = 0; j < query_ugroup.size(); j++)
        {
            pair<multimap<string, string>::iterator, multimap<string, string>::iterator> range_g = relative_g.equal_range(query_ugroup[j]);
            // auto range_g = relative_g.equal_range(query_ugroup[j]);
            for (auto it = range_g.first; it != range_g.second; it++)
            {
                if (check(c.find(it->second)->second, query_op, query_rtype, query_rname))
                {
                    flag = 1;
                    break;
                }
            }
            if (flag == 1)
            {
                break;
            }
        }
        if (flag == 1)
        {
            cout << 1 << endl;
            continue;
        }
        cout << 0 << endl;
    }
    return 0;
}
