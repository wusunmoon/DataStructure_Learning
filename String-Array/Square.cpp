//n阶幻方求解
#include<iostream>

using namespace std;

void OddSquare(int **a,int n);
void DEvenSquare(int **a,int n);
void SEvenSquare(int **a,int n); 

int main()
{
	int n;
	cout << "请输入幻方阶数：";
	while(cin >> n){
		//分配n个int*内存+n*n个int内存 
		int **a = new int*[n];
		for(int i = 0; i < n; ++i){
			a[i] = new int[n]();
		} 
		
		switch(n%4){
			case 0:
				DEvenSquare(a,n);
				break;
			case 1:
			case 3:
				OddSquare(a,n);
				break;
			case 2:
				SEvenSquare(a,n);
				break;	
		}	
		
		int *colSum = new int[n+1]();
		int rowSum; 
		for(int i = 0; i < n; ++i){
			rowSum = 0;
			for(int j = 0; j < n; ++j)
			{
				rowSum += a[i][j];
				cout << a[i][j] << " ";
				colSum[j] += a[i][j];
				if(i == j)
					colSum[n] += a[i][j];
			}
			cout << " "; 
			cout << rowSum;
			cout << endl;
		}
		cout << endl;
		for(int i = 0; i < n+1; ++i)
			cout << colSum[i] << " ";
		cout << endl;
		//释放n*n个int内存+n个int*内存 
		for(int i = 0; i < n; ++i){
			delete []a[i]; 
		} 
		delete []a;
		delete []colSum;
	  cout << "请输入幻方阶数：";
	}
	return 0;
}
//单偶阶幻方n=4k+2
void SEvenSquare(int **a,int n)
{
	int k = n/2;
	int row = 0;
	int col = k/2;
	for(int i = 1; i <= k*k; ++i){
		a[row][col] = i;
		a[row][col+k] = i + 2*k*k;
		a[row+k][col] = i + 3*k*k;
		a[row+k][col+k] = i + k*k;
		int rowt = row;
		int colt = col;		
		row = (row - 1 + k) % k;
		col = (col - 1 + k) % k;
		if(a[row][col] > 0){
			row = (rowt + 1) % k;
			col = colt;
		}
	}
	
	int m = k/2;
	int t = (n - 2) / 4;
	for(int i = 0; i < k; ++i){
		int j;
		if(i == m){//等于中间行 
			for(j = m; j < m+t; ++j){
				int temp = a[i][j];
				a[i][j] = a[i+k][j];
				a[i+k][j] = temp;
			}
			for(j = m+k; j >m+k-t+1; --j){
				int temp = a[i][j];
				a[i][j] = a[i+k][j];
				a[i+k][j] = temp;				
			}
		}
		else{
			for(j = 0; j < t; ++j){
				int temp = a[i][j];
				a[i][j] = a[i+k][j];
				a[i+k][j] = temp;
			}
			for(j = m+k; j >m+k-t+1; --j){
				int temp = a[i][j];
				a[i][j] = a[i+k][j];
				a[i+k][j] = temp;				
			}			
		}
	}
} 
//双偶阶幻方 n=4k
void DEvenSquare(int **a,int n)
{
	int k = 1;
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
		{
			if(i%4 == j%4 || i%4+j%4==3)
				a[i][j] = n*n + 1 - k++;//置为互补数 
			else
				a[i][j] = k++;	
		}	
}
//奇数阶幻方 
void OddSquare(int **a,int n)
{
	int row = 0;
	int col = n/2;
	for(int i = 1; i <= n*n; ++i){
		a[row][col] = i;
		int rowt = row;
		int colt = col;		
		row = (row - 1 + n) % n;
		col = (col - 1 + n) % n;
		if(a[row][col] > 0){
			row = (rowt + 1) % n;
			col = colt;
		}
	}
}
