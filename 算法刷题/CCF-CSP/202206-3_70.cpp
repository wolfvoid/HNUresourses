// -*- coding:utf-8 -*-

// File    :   202206-3.cpp
// Time    :   2024/03/26
// Author  :   wolf

#include <iostream>
#include <vector>
const int N = 501;

using namespace std;

// 存储角色信息
struct character
{
    string name;
    int nv;
    vector<string> op;
    int no;
    vector<string> rtype;
    int nn;
    vector<string> rname;
};

// 存储角色与用户/用户组的链接
struct character_link
{
    string cname;
    struct character ch;
    vector<string> u;
    vector<string> g;
};

vector<character> c;
vector<character_link> c_link;

int main()
{
    // 关闭同步
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    // 即使关闭同步，该算法还是会超时，这是算法本身的局限
    int n, m, q;
    cin >> n >> m >> q;
    for (int i = 0; i < n; i++)
    {
        struct character ctemp;
        cin >> ctemp.name;
        cin >> ctemp.nv;
        for (int j = 0; j < ctemp.nv; j++)
        {
            string temp;
            cin >> temp;
            ctemp.op.push_back(temp);
        }
        cin >> ctemp.no;
        for (int j = 0; j < ctemp.no; j++)
        {
            string temp;
            cin >> temp;
            ctemp.rtype.push_back(temp);
        }
        cin >> ctemp.nn;
        for (int j = 0; j < ctemp.nn; j++)
        {
            string temp;
            cin >> temp;
            ctemp.rname.push_back(temp);
        }
        c.push_back(ctemp);
    }
    for (int i = 0; i < m; i++)
    {
        struct character_link cltemp;
        cin >> cltemp.cname;
        for (unsigned int j = 0; j < c.size(); j++)
        {
            if (cltemp.cname == c[j].name)
            {
                cltemp.ch = c[j];
            }
        }
        int ns;
        cin >> ns;
        for (int j = 0; j < ns; j++)
        {
            string ug, ugname;
            cin >> ug >> ugname;
            if (ug == "u")
            {
                cltemp.u.push_back(ugname);
            }
            else if (ug == "g")
            {
                cltemp.g.push_back(ugname);
            }
            else
            {
                cout << "error" << endl;
            }
        }
        c_link.push_back(cltemp);
    }
    for (int i = 0; i < q; i++)
    {
        string query_user;
        cin >> query_user;
        int ng;
        vector<string> query_ugroup;
        cin >> ng;
        for (int j = 0; j < ng; j++)
        {
            string uboxtemp;
            cin >> uboxtemp;
            query_ugroup.push_back(uboxtemp);
        }
        string query_op, query_rtype, query_rname;
        cin >> query_op >> query_rtype >> query_rname;

        // excute
        int ans = 0; // default ok
        vector<character> target_c;
        for (unsigned int j = 0; j < c_link.size(); j++)
        {
            for (unsigned int k = 0; k < c_link[j].u.size(); k++)
            {
                if (query_user == c_link[j].u[k])
                {
                    target_c.push_back(c_link[j].ch);
                }
            }
            for (unsigned int k = 0; k < c_link[j].g.size(); k++)
            {
                for (unsigned int t = 0; t < query_ugroup.size(); t++)
                {
                    if (query_ugroup[t] == c_link[j].g[k])
                    {
                        target_c.push_back(c_link[j].ch);
                    }
                }
            }
        }
        for (unsigned int j = 0; j < target_c.size(); j++)
        {
            character cnow = target_c[j];
            // cout << cnow.name << endl;
            int flag1 = false, flag2 = false, flag3 = false; // default no
            for (unsigned int k = 0; k < cnow.op.size(); k++)
            {
                // cout << query_op << " " << cnow.op[k] << endl;
                if (query_op == cnow.op[k] || cnow.op[k] == "*")
                {
                    flag1 = true;
                    break;
                }
            }
            if (flag1 == false)
                continue;
            for (unsigned int k = 0; k < cnow.rtype.size(); k++)
            {
                // cout << query_op << " " << cnow.op[k] << endl;
                if (query_rtype == cnow.rtype[k] || cnow.rtype[k] == "*")
                {
                    flag2 = true;
                    break;
                }
            }
            if (flag2 == false)
                continue;
            if (cnow.rname.size() == 0)
                flag3 = true;
            else
            {
                for (unsigned int k = 0; k < cnow.rname.size(); k++)
                {
                    if (query_rname == cnow.rname[k])
                    {
                        flag3 = true;
                        break;
                    }
                }
            }
            if (flag3 == false)
                continue;
            // success
            if (flag1 == true && flag2 == true && flag3 == true)
            {
                ans = 1;
                break;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
