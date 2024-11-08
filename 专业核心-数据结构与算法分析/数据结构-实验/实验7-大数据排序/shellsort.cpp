# include <iostream>
# include <algorithm>
using namespace std;

void inssort(int *A, int n, int incr)
{
    for(int i = incr; i < n; i += incr)
        for(int j = i; (j >= incr) && (A[j] < A[j - incr]); j -= incr)
            swap(A[j], A[j - incr]);
}

void shellsort(int *A, int n)
{
    for (int i=n/2; i>2; i/=2)
    {
    for (int j=0;j<i;j++)
    {inssort(A+j-1,n-j,i);}
    }
    inssort(A,n,1);
}


int main()
{
    int n;
    scanf("%d", &n);
    int *a;
    a = new int[n];
    for(int i = 0; i < n; i++)
        cin >> a[i];

    shellsort(a, n);

    for(int i = 0; i < n; i++)
        cout << a[i] << " ";
    cout << endl;
    return 0;
}

