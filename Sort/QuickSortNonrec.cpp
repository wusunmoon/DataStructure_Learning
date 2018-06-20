/*
	程序：快速排序的非递归算法
	作者：Moyu 
*/
#include<iostream>
#include<stack>
#include<vector>
#include<random>
#include<ctime>

using namespace std;

const int Size = 36;

void InitRandomArr(vector<int> &v, int n);
void OutPut(vector<int> &v);
int Partition(vector<int> &v, int lo, int hi);
void QuickSortNonrec(vector<int> &v);
int main()
{
	vector<int> v;
	InitRandomArr(v,Size);
	cout << "随机数组排序：" << endl;
	OutPut(v);
	cout << "排序结果：" << endl;
	QuickSortNonrec(v);
	OutPut(v);
	return 0;
}
void InitRandomArr(vector<int> &v, int n)
{
	uniform_int_distribution<unsigned> u(1,n);
	default_random_engine e(time(0));
	for(int i = 0; i < n; ++i){
		v.push_back(u(e));
	}
}
void OutPut(vector<int> &v)
{
	for(auto i : v)
		cout << i << " ";
	cout << endl;
}
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
void QuickSortNonrec(vector<int> &v)
{
	int n = v.size();
	stack<int> ms;
	stack<int> hs;
	int lo = 0;
	int hi = n - 1;
	while(lo < hi || !ms.empty())
	{
		while(lo < hi){
			int m = Partition(v,lo,hi);
			ms.push(m);
			hs.push(hi);
			hi = m - 1; 
		}	
		if(!ms.empty()){
			int m = ms.top();
			ms.pop();
			lo = m + 1;
			hi = hs.top();
			hs.pop();
		}
	}	
}
