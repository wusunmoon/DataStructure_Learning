#ifndef MGRAPH_HPP
#define MGRAPH_HPP

#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

const int MaxSize = 10;

template <class T>
class MGraph{
	public:
		MGraph(T a[], int n);	//构造函数，建立一个n个顶点的图 
		~MGraph(){}						//析构函数为空 
		void Prim();
		void Kruskal();
	private:
		T vertex[MaxSize];				//图的顶点数组 
		int arc[MaxSize][MaxSize];		//邻接矩阵 
		int vertexNum;					//顶点数 
		int arcNum;						//边数 
};

template <class T>
MGraph<T>::MGraph(T a[], int n)
{
	vertexNum = n;
	for(int i = 0; i < n; ++i)
		vertex[i] = a[i];
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j){
			if(i == j)
				arc[i][j] = 0;
			else
			    arc[i][j] = -1;			//-1表不可达（无穷远） 
		}
	
	int e = 0;
	ifstream fgraph("NetGraph.txt",ifstream::in);
	string line;
	while(getline(fgraph,line)){
		stringstream liness(line);
		int i,j,w;
		liness >> i >> j >> w;
		arc[i][j] = w;
		++e;
	}		
	arcNum = e/2;
} 

int MinEdge(int lowcost[],int n)
{
	int r;
	int min = -1;
	for(int i = 0; i < n; ++i){
		if(lowcost[i] != 0 && lowcost[i] != -1){
			if(min == -1){
				min = lowcost[i];
				r = i;
			}
			else{
				if(min > lowcost[i]){
					min = lowcost[i];
					r = i;
				}
			}
		}
	}	
	return r;
} 
template <class T>
void MGraph<T>::Prim()
{
	int lowcost[MaxSize];
	int adjvex[MaxSize];
	for(int i = 0; i < vertexNum; ++i){
		lowcost[i] = arc[0][i];
		adjvex[i] = 0;
	}
	for(int i = 1; i < vertexNum; ++i){
		int k = MinEdge(lowcost,vertexNum);
		cout << "(" << adjvex[k] << "," << k << ") " << lowcost[k] << endl;
		lowcost[k] = 0;
		for(int j = 0; j < vertexNum; ++j){
			if(lowcost[j] != 0){
				if(lowcost[j] == -1){
					lowcost[j] = arc[k][j];
					adjvex[j] = k;
				}
				else{
					if(arc[k][j] != -1 && lowcost[j] > arc[k][j]){
						lowcost[j] = arc[k][j];
						adjvex[j] = k;
					}
				}
			}
		}
	}
}

struct EdgeType{
	int from,to;
	int w;
};
int FindRoot(int Parent[],int i)
{
	if(Parent[i] == i)
		return i;
	else{
		int t = FindRoot(Parent,Parent[i]);
		Parent[i] = t;
		return t;
	}
}
bool Comp(EdgeType e1, EdgeType e2)
{
		return e1.w < e2.w;
}
template <class T>
void MGraph<T>::Kruskal()
{
	vector<EdgeType> edges;
	EdgeType edge;
	for(int i = 0; i < vertexNum; ++i)
		for(int j = i+1; j < vertexNum; ++j)
		{
			if(arc[i][j] > 0){
				edge.from = i;
				edge.to = j;
				edge.w = arc[i][j];
				edges.push_back(edge);
			}
		}
	sort(edges.begin(),edges.end(),Comp);
	
	int Parent[MaxSize];
	for(int i = 0; i < vertexNum; ++i)
		Parent[i] = i;
	
	for(int i = 0; i < edges.size(); ++i){
		int v1 = FindRoot(Parent,edges[i].from);
		int v2 = FindRoot(Parent,edges[i].to);
		if(v1 != v2){
			cout << "(" << edges[i].from << "," << edges[i].to << ") " << edges[i].w << endl; 
			Parent[v2] = v1;
		}
	}
}
#endif
