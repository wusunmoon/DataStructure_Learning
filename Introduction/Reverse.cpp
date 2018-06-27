//将一个具有n个元素的数组向左移动i个位置

#include <iostream>
using namespace std; 
void Reverse(int A[],int lo,int hi)
{
	while(lo<hi){
		int t = A[lo];
		A[lo]=A[hi];
		A[hi]=t;
		++lo;
		--hi;
	}
} 
void LeftShift(int A[],int n,int i)
{
	Reverse(A,0,i-1);
	Reverse(A,i,n-1);
	Reverse(A,0,n-1);
}
int main()
{
	int A[5]={1,2,3,4,5};
	
	LeftShift(A,5,2);
	for(int i=0;i<5;++i)
		cout<<A[i]<<" ";
	
	cout<<endl;
	return 0;
}
