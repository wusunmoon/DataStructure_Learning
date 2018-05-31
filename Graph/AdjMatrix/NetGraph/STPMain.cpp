#include"STP.hpp"

int main()
{
	string s[] = {"v0","v1","v2","v3","v4"};
	MGraph<string> g(s,5);
	cout << "Dijkstra算法求解：" << endl;
	g.Dijkstra(0);
	cout << endl;
	
	int dist[5][MaxSize];
	string Path[5][MaxSize];
	g.Floyd(dist,Path,5);
	cout << "Floyd算法求解：" << endl;
	for(int i = 0; i < 5; ++i){
		cout << dist[0][i] << " " << Path[0][i] << endl;
	}
	return 0;
}
