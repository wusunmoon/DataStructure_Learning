//中序线索二叉树类的模板实现

#include<iostream>

using namespace std;

enum flag{Child,Thread};

template <class T>
struct ThrNode{
	T data;
	ThrNode<T> * lchild, * rchild;
	flag ltag,rtag;
};

template <class T>
class InThrBiTree{
	public:
		InThrBiTree();
		~InThrBiTree();
		ThrNode<T> * First(ThrNode<T> * p);
		ThrNode<T> * Next(ThrNode<T> * p);
		void InOrder();
	private:
		ThrNode<T> * root;
		ThrNode<T> * Creat(ThrNode<T> * bt);
		void ThrBiTree(ThrNode<T> * bt,ThrNode<T> * &pre);
		void Release(ThrNode<T> * bt);
};

template <class T>
InThrBiTree<T>::InThrBiTree()
{
	root = Creat(root);
	ThrNode<T> * pre = NULL;
	ThrBiTree(root,pre);
}
template <class T>
InThrBiTree<T>::~InThrBiTree()
{
	if(root != NULL){
		Release(root);
	}
}

template <class T>
void InThrBiTree<T>::Release(ThrNode<T> * bt)
{
	if(bt->ltag == Child) 
		Release(bt->lchild);
	if(bt->rtag == Child)
		Release(bt->rchild);
		
	delete bt;
	return;
}

template <class T>
void InThrBiTree<T>::InOrder()
{
	for(ThrNode<T> * p = First(root); p != NULL; p = Next(p))
		cout << p->data;
}
template <class T>
ThrNode<T> * InThrBiTree<T>::Next(ThrNode<T> * p)
{
	if(p->rtag == 1)
		return p->rchild;
	else{
		return First(p->rchild);
	}
}
template <class T>
ThrNode<T> * InThrBiTree<T>::First(ThrNode<T> * p)
{
	while(p->ltag == Child){
		p = p->lchild;
	}
	return p;
}

template <class T>
ThrNode<T> * InThrBiTree<T>::Creat(ThrNode<T> * bt)
{
	T ch;
	cin >> ch;
	if(ch == '#')
		bt = NULL;
	else{
		bt = new ThrNode<T>;
		bt->data = ch;
		bt->ltag = Child;
		bt->rtag = Child;
		bt->lchild = Creat(bt->lchild);
		bt->rchild = Creat(bt->rchild);
	}
	return bt;
}

template <class T>
void InThrBiTree<T>::ThrBiTree(ThrNode<T> * bt,ThrNode<T> * &pre)
{
	if(bt != NULL){
		ThrBiTree(bt->lchild,pre);
		if(bt->lchild == NULL){
			bt->lchild = pre;
			bt->ltag = Thread;
		}
		if(bt->rchild == NULL){
			bt->rtag = Thread;
		}
		if(pre != NULL && pre->rtag == Thread){
			pre->rchild = bt; 
		}
		pre = bt;
		ThrBiTree(bt->rchild,pre);
	}
}

