#include"ALGraph.hpp"

int main()
{
	string fpath = "F:\\c++ project\\Graph.txt";
	char ch[] = {'A','B','C','D','E'};
	ALGraph<char> g(ch,5,fpath);
	cout << "深度优先遍历：（递归）" ;
	g.DFSTraverse(0);
	cout << endl;
	cout << "广度优先遍历：";
	g.BFSTraverse(0);
	cout << endl;
	cout << "深度优先遍历：（非递归）"; 
	g.DFSTNorecursion(0); 
	cout << endl;
	cout << endl;
	cout << "指向A的顶点：" << endl; 
	g.InVertex(0);
	cout << endl;
	cout << "基于深度优先遍历算法：" << endl; 
	cout << "B到D" << (g.DFSTBePath(1,3)?"存在":"不存在") << "路径" << endl; 
	cout << "A到D" << (g.DFSTBePath(0,3)?"存在":"不存在") << "路径" << endl; 
	cout << "基于广度优先遍历算法：" << endl; 
	cout << "B到D" << (g.BFSTBePath(1,3)?"存在":"不存在") << "路径" << endl; 
	cout << "A到D" << (g.BFSTBePath(0,3)?"存在":"不存在") << "路径" << endl; 
	cout << endl;

	fpath = "F:\\c++ project\\DirGraph1.txt";
	string str[] = {"v1","v2","v3","v4"};
	ALGraph<string> g1(str,4,fpath);
	g1.Kosaraju();
	return 0;
}
