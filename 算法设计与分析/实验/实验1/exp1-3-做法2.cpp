#include <stdio.h>
using namespace std;

const int max_num = 1000;
int prime[max_num];  // 维护一张质数表
int prime_total = 0; // 质数表中质数的个数
int a, b;
int ans = 0;     // 符合要求的数的最大约数
int ans_num = 0; // 符合要求的数

// 使用筛法筛出一定范围内的质数
void get_primes(int max_prime)
{
    bool flag[max_prime + 1];
    for (int i = 2; i <= max_prime; i++)
        flag[i] = true;
    for (int i = 2; i <= max_prime; i++)
        if (flag[i])
        {
            for (int j = i + i; j <= max_prime; j += i)
                flag[j] = false;
        }
    for (int i = 2; i <= max_prime; i++)
        if (flag[i])
            prime[prime_total++] = i;
    prime_total--;
}

void search()
{
    for (int i = a; i <= b; i++)
    {
        long long now = i;   // 当前待处理数
        long long total = 1; // 当前数的公约数数量
        for (int j = 0; j <= prime_total; j++)
        {
            int num = 1;
            while (now % prime[j] == 0)
            {
                now /= prime[j];
                num++;
            }
            total *= num;
        }
        if (total > ans)
        {
            ans = total;
            ans_num = i;
        }
    }
}

int main()
{
    scanf("%d %d", &a, &b);
    get_primes(100);
    search();
    printf("Between %d and %d, %lld has a maximum of %lld divisors.\n", a, b, ans_num, ans);
    return 0;
}
