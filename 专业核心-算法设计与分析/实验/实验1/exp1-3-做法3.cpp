#include <stdio.h>
using namespace std;

const int max_num = 1000;
int prime[max_num]; // 维护一张质数表
int prime_total = 0;// 质数表中质数的个数
int a,b;
int ans = 0;        // 符合要求的数的最大约数
int ans_num = 0;    // 符合要求的数

// 使用筛法筛出一定范围内的质数
void get_primes(int max_prime){
    bool flag[max_prime+1];
    for (int i=2;i<=max_prime;i++) flag[i] = true;
    for (int i=2;i<=max_prime;i++)
        if(flag[i]){
            for (int j=i+i; j<=max_prime; j+=i)
                flag[j]=false;
    }
    for (int i=2;i<=max_prime;i++)
        if (flag[i]) prime[prime_total++]=i;
    prime_total--;
}

//对每一个状态进行列举，并比较记录各个状态中最小的部分
void search(int depth,long long num,long long sum)
{
    // 对于合法枚举结果的比较处理 （到达终点）
    if (a<=num && num<=b){
        if (sum>ans) {ans=sum; ans_num=num;}
        else if (sum==ans && num<ans_num) {ans_num=num;}
    }
    if (depth>prime_total) return;  // 搜索超出规定层数，直接返回
    if (num*prime[depth]>b) return; // 如果本层的质数乘上去都超范围了，那么之后的质数乘上去必然超范围，故直接返回，且本层没有结果
    long long new_num = num;
    // 以当前num为基础，分别乘上i个prime[depth]，进行深搜
    search(depth+1,num,sum);
    int i=0;
    while(new_num*prime[depth]<=b){
        new_num*=prime[depth];
        i++;
        search(depth+1,new_num,sum*(i+1));
    }
}

int main()
{
    scanf("%d %d",&a, &b);
    get_primes(b);
    search(0,1,1);
    printf("Between %d and %d, %lld has a maximum of %lld divisors.\n",a,b,ans_num,ans);
    return 0;
}
