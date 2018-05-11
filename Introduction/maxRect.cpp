/*
    给定一组非负整数组成的数组h，代表一组柱状图的高度，其中每个柱子的宽度都为1。 在这组柱状图中找到能组成的最大矩形的面积。
入参h为一个整型数组，代表每个柱子的高度，返回面积的值。

输入描述：
    输入包括两行,第一行包含一个整数n(1 ≤ n ≤ 10000)
    第二行包括n个整数,表示h数组中的每个值,h_i(1 ≤ h_i ≤ 1,000,000)
输出描述：
    输出一个整数,表示最大的矩阵面积。
    
示例：
    输入
    6
    2 1 5 6 2 3
    输出
    10

看到的一种叫简洁的解答：
*/
#include <iostream>
#include <vector>
using namespace std;
int main()
{
	int n;
	vector<int> a;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		int x;
		cin >> x;
		a.push_back(x);
	}
	int ans = 0;
	for (int i = 0; i < n; i++)
	{
		int h = a[i];
		for (int j = i; j < n; j++)
		{
			if (a[j] < h)
				h = a[j];
			int s = (j - i + 1) * h;
			if (ans < s)
				ans = s;
		}
	}
	cout << ans << endl;
	return 0;
}
