/*
    程序：第j小元素
    作者：Moyu
*/
#include<iostream>
#include<vector>
#include<random>
#include<ctime>

using namespace std;

const int Size = 10;

void InitRandomArr(vector<int> &v, int n);
void OutPut(vector<int> &v);
int Partition(vector<int> &v, int lo, int hi);
int Jth(vector<int> &v, int j); 

int main()
{
	vector<int> v;
	InitRandomArr(v,Size);
	cout << "随机数组：" << endl;
	OutPut(v);
	int j;
	cout << "输入j：";
	cin >> j;
	cout << "第" << j << "小元素为：" << Jth(v,j-1) << endl;
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
	for(int i = 0; i < n; ++i)
		v.push_back(u(e));	
} 
/*
	函数：输出向量
	参数：v：带输出向量 
*/ 
void OutPut(vector<int> &v)
{
	for(auto i : v){
		cout << i << " ";
	}
	cout << endl;
}
/*
	函数：快速排序一次划分
	参数：v：待排数组  lo：数组下限  hi：数组上限 
*/ 
int Partition(vector<int> &v, int lo, int hi)
{
	int povit = v[lo];
	while(lo < hi){
		while(lo < hi && povit <= v[hi])
			--hi;
		v[lo] = v[hi];
		while(lo < hi && povit >= v[lo])
			++lo;
		v[hi] = v[lo];
	}
	v[lo] = povit;
	
	return lo;
}
/*
	函数：第j小元素（0 <= j < n）
	参数：v：数组  j：序数
	返回值： 第j小元素（0 <= j < n）
*/
int Jth(vector<int> &v, int j)
{
	int n = v.size();
	int s = 0;
	int t = n - 1;
	int m = Partition(v,s,t);
	while(m != j){
		if(m < j){
			m = Partition(v,m+1,t);
		}
		else{
			m = Partition(v,s,m-1);
		}
	}
	return v[m];
}
