/*
	程序：排序算法时间性能比较
	作者：Moyu 
*/

#include<iostream>
#include<random>
#include<ctime>

using namespace std;

const int Size = 24;	//比较数据数量 

int movec;	//交换次数
int compc;  //比较次数
 
void InitRandomArr(vector<int> &v, int n);
void InitPosArr(vector<int> &v, int n);
void InitNegArr(vector<int> &v, int n);
void OutPut(const vector<int> &v); 
void InsertSort(vector<int> &v);
void ShellSort(vector<int> &v);
void BubbleSort(vector<int> &v);
int Partition(vector<int> &v, int lo, int hi);
void QuickSortRec(vector<int> &v, int lo, int hi);
void QuickSort(vector<int> &v);
void SelectSort(vector<int> &v);
void Sift(vector<int> &v,int k,int n);
void HeapSort(vector<int> &v);
void Merge(vector<int> &v, vector<int> &v1, int s, int m, int t); 
void MergePass(vector<int> &v, vector<int> &v1, int h);
void MergeSort(vector<int> &v);

int main()
{
	vector<int> v;
	InitRandomArr(v,Size);
	cout << "随机数列排序：" << endl;
	OutPut(v);
	 
	vector<int> vt(v);	 
	InsertSort(vt);
	vt = v;
	ShellSort(vt);
	vt = v;
	BubbleSort(vt);
	vt = v;
	QuickSort(vt);
	vt = v;
	SelectSort(vt);
	vt = v;
	HeapSort(vt);
	vt = v;
	MergeSort(vt);

	cout << "-----------------------------------------------------" << endl; 
	
	InitPosArr(v,Size);
	cout << "正序数列排序：" << endl;
	OutPut(v);
	vt = v;	 
	InsertSort(vt);
	vt = v;
	ShellSort(vt);
	vt = v;
	BubbleSort(vt);
	vt = v;
	QuickSort(vt);
	vt = v;
	SelectSort(vt);
	vt = v;
	HeapSort(vt);
	vt = v;
	MergeSort(vt);

	cout << "-----------------------------------------------------" << endl; 
	
	InitNegArr(v,Size);
	cout << "逆序数列排序：" << endl;
	OutPut(v);
	vt = v;	 
	InsertSort(vt);
	vt = v;
	ShellSort(vt);
	vt = v;
	BubbleSort(vt);
	vt = v;
	QuickSort(vt);
	vt = v;
	SelectSort(vt);
	vt = v;
	HeapSort(vt);
	vt = v;
	MergeSort(vt);
	
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
	函数：初始化正序数组
	参数：v：数组 	n：初始化大小 
*/ 
void InitPosArr(vector<int> &v, int n)
{
	v.clear();
	uniform_int_distribution<unsigned> u(1,9);
	default_random_engine e(time(0));
	v.push_back(u(e)); 
	for(size_t i = 1; i < n; ++i)
		v.push_back(u(e) + v[i-1]); 
}
/*
	函数：初始化逆序数组
	参数：v：数组 	n：初始化大小 
*/ 
void InitNegArr(vector<int> &v, int n)
{
	v.clear();
	v.assign(n,0);
	uniform_int_distribution<unsigned> u(1,9);
	default_random_engine e(time(0));
	v[n-1] = u(e); 
	for(int i = n - 2; i >= 0; --i)
		v[i] = v[i+1] + u(e); 
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
	函数：直接插入排序 
	参数：v：待排数组 
*/
void InsertSort(vector<int> &v)
{
	movec = 0;
	compc = 0; 
	int n = v.size();
	int t;
	int j;
	for(int i = 1; i < n; ++i){
		t = v[i];
		++movec;
		for(j = i - 1; j >=0 && t < v[j]; --j){
			++compc;
			v[j+1] = v[j];
			++movec;
		}
		++compc;
		if(j < 0)
			--compc;
		v[j+1] = t;
		++movec;
	}
	cout << "直接插入排序结果：" << endl;
	OutPut(v);
	cout << "比较次数：" << compc << " 移动次数：" << movec << endl; 
}
/*
	函数：希尔排序 
	参数：v:待排数组 
*/ 
void ShellSort(vector<int> &v)
{
	movec = 0;
	compc = 0; 
	int n = v.size();
	int t;
	int j;
	for(int d = (n>>1); d >= 1; d = (d>>1)){
		for(int i = d; i < n; ++i){
			t = v[i];
			++movec;
			for(j = i - d; j >=0 && t < v[j]; j = j-d){
				++compc;
				v[j+d] = v[j];
				++movec;
			}
			++compc;
			if(j < 0)
				--compc;
			v[j+d] = t; 
			++movec;
		}
	}	
	cout << "希尔排序结果：" << endl;
	OutPut(v);
	cout << "比较次数：" << compc << " 移动次数：" << movec << endl; 
} 
/*
	函数：冒泡排序 
	参数：v：待排数组 
*/ 
void BubbleSort(vector<int> &v)
{
	movec = 0;
	compc = 0; 

	int exchange = v.size()-1;
	int bound;
	while(exchange != 0){
		bound = exchange;
		exchange = 0;
		for(int j = 0; j < bound; ++j){
			++compc; 
			if(v[j] > v[j+1]){
				int t = v[j+1];
				v[j+1] = v[j];
				v[j] = t;
				movec+=3;
				exchange = j;
			}
		}
	}	
	cout << "冒泡排序结果：" << endl;
	OutPut(v);
	cout << "比较次数：" << compc << " 移动次数：" << movec << endl; 
} 
/*
	函数：快速排序一次划分
	参数：v：待排数组  lo：数组下限  hi：数组上限 
*/ 
int Partition(vector<int> &v, int lo, int hi)
{
	int povit = v[lo];
	++movec; 
	while(lo < hi){
		compc += 2;
		while(lo < hi && povit <= v[hi])
			--hi;
		if(lo < hi)
			--compc;
		v[lo] = v[hi];
		++movec;
		
		while(lo < hi && povit >= v[lo])
			++lo;
		if(lo < hi)
			--compc;
		v[hi] = v[lo];
		++movec;
	}
	v[lo] = povit;
	++movec;
	return lo;
}
/*
	函数：快速排序 
	参数：v:待排数组  lo：数组下限  hi：数组上限 
*/ 
void  QuickSortRec(vector<int> &v, int lo, int hi)
{	
	if(lo < hi){
		int m = Partition(v,lo,hi);
		QuickSortRec(v,lo,m-1);
		QuickSortRec(v,m+1,hi);
	}
}
void QuickSort(vector<int> &v)
{
	movec = 0;
	compc = 0; 

	int lo = 0;
	int hi = v.size()-1;
	QuickSortRec(v,lo,hi);
	cout << "快速排序结果：" << endl;
	OutPut(v);
	cout << "比较次数：" << compc << " 移动次数：" << movec << endl; 
}
/*
	函数：简单选择排序 
	参数：v：待排数组 
*/
void SelectSort(vector<int> &v)
{
	movec = 0;
	compc = 0; 
	int n = v.size();
	int index;
	for(int i = 0; i < n-1; ++i){
		index = i;
		for(int j = i+1; j < n; ++j){
			++compc;
			if(v[index] > v[j])
				index = j;
		}
		if(index != i){
			int t = v[index];
			v[index] = v[i];
			v[i] = t;
			movec+=3;
		}
	}	
	cout << "简单选择排序结果：" << endl;
	OutPut(v);
	cout << "比较次数：" << compc << " 移动次数：" << movec << endl; 
}
/*
	函数：筛选法从上到下调整堆 
	参数：v：待排数组  k：待调整位置 n:待排数组元素个数 
*/
void Sift(vector<int> &v,int k,int n)
{
	int i = k;
	int j = 2 * i + 1;
	while(j < n){
		++compc; 
		
		if(j < n-1 && v[j] < v[j+1])
			++j;
			
		if(j >= n-1)
			--compc;
		++compc;
		if(v[i] > v[j])
			break;
		else{
			int t = v[j];
			v[j] = v[i];
			v[i] = t;
			
			movec += 3;
			
			i = j;
			j = 2 * i + 1;
		}
	}
}
/*
	函数：堆排序 
	参数：v：待排数组 
*/
void HeapSort(vector<int> &v)
{
	movec = 0;
	compc = 0; 

	int n = v.size();
	for(int i = (n>>1)-1; i >=0; --i)
		Sift(v,i,n);
	for(int i = 0; i < n-1; ++i){
		int t = v[0];
		v[0] = v[n-1-i];
		v[n-1-i] = t;
		
		movec += 3;
		
		Sift(v,0,n-1-i);
	}	
	cout << "堆排序结果：" << endl;
	OutPut(v);
	cout << "比较次数：" << compc << " 移动次数：" << movec << endl; 

} 
/*
	函数：一次归并 
	参数：v：待排数组  v1：目标数组  s：起始位置 m：第一段终止位置 t：第二段终止位置 
*/
void Merge(vector<int> &v, vector<int> &v1, int s, int m, int t)
{
	int i = s;
	int j = m + 1;
	int k = s;
	while(i <= m && j <= t){
		++compc;
		if(v[i] <= v[j]){
			++movec;
			v1[k++] = v[i++];
		}
		else{
			++movec;
			v1[k++] = v[j++];
		}
	}
	while(i <= m){
		++movec;
		v1[k++] = v[i++];
	}
	
	while(j <= t){
		++movec;
		v1[k++] = v[j++];
	}
}
/*
	函数：一趟归并  
	参数：v：待排数组  v1：目标数组  h：段大小 
*/
void MergePass(vector<int> &v, vector<int> &v1, int h)
{
	int n = v.size();
	int i = 0;
	while(i <= n - 2 * h){
		Merge(v,v1,i,i+h-1,i+2*h-1);
		i = i + 2*h;
	}
	if(i <= n - h)
		Merge(v,v1,i,i+h-1,n-1);
	else{
		while(i < n){ 
			v1[i] = v[i];
			++i;
			++movec; 
		} 
	}
} 
/*
	函数：归并排序 
	参数：v：待排数组 
*/
void MergeSort(vector<int> &v)
{
	movec = 0;
	compc = 0; 

	int n = v.size();
	vector<int> v1(n,0);
	int h = 1;
	while(h < n){
		MergePass(v,v1,h);
		h *= 2;
		MergePass(v1,v,h);
		h *= 2;
	}
	cout << "归并排序结果：" << endl;
	OutPut(v);
	cout << "比较次数：" << compc << " 移动次数：" << movec << endl; 
}
