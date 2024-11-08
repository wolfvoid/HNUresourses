#include <iostream>
#include <string.h>
using namespace std;

int trans[10] = {13, 1, 2, 3, 5, 4, 4, 2, 2, 2};
int monthd[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
bool check(int num)
{
    int year = num / 10000;
    int month = num / 100 % 100;
    int day = num % 100;
    if (month == 0 || month > 12)
        return 0;
    bool flag = 0;
    if (year % 4 == 0 && month == 2 && day == 29)
        flag = 1;
    int sum = 0;
    if (flag || (day != 0 && day <= monthd[month]))
    {
        cout << year << " " << month << " " << day << endl;
        string s = to_string(num);
        for (int i = 0; i < 8; i++)
        {
            sum += (trans[s[i] - '0']);
        }
    }
    if (sum > 50)
        return 1;
    return 0;
}

int main()
{
    int ans = 0;
    for (int i = 20000101; i <= 20240413; i++)
    {
        if (check(i) == 1)
            ans++;
    }
    cout << ans << endl;
}
