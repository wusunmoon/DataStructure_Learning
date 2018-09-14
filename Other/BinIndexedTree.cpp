/*
	程序：树状数组
	作者：Moyu
	理论学习：https://blog.csdn.net/Yaokai_AssultMaster/article/details/79492190
			https://www.cnblogs.com/hsd-/p/6139376.html 
	代码参考：
	https://github.com/jakobkogler/Algorithm-DataStructures/blob/master/RangeQuery/BinaryIndexedTree.cpp
		 
*/
#include<iostream>
#include<vector>

using namespace std;

class BIT{
	public:
		BIT(vector<int> list);
		int Query(int idx);
		int RangeQuery(int from_idx, int to_idx);
		void Update(int idx, int add);
	private:
		vector<int> vt;
};
/*
BIT::BIT(vector<int> list)
{
	//Initialize BIT with list in O(n*log(n))
	vt = vector<int>(list.size() + 1, 0);
	for(int i = 0; i < list.size(); ++i)
		Update(i,list[i]);
}*/
BIT::BIT(vector<int> list)
{
	//Initialize BIT with list in O(n)
	int size = list.size();
	vt = vector<int>(size + 1, 0);
	for(int i = 0; i < size; ++i)
		vt[i+1] = list[i];
	
	++size;
	for(int i = 1; i < size; ++i){
		int j = i + (i & -i);
		vt[j] += vt[i]; 
	}
}
int BIT::Query(int idx)
{
	//Computes prefix sum of up to the element at index idx
	int ret = 0;
	for(++idx; idx > 0; idx -= (idx & -idx))
		ret += vt[idx];
	return ret;
}
int BIT::RangeQuery(int from_idx, int to_idx)
{
	// Computes the range sum between two indices (both inclusive)
	if(from_idx == 0)
		return Query(to_idx);
	else{
		return Query(to_idx) - Query(from_idx - 1);
	}
}
void BIT::Update(int idx, int add)
{
	// Add a value to the element at index idx
	int size = vt.size();
	for(++idx; idx < size; idx += (idx & -idx))
		vt[idx] += add;
}

int main()
{
	vector<int> v{ 1, 7, 3, 0, 5, 8, 3, 2, 6, 2, 1, 1, 4, 5 };
	BIT bit(v);
	cout << bit.RangeQuery(2,4) << endl;
	
	bit.Update(3,3);
	cout << bit.RangeQuery(2,4) << endl;

	return 0;
}
