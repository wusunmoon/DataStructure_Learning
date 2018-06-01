/*
			农夫过河问题
1.问题描述
	一个农夫带一只狼、一颗白菜和一只山羊要从一条河的南岸过到北岸，农夫每次只能
带一样东西过河，但是任意时刻如果农夫不在场时，狼要吃羊、羊要吃菜，请为农夫设计过河方案。
2.分析
用0，1分别表示在南岸，北岸
则用四位二进制数顺序表示农夫，狼，白菜和羊的位置（0000~1111）

结果应为							  				  
	  						
				11 - 2   
			  /			\ 
	0 - 9 - 1 			 14 - 6 - 15 
			  \ 		/
			    13 - 4  
注：结果应有两种方案，但程序只能输出一种，暂时没想到如何同时弄出两种	
*/ 

#include<iostream>
#include<queue>
#include<vector>

using namespace std;

const int Size = 16;
struct ArcNode{
	int adjvex;
	ArcNode * next;
};
struct VertexNode{
	int vertex;
	ArcNode * firstedge;
};
VertexNode adjlist[Size];
void InitAdjList();

int main()
{
	//邻接表初始化 
	InitAdjList();
	//广度优先遍历	
	vector<int> Path(Size,-1);//Path[i]的值为顶点i的上一个遍历顶点 
	bool visited[Size] = {0}; 
	queue<int> Q;
	Q.push(0);
	visited[0] = 1;
	while(!Q.empty() && Path[Size-1] == -1){
		int v = Q.front();
		Q.pop();
		ArcNode * pt = adjlist[v].firstedge;
		while(pt != NULL){
			int j = pt->adjvex;
			if(visited[j] == 0){
				Q.push(j);
				visited[j] = 1;
				Path[j] = v;
			}
			pt = pt->next; 
		}
	}
	
	if(Path[Size-1] == -1){
		cout << "没找到可行方案。" << endl;
		return 0;
	}
	//调整结果 
	vector<int> vPath;
	int i = Size -1;
	while(i != -1){
		vPath.push_back(i);
		i = Path[i];
	}
	//输出结果 
	for(int i = vPath.size()-1; i > 0 ; --i){
		int j = i-1;
		string str = "";
		switch(vPath[i] & 8){
			case 0:
				str += "农夫从南岸到北岸 ";
				break;
			case 8:
				str += "农夫从北岸到南岸 "; 
				break;
		}
		switch(vPath[i] ^ vPath[j]){
			case 8:
				break;
			case 9:
				str += "带着羊";
				break;
			case 10:
				str += "带着白菜";
				break;
			case 12:
				str += "带着狼";
				break;
		}
		cout << str << endl;
	}
	return 0;
}

void InitAdjList()
{
	for(int i = 0; i < Size; ++i){
		adjlist[i].vertex = i;
		adjlist[i].firstedge = NULL;
		if(i == 3 || i == 5 || i == 7 || i == 8 
			|| i == 10 || i == 12)
			continue;
		for(int j = 0; j < Size; ++j){
			if(j == 3 || j == 5 || j == 7 || j == 8 
				|| j == 10 || j == 12)
				continue;
			if((i ^ 8) == j || (i ^ 9) == j || (i ^ 10) == j || (i ^ 12) == j){
				ArcNode * p = new ArcNode{j,adjlist[i].firstedge};
				adjlist[i].firstedge = p;
			}			
		}
	}
}



