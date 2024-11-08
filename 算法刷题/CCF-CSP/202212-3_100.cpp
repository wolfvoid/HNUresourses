#include <bits/stdc++.h>
using namespace std;
int main()
{
	double pi = acos(-1);
	int q[8][8];
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			cin >> q[i][j];
	int m[8][8];
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			m[i][j] = 0;
	int n;
	cin >> n;
	int w[n + 1];
	int T;
	cin >> T;
	for (int i = 1; i <= n; i++)
		cin >> w[i];
	int example[8][8] = {
		/*1*/ {1, 2, 6, 7, 15, 16, 28, 29},
		/*2*/ {3, 5, 8, 14, 17, 27, 30, 43},
		/*3*/ {4, 9, 13, 18, 26, 31, 42, 44},
		/*4*/ {10, 12, 19, 25, 32, 41, 45, 54},
		/*5*/ {11, 20, 24, 33, 40, 46, 53, 55},
		/*6*/ {21, 23, 34, 39, 47, 52, 56, 61},
		/*7*/ {22, 35, 38, 48, 51, 57, 60, 62},
		/*8*/ {36, 37, 49, 50, 58, 59, 63, 64},
	};
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			if (example[i][j] <= n)
				m[i][j] = w[example[i][j]]; // T1

	int m1[8][8];
	double m2[8][8];

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			m1[i][j] = m[i][j] * q[i][j]; // T2
	//		不是矩阵乘法
	//		for (int i=0;i<8;i++)
	//			for (int j=0;j<8;j++)
	//			{
	//				int temp=0;
	//				for (int k=0;k<8;k++)
	//				{
	//					temp+=(m[i][k]*q[k][j]);
	//				}
	//				m1[i][j]=temp;
	//			}

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			m2[i][j] = m1[i][j];
	double m5[8][8];
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			double temp = 0;
			double au, av;
			for (int u = 0; u < 8; u++)
			{
				if (u == 0)
					au = sqrt(0.5);
				else
					au = 1;
				for (int v = 0; v < 8; v++)
				{
					if (v == 0)
						av = sqrt(0.5);
					else
						av = 1;
					temp += (au * av * m2[u][v] * cos(pi * (i + 0.5) * u / 8) * cos(pi * (j + 0.5) * v / 8));
				}
			}
			m5[i][j] = temp / 4 + 128;
			if (m5[i][j] > 255)
				m5[i][j] = 255;
			else if (m5[i][j] < 0)
				m5[i][j] = 0;
			// 如果得到的整数大于255，则取255；如果得到的整数小于0，则取0；
			// 这句话没看到找错误找了好久
		} // T3

	if (T == 0) // 20分
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				cout << m[i][j] << " ";
			}
			cout << endl;
		}
	}
	else if (T == 1) // 40分
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				cout << m1[i][j] << " ";
			}
			cout << endl;
		}
	}
	else if (T == 2) // 100分
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				cout << fixed << setprecision(0) << m5[i][j] << " ";
			}
			cout << endl;
		}
	}
	return 0;
}
