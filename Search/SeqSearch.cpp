/*
程序：顺序查找
作者：moyu 
*/
#include<iostream>
#include<vector>
#include<random>
#include<ctime>
using namespace std;

const int Max = 10;
void Creat(vector<int>& v)
{
	v.clear();
	uniform_int_distribution<unsigned> u(1,10);
	default_random_engine e(time(0));
	for(size_t i = 0; i < Max; ++i){
		v.push_back(u(e));
	}
}
void SeqSearch(const vector<int> &v, int k)
{
	for(int i = 0; i < v.size(); ++i){
		if(v[i] == k)
			cout << "元素" << k << "在序列中的序号是" << i << endl; 
	}
}
int main()
{
	vector<int> v;
	Creat(v);
	cout << "序列：";
	for(auto i : v)
		cout << i << " ";
	cout << endl;
	int k;
	uniform_int_distribution<unsigned> u(1,10);
	default_random_engine e(time(0));
 	k = u(e);
 	SeqSearch(v,k);
	cout << endl;
	return 0;
}
