/*
程序：折半查找
作者：Moyu 
*/
#include<iostream>
#include<vector>
#include<random>
#include<ctime>

using namespace std;

const int Max = 10;

void Creat(vector<int> &v)
{
	uniform_int_distribution<unsigned> u(1,10);
	default_random_engine e(time(0));
	v.push_back(u(e));
	for(size_t i = 1; i < Max; ++i)
		v.push_back(v[i-1] + u(e));
}
int BinSearch(const vector<int> &v, int k)
{
	int low = 0, high = v.size()-1;
	while(low <= high){
		int mid = (low + high) / 2;
		if(k == v[mid])
			return mid;
		else if(k < v[mid])
			high = mid - 1;
		else
			low = mid + 1;
	}
	return -1;
}
int main()
{
	vector<int> v;
	Creat(v);
	for(auto i : v)
		cout << i << " ";
	cout << endl;
	uniform_int_distribution<unsigned> u(0,9);
	default_random_engine e(time(0));
	int k = v[(u(e)+u(e))/2];
	int location = BinSearch(v,k);
	cout << "元素" << k << "在序列号中的序号是" << location;
	return 0;
}
