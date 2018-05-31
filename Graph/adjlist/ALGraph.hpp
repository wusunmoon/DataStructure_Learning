#ifndef ALGRAPH_HPP
#define ALGRAPH_HPP

#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<queue>
#include<stack>
#include<vector>
#include<cstring>

using namespace std;

const int MaxSize = 10;

struct ArcNode{
	int adjvex;
	ArcNode * next;
};
template <class T>
struct VertexNode{
	T vertex;
	ArcNode * firstedge;
};

template <class T>
class ALGraph{
	public:
		ALGraph(T a[], int n, string fpath);		//构造函数 
		~ALGraph();									//析构函数 
		void DFSTraverse(int v);					//递归深度优先遍历 
		void BFSTraverse(int v);					//广度优先遍历 
		void DFSTNorecursion(int v); 				//非递归深度优先遍历 
		void InVertex(int v);						//输出指向v的顶点 
		bool DFSTBePath(int i, int j); 				//求顶点i到j之间是否存在路径（基于深度优先遍历）
		bool BFSTBePath(int i, int j);				//求顶点i到j之间是否存在路径（基于广度优先遍历）
		void Kosaraju();							//求有向图的强连通分量的Kosaraju算法（虽然与查到的定义有些出入） 
	private:
		VertexNode<T> adjlist[MaxSize];				//邻接表 
		VertexNode<T> veradjlist[MaxSize];			//逆邻接表 
		int vertexNum;								//顶点数 
		int arcNum; 								//边数 
		void DFS(int v, bool (&visited)[MaxSize]);	//深度优先递归函数 
		void InitVeradjlist();						//由邻接表初始化逆邻接表 
		bool DFSBePath(int i, bool (&visited)[MaxSize], int j);//求顶点i到j之间是否存在路径（基于递归深度优先遍历） 
		void DFS(int v, bool (&visited)[MaxSize], vector<int>& vseq);
		void DFSV(int v, bool (&visited)[MaxSize], vector<int>& vseq);		
};

template <class T>
ALGraph<T>::ALGraph(T a[], int n, string fpath)
{
	arcNum = 0;
	vertexNum = n;
	for(int i = 0; i < vertexNum; ++i){
		adjlist[i].vertex = a[i];
		adjlist[i].firstedge = NULL;
	}
	
	ifstream fgraph(fpath,ifstream::in);
	string line;
	while(getline(fgraph,line)){
		++arcNum;
		stringstream liness(line);
		int i,j;
		liness >> i >> j;
		ArcNode * pt = new ArcNode{j,NULL};
		pt->next = adjlist[i].firstedge;
		adjlist[i].firstedge = pt;
	}
	
	InitVeradjlist();
}
template <class T>
void ALGraph<T>::InitVeradjlist()
{
	for(int i = 0; i < vertexNum; ++i){
		veradjlist[i].vertex = adjlist[i].vertex;
		veradjlist[i].firstedge = NULL;
	}
	for(int i = 0; i < vertexNum; ++i){
		ArcNode * t = new ArcNode{i,NULL};
		ArcNode * p = adjlist[i].firstedge;
		while(p != NULL){
			t->next = veradjlist[p->adjvex].firstedge;
			veradjlist[p->adjvex].firstedge = t;
			p = p->next;
		}
	}
}

template <class T>
ALGraph<T>::~ALGraph()
{
	ArcNode * pt;
	for(int i = 0; i < vertexNum; ++i){
		while((pt = adjlist[i].firstedge) != NULL){
			adjlist[i].firstedge = pt->next;
			delete pt;
		}
	}
}

template <class T>
void ALGraph<T>::DFSTraverse(int v)
{
	bool visited[MaxSize] = {0};
	DFS(v,visited);
}
template <class T>
void ALGraph<T>::DFS(int v, bool (&visited)[MaxSize])
{
	cout << adjlist[v].vertex << " ";
	visited[v] = 1;
	ArcNode * pt = adjlist[v].firstedge;
	while(pt != NULL){
		if(visited[pt->adjvex] == 0){
			DFS(pt->adjvex,visited);
		}
		pt = pt->next;
	} 
}

template <class T>
void ALGraph<T>::BFSTraverse(int v)
{
	bool visited[MaxSize] = {0};
	queue<int> Q;
	Q.push(v);
	visited[v] = 1;
	while(!Q.empty()){
		int i = Q.front();
		cout << adjlist[i].vertex << " ";
		Q.pop();
		ArcNode * pt = adjlist[i].firstedge;
		while(pt != NULL){
			if(visited[pt->adjvex] == 0){
				Q.push(pt->adjvex);
				visited[pt->adjvex] = 1;
			}
			pt = pt->next;
		}
	}
}

template <class T>
void ALGraph<T>::DFSTNorecursion(int v)
{
	bool visited[MaxSize] = {0};
	cout << adjlist[v].vertex << " ";visited[v] = 1;
	ArcNode * p = adjlist[v].firstedge;
	stack<ArcNode *> s;
	s.push(p);
	while(!s.empty()){
		p = s.top();
		s.pop();
		while(p != NULL){
			int j = p->adjvex;
			if(visited[j] == 0){
				cout << adjlist[j].vertex << " ";
				visited[j] = 1;
				s.push(p); 
				p = adjlist[j].firstedge;
			}
			else
				p = p->next;
		}
	}
}

template <class T>
void ALGraph<T>::InVertex(int v)
{
	ArcNode * p = veradjlist[v].firstedge;
	while(p != NULL){
		cout << veradjlist[v].vertex << "<-" << veradjlist[p->adjvex].vertex << endl;
		p = p->next;
	}
}

template <class T>
bool ALGraph<T>::DFSTBePath(int i, int j)
{
	bool visited[MaxSize] = {0};
	return DFSBePath(i,visited,j);		
} 
template <class T>
bool ALGraph<T>::DFSBePath(int i, bool (&visited)[MaxSize], int j)
{
	if(i == j)
		return true;
	visited[i] = 1;
	ArcNode * pt = adjlist[i].firstedge;
	while(pt != NULL){
		if(visited[pt->adjvex] == 0){
			if(DFSBePath(pt->adjvex,visited,j))
				return true;
		}
		pt = pt->next;
	} 	
	return false;
}

template <class T>
bool ALGraph<T>::BFSTBePath(int i, int j) 
{
	bool visited[MaxSize] = {0};
	queue<int> Q;
	Q.push(i);
	visited[i] = 1;
	while(!Q.empty()){
		int v = Q.front();
		if(v == j)
			return true;
		Q.pop();
		ArcNode * pt = adjlist[v].firstedge;
		while(pt != NULL){
			if(visited[pt->adjvex] == 0){
				Q.push(pt->adjvex);
				visited[pt->adjvex] = 1;
			}
			pt = pt->next;
		}
	}
	return false;	
}

template <class T>
void ALGraph<T>::DFS(int v, bool (&visited)[MaxSize], vector<int>& vSeq)
{
	visited[v] = 1;
	ArcNode * pt = adjlist[v].firstedge;
	while(pt != NULL){
		if(visited[pt->adjvex] == 0){
			DFS(pt->adjvex,visited,vSeq);
		}
		pt = pt->next;
	} 
	vSeq.push_back(v);
}
template <class T>
void ALGraph<T>::DFSV(int v, bool (&visited)[MaxSize], vector<int>& vSeq)
{
	visited[v] = 1;
	ArcNode * pt = veradjlist[v].firstedge;
	while(pt != NULL){
		if(visited[pt->adjvex] == 0){
			DFSV(pt->adjvex,visited,vSeq);
		}
		pt = pt->next;
	} 
	vSeq.push_back(v);
}
template <class T>
void ALGraph<T>::Kosaraju()
{
	vector<int> vertexSeq;
	bool visited[MaxSize] = {0};
	DFS(0,visited,vertexSeq);
	
	memset(visited, 0, MaxSize);
	bool flag[MaxSize] = {0};
	int num = 1;
	while(!vertexSeq.empty()){
		int i = vertexSeq.back();
		vector<int> scc;
		DFSV(i,visited,scc);
		cout << "强连通分量" << num++ << "：";
		for(int i = 0; i < scc.size(); ++i){
			cout << adjlist[scc[i]].vertex << " ";
			flag[scc[i]] = 1;
		}
		cout << endl;
		int loc = vertexSeq.back();
		while(flag[loc]){
			vertexSeq.pop_back();
			if (vertexSeq.empty())
				break;
			loc = vertexSeq.back();
		}
	}
} 
 
#endif
