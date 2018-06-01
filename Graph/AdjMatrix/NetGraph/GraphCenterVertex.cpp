/*
			医院选址问题
1.问题描述
	n个村庄之间的交通图可以用有向网来表示，图中边<vi,vj>上的权值表示从村庄i到村庄j
的道路长度。现在要从这n个村庄中选择一个村庄建一所医院，问这所医院应建在哪个村庄，
才能使所有的村庄离医院都比较近？
2.设计思想
	医院选址问题实际上是求有向图的中心点。首先定义顶点的偏心度。
	设图G=（V，E），对任一顶点k，称E(k) = max{dist<i,k>}(i@V(@表属于),dist<i,k>为顶点
i到顶点k的代价)为顶点k的偏心度。显然，偏心度最小的顶点即为图G的中心点。 
*/
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>

using namespace std;

const int MaxSize = 10;

template <class T>
class MGraph{
	public:
		MGraph(T a[], int n, string fpath);	//构造函数，建立一个n个顶点的图 
		~MGraph(){}						//析构函数为空 
		void Floyd(int dist[][MaxSize],int n); 
		T CenterVertex();
	private:
		T vertex[MaxSize];				//图的顶点数组 
		int arc[MaxSize][MaxSize];		//邻接矩阵 
		int vertexNum;					//顶点数 
		int arcNum;						//边数 
};

template <class T>
MGraph<T>::MGraph(T a[], int n, string fpath)
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
	ifstream fgraph(fpath,ifstream::in);
	string line;
	while(getline(fgraph,line)){
		stringstream liness(line);
		int i,j,w;
		liness >> i >> j >> w;
		arc[i][j] = w;
		++e;
	}		
	arcNum = e;
} 

template <class T>
void MGraph<T>::Floyd(int dist[][MaxSize], int n)
{
	//初始化 
	for(int i = 0; i < vertexNum; ++i)
		for(int j = 0; j < vertexNum; ++j)
		{
			dist[i][j] = arc[i][j];
		}
	//更新dist表 
	for(int k = 0; k < vertexNum; ++k)
		for(int i = 0; i < vertexNum; ++i)
			for(int j = 0; j < vertexNum; ++j){
				if(dist[i][j] != 0 && dist[i][k] != 0 && dist[k][j] != 0){
					if(dist[i][j] == -1){
						if(dist[i][k] != -1 && dist[k][j] != -1){
							dist[i][j] = dist[i][k] + dist[k][j];
						}
					}
					else{
						if(dist[i][k] != -1 && dist[k][j] != -1){
							if(dist[i][j] > dist[i][k] + dist[k][j]){
								dist[i][j] = dist[i][k] + dist[k][j];
							}
						}
					}
				}
			}
}

template <class T>
T MGraph<T>::CenterVertex()
{
	int Ecc[MaxSize];
	int dist[MaxSize][MaxSize];
	Floyd(dist,vertexNum);
	
	for(int j = 0; j < vertexNum; ++j){
		int max = -1;
		for(int i = 0; i < vertexNum; ++i){
			if(dist[i][j] != 0 && dist[i][j] != -1){
				if(max == -1)
					max = dist[i][j];
				else{
					if(max < dist[i][j])
						max = dist[i][j];
				}
			}
		}
		Ecc[j] = max;
	}
	
	int r = -1;
	int min;
	for(int i = 0; i < vertexNum; ++i){
		if(Ecc[i] != -1){
			if(r == -1){
				min = Ecc[i];
				r = i;
			}
			else{
				if(min > Ecc[i]){
					min = Ecc[i];
					r = i;
				}
			}
		}
	}
	
	return vertex[r];
}

int main()
{
	string fpath = "F:\\c++ project\\VillagesNetGraph.txt";
	char ch[] = {'a','b','c','d','e'};
	MGraph<char> g(ch,5,fpath);
	cout << "医院应建在：";
	cout << g.CenterVertex() << "村庄" << endl;	
	return 0;
}


