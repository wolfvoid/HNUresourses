#include <iostream>
#include <math.h>
using namespace std;

void copy(int x[],int y[],int left,int right)
{
    for (int i=left; i<=right; i++) x[i]=y[i];
}

void Merge(int x[],int y[],int left,int mid,int right)
{
    // 合并x[left:mid] x[mid+1,right] 到 y[left:right]
    //cout<< "merge:"<<left<<" "<<mid<<" "<<right<<endl;
    int i=left,j=mid+1,k=left;
    while ((i<=mid) && (j<=right))
    {
        if (x[i]<=x[j]) y[k++]=x[i++];
        else y[k++]=x[j++];
        if (i>mid) //左边已经合并完了，剩下右边直接加入
            for (int t=j; t<=right; t++) y[k++]=x[t];
        else if (j>right) //右边已经合并完了，剩下左边直接加入
            for (int t=i; t<=mid; t++) y[k++]=x[t];
    }
    //cout<<"merge_result"<<endl;
    //for (int i=left;i<=right;i++)cout<<y[i]<<" ";
    //cout<<endl;
}

void MergeSort(int x[], int left, int right)
{
    if (left<right)
    {
        int mid=(left+right)/2;
        int y[right+1];
        //cout<<"left mid right "<<left<<" "<<mid<<" "<< right<<endl;
        //cout<<"mergesort"<<left<<" "<<mid<<endl;
        MergeSort(x,left,mid);
        //cout<<"mergesort"<<mid+1<<" "<<right<<endl;
        MergeSort(x,mid+1,right);
        Merge(x,y,left,mid,right);
        copy(x,y,left,right);
    }
}

int main()
{
    int n; // 数据量
    cin >> n;
    int x[n];
    for (int i = 0; i < n; i++)
        cin >> x[i];
    MergeSort(x,0,n-1);
    for (int i=0; i<n;i++) cout<<x[i]<<" ";
}
