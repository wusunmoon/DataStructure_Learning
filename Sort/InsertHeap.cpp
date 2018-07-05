/*
	程序：插入法调整堆
	作者：Moyu 
*/
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

void InsertHeap(vector<int> &v)
{
	int k = v.size() - 1;
	int x = v[k];
	while(k > 0 && v[(k-1)/2] < x){
		v[k] = v[(k-1)/2];
		k = (k - 1) / 2;
	}
	v[k] = x;
}
int main()
{
	vector<int> v{50,40,45,36,32,18,22,30};
	v.push_back(55);
	for(auto i : v)
		cout << i << " ";
	cout << endl;
	InsertHeap(v);
	for(auto i : v)
		cout << i << " ";
	cout << endl;
	
	return 0;
} 
