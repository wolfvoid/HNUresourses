#include <stdio.h>
using namespace std;

int a,b;
int ans = 0;        // 符合要求的数的最大约数
int ans_num = 0;    // 符合要求的数

void func(){//暴力出奇迹
    for(int i=a;i<=b;i++){
        int ret=0;
        for(int j=1;j*j<=i;j++){
            if(i%j==0) ret+=2;
            if(j*j==i) ret--;
        }
        if(ret>ans){
            ans_num=i;
            ans=ret;
        }
    }
}

int main()
{
    scanf("%d %d",&a, &b);
    func();
    printf("Between %d and %d, %lld has a maximum of %lld divisors.\n",a,b,ans_num,ans);
    return 0;
}
