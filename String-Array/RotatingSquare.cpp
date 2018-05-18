//数字旋转方阵求解

#include<iostream>

using namespace std;

void Full(int **a,int n,int begin=0,int number=1);

int main()
{
	int n;
	cout << "输入阶数："; 
	while(cin >> n){
		int **a = new int*[n];
		for(int i = 0; i < n; ++i)
			a[i] = new int[n];
		
		Full(a,n);
		
		for(int i = 0; i < n; ++i){
			for(int j = 0; j < n; ++j){
				cout << a[i][j] << " ";
			}
			cout << endl;
		}
		for(int i = 0; i < n; ++i)
			delete []a[i];

		cout << "输入阶数："; 
	}
	return 0;
}

void Full(int **a,int n,int begin,int number)
{
	if(n == 0)
		return;
	if(n == 1){
		a[begin][begin] = number;
		return;
	}
	int i = begin, j = begin;
	for(int k = 0; k < n - 1; ++k){
		a[i++][j] = number++;
	}
	for(int k = 0; k < n - 1; ++k){
		a[i][j++] = number++;
	}
	for(int k = 0; k < n - 1; ++k){
		a[i--][j] = number++;
	}
	for(int k = 0; k < n - 1; ++k){
		a[i][j--] = number++;
	}
	Full(a,n-2,begin+1,number);	
}
