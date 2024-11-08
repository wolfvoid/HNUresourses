#include <iostream>
#include <string>
using namespace std;

int const N = 100000000;
int ans = 0;
// N=100000000
int main()
{
    for (int i = 1; i < N; i++)
    {
        string s = to_string(i);
        int num = s.size();
        if (num % 2 != 0)
            continue;
        string sa = s.substr(0, num / 2);
        string sb = s.substr(num / 2, num / 2);
        int suma = 0, sumb = 0;
        for (unsigned int i = 0; i < sa.size(); i++)
        {
            suma += (sa[i] - '0');
            sumb += (sb[i] - '0');
        }
        if (suma == sumb)
        {
            ans++;
            // cout << i << endl;
        }
    }
    cout << ans << endl;
    // 4430091
}
