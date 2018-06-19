/*
	程序： 基于折半查找寻找插入位置的直接插入排序
	作者：Moyu 
*/
#include<iostream>
#include<vector>
#include<random>
#include<ctime>

using namespace std;

const int Size = 36;
void InitRandomArr(vector<int> &v, int n);
void OutPut(const vector<int> &v);
void InsertSortPlus(vector<int> &v);

int main()
{
	vector<int> v;
	InitRandomArr(v,Size);
	cout << "随机数组排序：" << endl; 
	OutPut(v);
	InsertSortPlus(v);
	cout << "排序结果：" << endl;
	OutPut(v);
	return 0;
}
/*
	函数：初始化随机数组
	参数：v：数组 	n：初始化大小 
*/ 
void InitRandomArr(vector<int> &v, int n)
{
	v.clear();
	uniform_int_distribution<unsigned> u(1,n);
	default_random_engine e(time(0));
	for(size_t i = 0; i < n; ++i)
		v.push_back(u(e)); 
}
/*
	函数：输出向量
	参数：v：带输出向量 
*/ 
void OutPut(const vector<int> &v)
{
	for(auto i : v)
		cout << i << " ";
	cout << endl;
}
/*
	函数：基于折半查找寻找插入位置的直接插入排序
	参数：v:待排数组 
	Bug修复：当为特殊情况a m b且t<v[m]时，应插在a之后
*/
void InsertSortPlus(vector<int> &v)
{
	int n = v.size();
	for(int i = 1; i < n; ++i){
		int t = v[i];
		int a = 0;
		int b = i - 1;
		while(a < b){
			int m = (a + b) / 2;
			if(t < v[m])
				b = m - 1;
			else
				a = m + 1;
		}
		if(v[a] < t)//特殊情况
			++a;
		for(int j = i - 1; j >= a; --j)
			v[j+1] = v[j];
		v[a] = t;
	}
}
