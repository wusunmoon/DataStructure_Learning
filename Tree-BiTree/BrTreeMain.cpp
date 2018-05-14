#include<iostream>
#include"BrTree.hpp"

using namespace std;

int main()
{
	BrTree bt;

	cout << "前序遍历：";
	bt.PreOrder();
	cout << endl;
	
	cout << "中序遍历：";
	bt.InOrder();
	cout << endl;	

	cout << "后序遍历：";
	bt.PostOrder();
	cout << endl;
	
	return 0;
}
