#include"TSP.hpp"

int main()
{
	char ch[5] = {'1','2','3','4','5'};
	MGraph<char> g(ch,5);
	g.GreedyAlg(0);
	return 0;
}
