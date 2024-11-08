#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

bool cmp(pair<int, int> a, pair<int, int> b)
{
    if (a.first < b.first)
        return 1;
    else if (a.first == b.first && a.second < b.second)
        return 1;
    return 0;
}
int main()
{
    int n, m;
    vector<pair<int, int>> v;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int input;
        cin >> input;
        v.push_back(make_pair(input, i));
    }
    cin >> m;
    sort(v.begin(), v.end(), cmp);
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (v[i].first+v[j].first==m)
            {
                cout << v[i].second << " " << v[j].second << endl;
                return 0;
            }
        }
    }
    return 0;
}
