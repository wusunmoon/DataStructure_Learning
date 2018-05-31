#include"DirGraphNoRing.hpp"

int main()
{
	string s[] = {"v0","v1","v2","v3","v4","v5","v6"};
	ALGraph<string> g(s,7);
//	cout << (g.TopSort()?"无回路":"有回路") << endl; 
	cout << (g.TopSortPlus()?"无回路":"有回路") << endl; 

	return 0;
}
