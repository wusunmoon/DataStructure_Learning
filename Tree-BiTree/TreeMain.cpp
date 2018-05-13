#include<iostream>
#include"Tree.hpp"

using namespace std;

int main()
{
	Tree<char> t1;
	t1.PreOrder();
	cout << endl;
	t1.PostOrder();
	cout << endl;
	
	return 0;
}
/*
输入示例：
A
A B
A C
B D
B E
B F
C G
C H
E I

树结构为

                                      A
                                  B        C
                                D E F     G H
                                  I
*/
