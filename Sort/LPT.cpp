/*
	程序：最长时间优先（LPT）算法 （机器调度问题） 
	问题描述： 
		机器调度是指有m台机器需要处理n个作业，设作业i的处理时间为ti，则对n个作
	业进行机器分配，使得：
		（1）一台机器在同一时间内只能处理一个作业；
		（2）一个作业不能同时在两台机器上处理；
		（3）作业i一旦运行，则需要ti个连续时间单位。
		设计算法进行合理调度，使得在m台机器上处理n个作业所需的处理时间最短。
	基本要求：
		（1）建立问题模型，设计数据结构； 
		（2）设计调度算法，为每个作业分配一台可用机器；
		（3）给出分配方案。 
	作者：Moyu 
*/
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

const int M = 3;	//机器数 
const int N = 7;	//作业数
//机器类 
class Machine{
	friend bool operator<(const Machine& m1, const Machine& m2);
	friend bool operator>(const Machine& m1, const Machine& m2);
	public:
		Machine(int ID,int avail):ID(ID),avail(avail){}
		inline int GetID(){return ID;}
		inline void SetID(int value){ID = value;}
		inline int GetAvail(){return avail;}
		inline void SetAvail(int value){avail = value;}	
	private:
		int ID;
		int avail;
}; 
bool operator<(const Machine& m1, const Machine& m2)
{
	return m1.avail < m2.avail;
}
bool operator>(const Machine& m1, const Machine& m2)
{
	return m1.avail > m2.avail;
}
//作业类 
class Job{
	friend bool operator<(const Job& j1, const Job& j2);
	friend bool operator>(const Job& j1, const Job& j2);
	public:
		Job(int ID,int time):ID(ID),time(time){}
		inline int GetID(){return ID;}
		inline void SetID(int value){ID = value;}
		inline int GetTime(){return time;}
		inline void SetTime(int value){time = value;}		
	private:
		int ID;
		int time;
};
bool operator<(const Job& j1, const Job& j2)
{
	return j1.time < j2.time;
}
bool operator>(const Job& j1, const Job& j2)
{
	return j1.time > j2.time;
}

template<class T>
void BigSift(vector<T> &v, int n, int k);
template<class T>
void SmallSift(vector<T> &v, int n, int k);

int main()
{
	//机器 
	vector<Machine> vm;
	//初始化机器数组 
	for(int i = 0; i < M; ++i){
		Machine m(i,0);
		vm.push_back(m);
	}
	//调整机器数组为小根堆 
	for(int i = ((M-1)>>1); i >= 0; --i)
		SmallSift(vm,M,i);
	
	//作业时间数组	
	vector<int> jt{2,14,4,16,6,5,3};
	//作业 
	vector<Job> vj;
	//初始化作业数组 
	for(int i = 0; i < N; ++i){
		Job j(i,jt[i]);
		vj.push_back(j);
	}
	//调整作业数组为大根堆 
	for(int i = ((N-1)>>1); i >= 0; --i)
		BigSift(vj,N,i);
	//调度结果
	vector<vector<int>> ret(M);
	
	if(N <= M){
		for(int i = 0; i < N; ++i){
			ret[i].push_back(i);
		}
		for(int i = 0; i < M; ++i)
			cout << "m" << i << ":" << ret[i][0] << endl;
		cout << "最短调度长度：" << vj[0].GetTime() << endl;
	}
	else{
		int n = N;
		for(int i = 0; i < N; ++i){
			vm[0].SetAvail(vm[0].GetAvail() + vj[0].GetTime());
			ret[vm[0].GetID()].push_back(vj[0].GetID());
			
			Job jt = vj[0];
			vj[0] = vj[n-1];
			vj[n-1] = jt;
			BigSift(vj,--n,0);
			
			SmallSift(vm,M,0);
		}
		for(int i = 0; i < M; ++i){
			cout << "m" << i << " : ";
			for(auto j : ret[i])
				cout << j << " ";
			cout << endl;
		}
		cout << "最短调度长度：" << max_element(vm.begin(),vm.end())->GetAvail() << endl;				
	}
	
	return 0;
}
/*
	函数：大根堆调整
	参数：v：待调整数组  n：数组元素数量 k：待调整位置 
*/
template<class T>
void BigSift(vector<T> &v, int n, int k)
{
	int i = k;
	int j = 2 * i + 1;
	while(j < n){
		if(j < n - 1){
			if(v[j] < v[j+1])
				++j;
		}
		if(v[i] > v[j])
			break;
		else{
			T t = v[i];
			v[i] = v[j];
			v[j] = t;
		}
		i = j;
		j = 2 * i + 1;
	}
}
/*
	函数：小根堆调整
	参数：v：待调整数组  n：数组元素数量 k：待调整位置 
*/
template<class T>
void SmallSift(vector<T> &v, int n, int k)
{
	int i = k;
	int j = 2 * i + 1;
	while(j < n){
		if(j < n - 1){
			if(v[j] > v[j+1])
				++j;
		}
		if(v[i] < v[j])
			break;
		else{
			T t = v[i];
			v[i] = v[j];
			v[j] = t;
		}
		i = j;
		j = 2 * i + 1;
	}	
}
