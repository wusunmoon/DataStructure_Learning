/*
	程序：双向起泡排序 
	作者：Moyu 
*/
#include<iostream>
#include<vector>
#include<random>
#include<ctime>

using namespace std;

const int Size = 16;

void InitRandomArr(vector<int> &v, int n);
void OutPut(vector<int> &v);
void DoubleBubble(vector<int> &v);
int main()
{
	vector<int> v;
	InitRandomArr(v,Size);
	cout << "随机数组排序：" << endl;
	OutPut(v);
	cout << "排序结果：" << endl;
	DoubleBubble(v);
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
void DoubleBubble(vector<int> &v)
{
	int n = v.size();
	int s = 0;
	int t = n - 1;
	int exchange;
	do{
		exchange = -1;
		for(int i = s; i < t; ++i){
			if(v[i] > v[i+1]){
				int tv = v[i];
				v[i] = v[i+1];
				v[i+1] = tv;
				exchange = i;
			}
		}
		t = exchange;
		for(int j = t; j > s; --j){
			if(v[j] < v[j-1]){
				int tv = v[j];
				v[j] = v[j-1];
				v[j-1] = tv;
				exchange = j;
			}
		}
		s = exchange;
	}while(exchange != -1);
} 
