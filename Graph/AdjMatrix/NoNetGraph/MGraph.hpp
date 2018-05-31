#ifndef MGRAPH_HPP
#define MGRAPH_HPP

#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<queue>
#include<vector>

using namespace std;

const int MaxSize = 10;

template <class T>
class MGraph{
	public:
		MGraph(T a[], int n, string fpath);	//构造函数，建立一个n个顶点的图 
		~MGraph(){}						//析构函数为空 
		void DFSTraverse(int v);		//深度优先遍历 
		void BFSTraverse(int v);		//广度优先遍历 
		bool BeEulerRing();				//是否存在欧拉回路
		void TangramColor();			//七巧板涂色问题
		void HamiltonPath();			//哈密顿路径 
		
	private:
		T vertex[MaxSize];				//图的顶点数组 
		int arc[MaxSize][MaxSize];		//邻接矩阵 
		int vertexNum;					//顶点数 
		int arcNum;						//边数 
		void DFS(int v,bool (&visited)[MaxSize]);
		void DFSTangramColor(int v, int color[], int &num);
		void DFSHa(int v, bool (&visited)[MaxSize], vector<int> &vseq); 
};

template <class T>
MGraph<T>::MGraph(T a[], int n, string fpath)
{
	vertexNum = n;
	for(int i = 0; i < n; ++i)
		vertex[i] = a[i];
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
			arc[i][j] = 0;
	
	int e = 0;
	ifstream fgraph(fpath,ifstream::in);
	string line;
	while(getline(fgraph,line)){
		stringstream liness(line);
		int i,j;
		liness >> i >> j;
		arc[i][j] = 1;
		++e;
	}		
	arcNum = e;
} 

template <class T>
void MGraph<T>::DFSTraverse(int v)
{
	bool visited[MaxSize] = {0};
	DFS(v,visited);
}
template <class T>
void MGraph<T>::DFS(int v,bool (&visited)[MaxSize])
{
	cout << vertex[v] << " ";
	visited[v] = 1;
	for(int j = 0; j < vertexNum; ++j){
		if(arc[v][j] > 0 && visited[j] == 0){
			DFS(j,visited);
		}
	}
}

template <class T>
void MGraph<T>::BFSTraverse(int v)
{
	bool visited[MaxSize] = {0};
	queue<int> Q;
	Q.push(v);
	visited[v] = 1;
	while(!Q.empty()){
		int i = Q.front();
		Q.pop();
		cout << vertex[i] << " ";

		for(int j = 0; j < vertexNum; ++j){
			if(arc[i][j] > 0 && visited[j] == 0){
				Q.push(j);
				visited[j] = 1;
			}
		}
	}
}

template <class T>
bool MGraph<T>::BeEulerRing()
{
	int count = 0;
	for(int i = 0; i < vertexNum; ++i){
		int t = 0;
		for(int j = 0; j < vertexNum; ++j){
			t += arc[i][j];
		}
		if(t%2){
			++count;
		}
	}
	if(count == 0 || count == 2){
		return true;
	}
	else{
		return false;
	}
}

template <class T>
void MGraph<T>::TangramColor()
{
	int color[7] = { 0 };
	int num = 0;
	DFSTangramColor(0, color, num);
	cout << "共有" << num << "种涂法" << endl;
}
template <class T>
void MGraph<T>::DFSTangramColor(int v, int color[], int &num)
{
	if (v >= 7) {
		++num;
		for (int i = 0; i < 7; ++i) {
			cout << color[i] << " ";
		}
		cout << endl;
		return;
	}
	else {
		for (int i = 1; i <= 4; ++i) {
			color[v] = i;
			bool flag = 0;
			for (int j = 0; j < vertexNum; ++j) {
				if (arc[v][j] > 0 && color[v] == color[j]) {
					flag = 1;
					break;
				}
			}
			if(!flag)
				DFSTangramColor(v + 1, color, num);
		}
	}
}

template <class T>
void MGraph<T>::HamiltonPath()
{
	vector<int> vseq;
	bool visited[MaxSize] = {0};
	DFSHa(0,visited,vseq);
	if(vseq.size() < vertexNum)
		cout << "此图不存在哈密顿路径。" << endl;
	else{
		cout << "此图哈密顿路径：" << endl;
		for (int i = 0; i < vseq.size(); ++i)
			cout << vertex[vseq[i]] << (i == vseq.size() - 1 ? "" : "->");
	}
	cout << endl;
}
template <class T>
void MGraph<T>::DFSHa(int v, bool (&visited)[MaxSize], vector<int> &vseq)
{
	visited[v] = 1;
	vseq.push_back(v);
	for(int j = 0; j < vertexNum; ++j){
		if(visited[j] == 0 && arc[v][j] == 1)
			DFSHa(j,visited,vseq);
	}	
	if(vseq.size() == vertexNum)
		return;
	visited[v] = 0;
	vseq.pop_back();
} 

#endif
