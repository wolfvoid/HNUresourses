#include <iostream>
#include <math.h>
using namespace std;

void BinarySearch(int x[], int left, int right, int &maxi, int &mini)
{
    if (left == right)
    {
        maxi = x[left];
        mini = x[left];
        return;
    }
    else
    {
        int max1, min1, max2, min2;
        int mid = (left + right) / 2;
        // cout << left << " " << mid << " " << right << endl;
        BinarySearch(x, left, mid, max1, min1);
        BinarySearch(x, mid + 1, right, max2, min2);
        maxi = max(max1, max2);
        mini = min(min1, min2);
        return;
    }
}

int main()
{
    int n; // 数据量
    cin >> n;
    int x[n];
    for (int i = 0; i < n; i++)
        cin >> x[i];
    int maxi = x[0];
    int mini = x[0];
    BinarySearch(x, 0, n - 1, maxi, mini);
    cout << "max= " << maxi << endl;
    cout << "min= " << mini << endl;
}
