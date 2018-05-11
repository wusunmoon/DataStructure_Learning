//将一个具有n个元素的数组向左移动i个位置

#include <iostream>

using namespace std; 

void Reverse(int A[],int n)
{
	int i=0;
	int j=n-1;
	while(i<j){
		int t = A[i];
		A[i]=A[j];
		A[j]=t;
		++i;
		--j;
	}
} 
int main()
{
	int A[5]={1,2,3,4,5};
	
	Reverse(A,5);
	for(int i=0;i<5;++i)
		cout<<A[i]<<" ";
	
	cout<<endl;
	return 0;
}
