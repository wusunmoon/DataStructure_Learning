//汉诺塔问题求解

#include<iostream>

using namespace std;

int num;
void Hanoi(int n, char A,char B,char C)
{
	if(n == 1){
		cout << A << "->" << C << endl;
		++num;
	}
	else{
		Hanoi(n-1,A,C,B);
		cout << A << "->" << C << endl;
		++num;
		Hanoi(n-1,B,A,C);
	}
}
int main()
{
	char A = 'A';
	char B = 'B';
	char C = 'C';
	Hanoi(5,A,B,C);
	cout << num << endl;
	return 0;
}
