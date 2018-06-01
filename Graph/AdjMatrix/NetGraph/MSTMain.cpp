#include"MST.hpp"

int main()
{
	char a[] = {'0','1','2','3','4','5'};
	MGraph<char> g(a,6);
	g.Prim();
	cout << endl;
	g.Kruskal();
	return 0;
}
