#ifndef DIRGRAPHNORING
#define DIRGRAPHNORING

#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<stack>

using namespace std;

const int MaxSize = 10;

struct ArcNode{
	int adjvex;		//邻接点 
	ArcNode * next;	//下指针 
};
template <class T>
struct VertexNode{
	int in;					//入度 
	T vertex;				//顶点 
	ArcNode * firstedge;	//第一条边指针 
};

template <class T>
class ALGraph{
	public:
		ALGraph(T a[], int n);
		~ALGraph();
		bool TopSort(); 
		bool TopSortPlus(); 
	private:
		VertexNode<T> adjlist[MaxSize];
		int vertexNum;
		int arcNum; 
};

template <class T>
ALGraph<T>::ALGraph(T a[], int n)
{
	arcNum = 0;
	vertexNum = n;
	for(int i = 0; i < vertexNum; ++i){
		adjlist[i].in = 0;
		adjlist[i].vertex = a[i];
		adjlist[i].firstedge = NULL;
	}
	
	ifstream fgraph("DirGraph.txt",ifstream::in);
	string line;
	while(getline(fgraph,line)){
		++arcNum;
		stringstream liness(line);
		int i,j;
		liness >> i >> j;
		ArcNode * pt = new ArcNode{j,NULL};
		pt->next = adjlist[i].firstedge;
		adjlist[i].firstedge = pt;
		++adjlist[j].in;
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
bool ALGraph<T>::TopSort()
{
	stack<int> s;
	for(int i = 0; i < vertexNum; ++i){
		if(adjlist[i].in == 0)
			s.push(i);
	}
	
	int num = 0;
	while(!s.empty()){
		int i = s.top();
		cout << adjlist[i].vertex << " "; 
		s.pop();
		++num;
		ArcNode * pt = adjlist[i].firstedge;
		while(pt != NULL){
			--adjlist[pt->adjvex].in;
			if(adjlist[pt->adjvex].in == 0)
				s.push(pt->adjvex);
			pt = pt->next;
		}
	}
	if(num == vertexNum)
		return true;
	else
		return false;
}
/*
	拓扑排序改进版本 
*/
template <class T>
bool ALGraph<T>::TopSortPlus()
{
	int top = -1;
	for(int i = 0; i < vertexNum; ++i){
		if(adjlist[i].in == 0){
			adjlist[i].in = top;
			top = i;
		}
	}
	if(top == -1)
		return false;
	int num = 0;
	do{
		cout << adjlist[top].vertex  << " ";
		++num;
		int t = adjlist[top].in;
		ArcNode * p = adjlist[top].firstedge;
		adjlist[top].in = -1;
		top = t;
		while(p != NULL){
			--adjlist[p->adjvex].in;
			if(adjlist[p->adjvex].in == 0){
				adjlist[p->adjvex].in = top;
				top = p->adjvex;
			}
			p = p->next;
		}
	}while(top != -1);
	
	if(num == vertexNum)
		return true;
	else
		return false;
	
}

#endif
