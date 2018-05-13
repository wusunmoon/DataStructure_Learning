//树的模板实现
#ifndef TREE_HPP
#define TREE_HPP

#include<iostream>
#include<cstdio>

using namespace std;

const int Max = 20;

//孩子兄弟表示法
template <class T>
struct TNode{
	T data;
	TNode<T> * firstchild, * rightsib;
};

template <class T>
class Tree{
	public:
		Tree();
		~Tree(){Release(root);}
		void PreOrder(){PreOrder(root);}
		void PostOrder(){PostOrder(root);}
		
	private:
		TNode<T> * root;
		void Release(TNode<T> * bt);
		void PreOrder(TNode<T> * bt);
		void PostOrder(TNode<T> * bt);
};

template <class T>
Tree<T>::Tree()
{
	TNode<T> * Q[Max] = {NULL};
	int front = -1, rear = -1;
	
	T ch1 = '#', ch2 = '#';
	TNode<T> * p = NULL, * q = NULL;
	cout << "请输入根结点：";
	cin >> ch1;
	p = new TNode<T>;p->data= ch1;
	p->firstchild = p->rightsib = NULL;
	root = p;
	Q[++rear] = p;
	cout << "请输入结点对，以空格分隔：";
	fflush(stdin);
	ch1 = getchar(); getchar(); ch2 = getchar();
	while(ch1 != '#' || ch2 != '#'){
		p = new TNode<T>; p->data = ch2;
		p->firstchild = p->rightsib = NULL;
		Q[++rear] = p;
		while(front != rear){
			q = Q[front + 1];
			if(q->data != ch1)
				++front;
			else{
				if(q->firstchild == NULL)
					q->firstchild = p;
				else{
					q = q->firstchild;
					while(q->rightsib != NULL)
						q = q->rightsib;
					q->rightsib = p;
				}
				break;
			}
		}
		cout << "请输入结点对，以空格分隔：";
		fflush(stdin);
		ch1 = getchar(); getchar(); ch2 = getchar();
	} 
}

template <class T>
void Tree<T>::Release(TNode<T> * bt)
{
	if(bt != NULL){
		Release(bt->firstchild);
		Release(bt->rightsib);
		delete bt;
	}
}

template <class T>
void Tree<T>::PreOrder(TNode<T> * bt)
{
	if(bt != NULL){
		cout << bt->data;
		PreOrder(bt->firstchild);
		PreOrder(bt->rightsib);
	}
}

template <class T>
void Tree<T>::PostOrder(TNode<T> * bt)
{
	if(bt != NULL){
		PostOrder(bt->firstchild);
		if(bt->firstchild != NULL){
			TNode<T> * p = bt->firstchild;
			while(p->rightsib != NULL){
				PostOrder(p->rightsib);
				p = p->rightsib;
			}
		}
		cout << bt->data;
	}
}
#endif
