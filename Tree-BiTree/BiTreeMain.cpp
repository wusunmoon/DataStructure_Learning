#include<iostream>
#include"BiTree.hpp"

using namespace std;

int main()
{
	BiTree<char> ct;
	
	cout << "前序遍历（递归）：";
	ct.PreOrder();
	cout << endl;
	cout << "前序遍历（迭代）：";
	ct.PreOrderNonrecursion();
	cout << endl;
	cout << endl;

	cout << "中序遍历（递归）："; 
	ct.InOrder();
	cout << endl;
	cout << "中序遍历（迭代）：";
	ct.InOrderNonrecursion();
	cout << endl;
	cout << endl;

	cout << "后序遍历（递归）："; 
	ct.PostOrder();
	cout << endl;
	cout << "后序遍历（迭代）：";
	ct.PostOrderNonrecursion();
	cout << endl;
	cout << "后序遍历逆序（递归）："; 
	ct.RePostOrder(); 
	cout << endl;
	cout << "后序遍历逆序（迭代）：";
	ct.RePostOrderNonrecursion();
	cout << endl;
	cout << endl; 

	cout << "层序遍历："; 
	ct.LevelOrder();
	cout << endl;
	cout << endl;
	
	cout << "该二叉树是否是完全二叉树：" << (ct.IsCompleteBiTree()?"是":"否")<< endl;
	cout << endl;
	 
	int n = 0;
	ct.NodeNum(n);
	cout << "节点数：" << n << endl;
	cout << endl;
	
	cout << "深度：" << ct.Depth() << endl;
	cout << endl;
	
	char ch;
	cin >> ch;
	cout << ch << "的父节点：" << ct.Parent(ch)->data << endl;
	cout << endl;
	
	cin >> ch;
	cout << ch << "路径为："; 
	ct.Path(ch);
	cout << endl;
	cout << endl;

	cout << "该二叉树中叶子结点的个数：(递归)" << ct.CountLeaf() << endl;
	cout << endl;
	cout << "该二叉树中叶子结点的个数：(迭代)" << ct.CountLeafNonrecursion() << endl;
	cout << endl;

	cin >> ch;
	cout << "删除" << ch << "子树：";
	ct.DelSubTree(ch);
	ct.LevelOrder();  
	cout << endl;
	cout << endl;
	
	
	return 0;
}
/*
输入示例：
AB#D##C##
树结构：
		A
              B   C
	       D
*/
