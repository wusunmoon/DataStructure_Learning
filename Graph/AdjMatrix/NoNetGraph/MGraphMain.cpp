#include"MGraph.hpp"

int main()
{
	char ch[] = {'A','B','C','D','E'};
	string fpath = "F:\\c++ project\\Graph.txt";
	MGraph<char> g(ch,5,fpath);
	cout << "深度优先遍历：";
	g.DFSTraverse(0);
	cout << endl;
	cout << "广度优先遍历：";
	g.BFSTraverse(0);
	cout << endl;

	cout << endl << (g.BeEulerRing()?"存在":"不存在") << "欧拉回路" << endl; 
	cout << endl;

	cout << "七巧板涂色问题求解：(4色)" << endl;
	char ch1[] = { 'A','B','C','D','E' ,'F','G' };
	fpath = "F:\\c++ project\\TangramGraph.txt";
	MGraph<char> g1(ch1, 7, fpath);
	g1.TangramColor();
	cout << endl;
	
	cout << "哈密顿路径：" << endl;
	string str[] = {"v1","v2","v3","v4"};
	fpath = "F:\\c++ project\\HaGraph.txt";w
	MGraph<string> g2(str,4,fpath);	
	g2.HamiltonPath(); 
	
	return 0;
}
