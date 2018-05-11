//八皇后问题求解
#include<iostream>

using namespace std;

int c[20];		//皇后摆放数组 
int n = 8;		//皇后数量 
int cnt = 0;	//可行方案数量

void print()
{
	for(int i = 0;i < n;++i){
		for(int j = 0;j < n;++j){
			if(j == c[i])
				cout << "1 ";
			else
				cout << "0 ";
		}
		cout << endl;
	}
	cout << endl;
} 
void EightQueen(int r)
{
	if(r == n){
		print();
		++cnt;
		return;
	}
	
	for(int i = 0; i < n; ++i){
		c[r] = i;
		bool ok = 1;
		for(int j = 0; j < r;++j){
			if(c[r] == c[j] || r - j == c[r] - c[j] || j - r == c[r] - c[j]){
				ok = 0;
				break;
			}
		}
		if(ok)
			EightQueen(r+1);
	}
	
}
int main()
{
	EightQueen(0);
	cout << cnt << endl;
	return 0;
}
