#pragma once

#include<vector>

using namespace std;

//vector类型查找算法,找到不大于e的最大关键码
template<typename T>
int VecSearch(vector<T>& v, const T& e)
{
	int r = -1;	//r的初值为-1是考虑到当v.size()==0时，后面程序不会出错
	for (int i = 0; i < v.size(); ++i) {
		if (v[i] <= e)
			r = i;
		else
			break;
	}	
	return r;	
}

//vector类型插入算法
template<typename T>	//将e作为秩为r元素插入
int VecInsert(vector<T>& v, int r, const T& e)	//assert：0 <= r <= size
{
	v.insert(v.begin() + r, e);
	return r;
}

//vector类型删除算法
template<typename T>	//删除向量中秩为r的元素
T VecRemove(vector<T>& v, int r)	//0 <= r < size
{
	T e = v[r];	//备份被删除元素
	v.erase(v.begin() + r);
	return e;	//返回被删除元素
}