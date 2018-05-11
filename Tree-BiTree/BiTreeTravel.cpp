//由前序遍历和中序遍历----》后序遍历
#include<iostream>
#include<string>
using namespace std;

typedef struct tnode{
	char data;
	struct tnode * lChild,* rChild;
}TNode;
TNode tree[30];int loc;
TNode * Creat()
{
	tree[loc].lChild = NULL;
	tree[loc].rChild = NULL;
	return &tree[loc++];
}

string preStr;
string inStr;

TNode * ReBuild(int pres, int pree, int ins, int ine);
void PostOrder(TNode * p);

int main()
{
	while(cin >> preStr){
		cin >> inStr;
		TNode * root = ReBuild(0,preStr.size()-1,0,inStr.size()-1);
		PostOrder(root);
		cout << endl;
	}
	return 0;	
}
void PostOrder(TNode * p)
{
	if(p != NULL){
		PostOrder(p->lChild);
		PostOrder(p->rChild);
		cout << p->data;
	}
}
TNode * ReBuild(int pres, int pree, int ins, int ine)
{
	TNode * root = Creat();
	root->data = preStr[pres];
	
	int i = ins;
	while(inStr[i] != preStr[pres]){
		++i;
	}
	
	if(i != ins){
		root->lChild = ReBuild(pres+1,pres+(i-ins),ins,i-1);
	}
	if(i != ine){
		root->rChild = ReBuild(pres+(i-ins)+1,pree,i+1,ine);
	}
	
	return root;
}
