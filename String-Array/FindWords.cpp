/*
    “找词”游戏是在美国流行的一种游戏，它要求游戏者从一张填满字母的正方形表中，找出包含在一个给定集合中的所有词。
这些词可以竖着读（向上或向下）、横着读（从左或从右），或者沿45度对角线斜着读（4个方向都可以），但这些词必须是由表格中邻接的连续的单元格组成。
遇到表格的边界时可以环绕，但方向不得改变，也不能折来折去。表格中的同一单元格可以出现在不同的词中，但在任一词中，同一单元格不得出现一次以上。
以下是一具体游戏事例，可以结合这个实例为该游戏设计一个蛮力算法。
*/
#include<iostream>
#include<string>
#include<cmath>
#include<algorithm>
#include<vector>

#define ROW 16
#define COL 14
#define SIZE 13

using namespace std;

char T[ROW][COL+1] = {
	"DHOBSHNEPTUNEY",
	"UEJIHUNYSTHAOR",
	"DNAUUEEEMAENWA",
	"WNAIPLUTONAODH",
	"AGHPLIZOOERUSU",
	"RDEIHCTMNWTNSH",
	"FHYHOPBEOQHIUE",
	"RACOEAARRTEOAE",
	"USATURNCPLANET",
	"RTAEHFTUEULEEE",
	"IEUCUFAROVCEIO",
	"ARFAIRAYAOEIRH",
	"TOAINIABEARNAE",
	"OIATEOENAAEHUA",
	"EDIDDOEDUTSETS",
	"ESZEEHOPHSLUMS"
};
string words[SIZE] = {"VENUS","EARTH","MARS","CERES",
					"ASTEROIDS","JUPITER","SATURN",
					"NEPTUNE","URANUS","PLUTO",
					"DWARF","PLANET","MOON"};
int mov[8][2] = {
	0,1,
	1,1,
	1,0,
	1,-1,
	0,-1,
	-1,-1,
	-1,0,
	-1,1
};
/*ROW>=COL的情况下（i，j）处主对角线的元素个数*/
int RC(int i, int j)
{
	if(i - j < 0)
		return ROW-abs(i-j)-abs(ROW-COL);
	else if(i - j >= 0 && i - j < abs(ROW-COL))
		return ROW - abs(ROW-COL);
	else if(i - j >= abs(ROW-COL) && i - j < ROW)
		return ROW - abs(i - j);
	else
		return 0;
}
/*（i，j）处主对角线的元素个数*/
int MaxPrimX(int i, int j)
{
	if(ROW >= COL)
		return RC(i,j);
	else
		return RC(j,i);
}
/*（i，j）处副对角线的元素个数*/
int MaxViceX(int i, int j)
{
	if(ROW >= COL)
		return RC(ROW-i-1,j);
	else
		return RC(j,COL-i-1);
}
int M(int i, int j, int m)
{
	if(m == 0 || m == 4)
		return COL;
	else if(m == 2 || m == 6)
		return ROW;
	else if(m == 1 || m == 5)
		return MaxPrimX(i,j);
	else if(m == 3 || m == 7)
		return MaxViceX(i,j);
	else
		return -1;
}
void GetWords(int x,int y,int n,vector<string>& vs)
{
	string s;
	char * chs = new char[n+1];		
	chs[0] = T[x][y];

	for(int i = 0; i < 8; ++i){
		int m = M(x,y,i);
		if(m < n){
			vs.push_back("");
			continue;
		}
		int tx = x;
		int ty = y;
		for(int j = 1; j < n; ++j){
			if (i == 0 || i == 2 || i == 4 || i == 6) {
				tx = (tx + mov[i][0] + m) % m;
				ty = (ty + mov[i][1] + m) % m;
			}
			else {
				tx = tx + mov[i][0];
				ty = ty + mov[i][1];
				if (tx<0 || tx>ROW || ty<0 || ty>COL) {
					tx = tx + mov[i][0] * m;
					ty = ty + mov[i][1] * m;
				}
			}
			chs[j] = T[tx][ty];		
		}
		chs[n] = '\0';
		s = chs;
		vs.push_back(s);
	}
}
int main()
{
	for(int k = 0; k < SIZE; ++k){
		for(int i = 0; i < ROW; ++i){
			for(int j = 0; j < COL; ++j){
				if(words[k][0] == T[i][j]){
					vector<string> vs;
					GetWords(i,j,words[k].size(),vs);
					for(int l = 0; l < vs.size(); ++l){
						if(words[k] == vs.at(l)){
							cout << words[k] << " (" << i << "," << j << ") " << l << endl;
						}
					}
				}
			}
		}
	}	
	return 0;
}
