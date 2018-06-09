/*
	程序：斐波那契查找
	作者：Moyu
1.问题描述
	已经知道，对于有序数据序列进行查找，二分查找法性能是相当好的，时间效率能达
到O(log2 n)，但该算法其实还有些可以改进的地方。普通的折半查找直接通过折半
的方式对有序数据序列进行分割，这种方法实际上不是十分有效。对于大多数的有序数
据序列，通常分布都是比较均匀的，可以通过斐波那契数列对有序表进行分割。斐波那契
查找方法也称为黄金分割法，其平均性能比折半查找要好。
2.基本要求
	（1）设计斐波那契查找算法；
	（2）与普通的折半查找算法进行比较。
3.设计思想
	设n个记录的有序表，且n正好是某个斐波那契数-1，即n=F(k)-1，其分割思想为：
对于表长weiF(k)-1的有序表，以相对于low的偏移量F(k-1)-1取分割点，即mid=low+F(k-1)-1,
对有序表进行分割，则左子表的表长为F(k-1)-1，右子表的表长为(F(k)-1)-(F(k-1)-1)-1=F(k-2)-1。
可见，两个子表的表长也都是某个斐波那契数-1，因而可以对子表继续进行分割。算法的伪代码描述如下:
--------------------------------------------------------------------------
伪代码：
	1.设置初始查找区间：low=1，high=F(k)-1；
	2.计算当前查找区间的表长，计算分割点距区间低端的偏移量。F=F(k)-1;f=F(k-1)-1;
	3.当查找区间存在，执行下列操作：
		3.1 去查找区间的分割点：mid=low+f;
		3.2 将r[mid]与待查值k比较，有以下三种情况：
			（1）若k<r[mid],则查找在左半区间继续进行：
				p=f;f=F-f-1;	//计算分割点距该查找区间低端的偏移量
				F=p;			//计算左半区间的表长
				high=mid-1;		//调整查找区间的高端位置
			（2）若k>r[mid],则查找在右半区间继续进行：
				F=F-f-1;		//计算右半区间的表长 
				f=f-F-1;		//计算分割点距该查找区间低端的偏移量 
				low=mid+1; 		//调整查找区间的低端位置
			（3）若k=r[mid],则查找成功，返回记录在表中位置mid；
	4.退出循环，说明查找区间已不存在，返回查找失败标志-1； 
*/ 
#include<iostream>
#include<vector>
#include<random>
#include<ctime>

using namespace std;

const int M = 19;

long long Fibonacci(int k)
{
	if(k == 1 || k == 2)
		return 1;
	else{
		long long pre = 1;
		long long n = 1;
		int i = 2;
		do{
			long long t = pre + n;
			pre = n;
			n = t;
			++i;
		}while(i != k);
		return n;
	}
	
}
void Creat(vector<int> &v)
{
	uniform_int_distribution<int> u(1,10);
	default_random_engine e(time(0));
	v.push_back(u(e));
	int t = Fibonacci(M) - 1;
	for(size_t i = 1; i < t; ++i){
		v.push_back(v[i-1] + u(e));
	}
}
int FibonacciSearch(vector<int> &v, int k, int &count)
{
	count = 0;
	int low = 0;
	int high = v.size();
	int F = Fibonacci(M) - 1;
	int f = Fibonacci(M-1) -1;
	while(low <= high){
		++count;
		int mid = low + f;
		if(k < v[mid]){
			int p = f;
			f = F - f - 1;
			F = p;
			
			high = mid - 1;
		}
		else if(k > v[mid]){
			F = F - f - 1;
			f = f - F - 1;
			low = mid + 1;
		}
		else{
			return mid;
		}
	}
	return -1;
}
int BinSearch(const vector<int> &v, int k, int &count)
{
	count = 0;
	int low = 0, high = v.size()-1;
	while(low <= high){
		++count;
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

	int t = Fibonacci(M) - 1;	
	uniform_int_distribution<int> u(0,t-1);
	default_random_engine e(time(0));
	int k = v[(u(e) + u(e))/2];
	
	int count;
	cout << "Fibonacci : 查找元素 " << k << "下标为" << FibonacciSearch(v,k,count);
	cout << " 查找次数为" << count << endl;
	cout << "折半查找 : 查找元素 " << k << "下标为" << BinSearch(v,k,count);
	cout << " 查找次数为" << count << endl;
	
	return 0;
}
