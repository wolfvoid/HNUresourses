# include <iostream>
# include <algorithm>
using namespace std;

inline int findpivot(int *A, int i, int j)
{
    return (i + j) / 2;
}
inline int Partition(int *A, int left, int right, int& pivot)
{
    do
    {
        while(A[++left] < pivot);
        while((left < right) && (pivot < A[--right]));
        swap(A[left], A[right]);
    }
    while(left < right);
    return left;
}
void qsort(int *A, int left, int right)
{
    int i=left;
    int j=right;
    if (j<=i) return;
    int pivotindex=findpivot(A,i,j);
    int temp=A[pivotindex];
    A[pivotindex]=A[j];
    A[j]=temp;
    int k=Partition(A,i-1,j,A[j]);
    int temp2=A[k];
    A[k]=A[j];
    A[j]=temp2;
    qsort(A,i,k-1);
    qsort(A,k+1,j);
}
int main()
{
    int n;
    scanf("%d", &n);
    int *a;
    a = new int[n];

    for(int i = 0; i < n; i++)
        cin >> a[i];

    qsort(a, 0, n - 1);

    for(int i = 0; i < n; i++)
        cout << a[i] << " ";
    cout << endl;
    return 0;
}


