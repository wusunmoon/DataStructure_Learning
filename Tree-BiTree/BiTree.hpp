//二叉树类的模板实现

#include<iostream>
#include<queue>
#include<stack>
#include<algorithm>

using namespace std;

template <class T>
struct BiNode{
	T data;
	BiNode<T> * lchild, * rchild;
};

template <class T>
class BiTree
{
	public:
		BiTree(){root = Creat(root);}
		~BiTree(){Release(root);}
		void PreOrder(){PreOrder(root);}
		void InOrder(){InOrder(root);}
		void PostOrder(){PostOrder(root);}
		void RePostOrder(){RePostOrder(root);}
		void LevelOrder();
		void PreOrderNonrecursion(){PreOrderNonrecursion(root);}
		void InOrderNonrecursion(){InOrderNonrecursion(root);}
		void PostOrderNonrecursion(){PostOrderNonrecursion(root);}
		void RePostOrderNonrecursion(){RePostOrderNonrecursion(root);}
		void NodeNum(int &n){NodeNum(root,n);}
		int Depth(){return Depth(root);};
		BiNode<T> * Parent(T x){return Parent(root,x);}
		void DelSubTree(T x){DelSubTree(root,x);}
		void Path(T p){Path(root,p);}
		bool IsCompleteBiTree(){return IsCompleteBiTree(root);}
		int CountLeaf(){return CountLeaf(root);}
		int CountLeafNonrecursion(){return CountLeafNonrecursion(root);}

	private:
		BiNode<T> * root;
		BiNode<T> * Creat(BiNode<T> * bt);
		void Release(BiNode<T> * bt);
		void PreOrder(BiNode<T> * bt);
		void InOrder(BiNode<T> * bt);
		void PostOrder(BiNode<T> * bt);
		void RePostOrder(BiNode<T> * bt);
		void PreOrderNonrecursion(BiNode<T> * bt);
		void InOrderNonrecursion(BiNode<T> * bt);
		void PostOrderNonrecursion(BiNode<T> * bt); 
		void RePostOrderNonrecursion(BiNode<T> * bt);
		void NodeNum(BiNode<T> * bt, int &n);
		int Depth(BiNode<T> * bt);
		BiNode<T> * Parent(BiNode<T> * bt, T x);
		void DelSubTree(BiNode<T> * bt, T x);
		void Path(BiNode<T> * bt, T p); 
		bool IsCompleteBiTree(BiNode<T> * bt);
		int CountLeaf(BiNode<T> * bt);
		int CountLeafNonrecursion(BiNode<T> * bt);
};

template <class T>
int BiTree<T>::CountLeafNonrecursion(BiNode<T> * bt)
{
	int count = 0;
	if(bt != NULL){
		stack<BiNode<T> *> s;
		s.push(bt);
		BiNode<T> * p;
		while(!s.empty()){
			p = s.top();
			s.pop();
			if(p->lchild == NULL && p->rchild == NULL)
				++count;
			
			if(p->rchild != NULL)
				s.push(p->rchild);
			if(p->lchild != NULL)
				s.push(p->lchild);
			
		} 
	}
	return count;
}
template <class T>
int BiTree<T>::CountLeaf(BiNode<T> * bt)
{
	if(bt != NULL){
		if(bt->lchild == NULL && bt->rchild == NULL)
			return 1;
		else{
			return CountLeaf(bt->lchild) + CountLeaf(bt->rchild);
		}
	}
	else
		return 0;
}

template <class T>
bool BiTree<T>::IsCompleteBiTree(BiNode<T> * bt)
{
	if(bt == NULL)
		return true;
	queue<BiNode<T> *> q;
	q.push(bt);
	BiNode<T> * p;
	while((p = q.front()) != NULL){
		q.push(p->lchild);
		q.push(p->rchild);
		q.pop();
	}
	
	while(!q.empty()){
		p = q.front();
		
		if(p != NULL)
			return false;
		
		q.pop();
	}
	return true;
}
template <class T>
void BiTree<T>::Path(BiNode<T> * bt, T p)
{
	stack<BiNode<T> *> s;
	stack<int> flag;
	while(bt != NULL || !s.empty()){
		while(bt != NULL){
			s.push(bt);
			flag.push(1);
			bt = bt->lchild;
		}
		
		while(!s.empty() && flag.top() == 2){
			if(s.top()->data == p){
				while(!s.empty()){
					cout << s.top()->data;
					s.pop();
				}
				return;
			}
			s.pop();
		}
		if(!s.empty()){
			flag.pop();
			flag.push(2);
			bt = s.top()->rchild;
		}
	}
	
}
template <class T>
void BiTree<T>::DelSubTree(BiNode<T> * bt, T x)
{
	if(bt != NULL){
		BiNode<T> * p = Parent(bt,x);
		if(p){
			if(p->lchild != NULL && p->lchild->data == x){
				Release(p->lchild);
				p->lchild = NULL;
			}
			if(p->rchild != NULL && p->rchild->data == x){
				Release(p->rchild); 
				p->rchild = NULL;
			}	
		}
		else{
			Release(bt);
		}
	}
}
template <class T>
BiNode<T> * BiTree<T>::Parent(BiNode<T> * bt, T x)
{
	if(bt != NULL){
		if(bt->data == x)
			return NULL;
		
		if((bt->lchild != NULL && bt->lchild->data == x)|| 
			(bt->rchild != NULL && bt->rchild->data == x))
			return bt;
		else{
			BiNode<T> * p = NULL;
			if(p = Parent(bt->lchild,x))
				return p;
			if(p = Parent(bt->rchild,x))
				return p;
		} 
		
		return NULL;
	}
	return NULL;
}
template <class T>
void BiTree<T>::RePostOrderNonrecursion(BiNode<T> * bt)
{
	if(bt != NULL){
		stack<BiNode<T>*> s;
		s.push(bt);
		while(!s.empty()){
			bt = s.top();
			s.pop();
			cout << bt->data;
			if(bt->lchild != NULL)
				s.push(bt->lchild);
			if(bt->rchild != NULL)
				s.push(bt->rchild);
		}
	}
}
template <class T>
void BiTree<T>::RePostOrder(BiNode<T> * bt)
{
	if(bt != NULL){
		cout << bt->data;
		RePostOrder(bt->rchild);
		RePostOrder(bt->lchild);
	}
}

template <class T>
int BiTree<T>::Depth(BiNode<T> * bt)
{
	if(bt == NULL)
		return 0;
	else{
		int lh = Depth(bt->lchild);
		int rh = Depth(bt->rchild);
		return max(lh,rh)+1;
	}
}
template <class T>
void BiTree<T>::NodeNum(BiNode<T> * bt, int &n)
{
	if(bt != NULL){
		NodeNum(bt->lchild,n);
		++n;
		NodeNum(bt->rchild,n);
	}
}
template <class T>
void BiTree<T>::PostOrderNonrecursion(BiNode<T> * bt)
{
	if(bt != NULL){
		stack<BiNode<T> *> s1;
		stack<BiNode<T> *> s2;
		s1.push(bt);
		BiNode<T> * p;
		while(!s1.empty()){
			p = s1.top();
			s1.pop();
			s2.push(p);
			if(p->lchild != NULL){
				s1.push(p->lchild);
			}
			if(p->rchild != NULL){
				s1.push(p->rchild);
			}
		}
		
		while(!s2.empty()){
			p = s2.top();
			s2.pop();
			cout << p->data;
		}
	}
}
template <class T>
void BiTree<T>::InOrderNonrecursion(BiNode<T> * bt)
{
	if(bt != NULL){
		stack<BiNode<T> *> s;
		while(bt != NULL || !s.empty()){
			while(bt != NULL){
				s.push(bt);
				bt = bt->lchild;
			}
			if(!s.empty()){
				bt = s.top();
				s.pop();
				cout << bt->data;
				bt = bt->rchild;
			}
		}
	}
}
template <class T>
void BiTree<T>::PreOrderNonrecursion(BiNode<T> * bt)
{
	if(bt != NULL){
		stack<BiNode<T> *> s;
		BiNode<T> * p;
		s.push(bt);
		while(!s.empty()){
			p = s.top();
			s.pop();
			
			cout << p->data;
			
			if(p->rchild != NULL){
				s.push(p->rchild);
			}
			if(p->lchild != NULL){
				s.push(p->lchild);
			}
		}
	}
}
template <class T>
BiNode<T> * BiTree<T>::Creat(BiNode<T> * bt)
{
	T ch;
	cin >> ch;
	if(ch == '#')
		bt = NULL;
	else{
		bt = new BiNode<T>;
		bt->data = ch;
		bt->lchild = Creat(bt->lchild);
		bt->rchild = Creat(bt->rchild);
	}
	return bt;
}

template <class T>
void BiTree<T>::Release(BiNode<T> * bt)
{
	if(bt != NULL){
		Release(bt->lchild);
		Release(bt->rchild);
		delete bt;
	}
}

template <class T>
void BiTree<T>::PreOrder(BiNode<T> * bt)
{
	if(bt != NULL){
		cout << bt->data;
		PreOrder(bt->lchild);
		PreOrder(bt->rchild);
	}
}

template <class T>
void BiTree<T>::InOrder(BiNode<T> * bt)
{
	if(bt != NULL){
		InOrder(bt->lchild);
		cout << bt->data;
		InOrder(bt->rchild);
	}
}

template <class T>
void BiTree<T>::PostOrder(BiNode<T> * bt)
{
	if(bt != NULL){
		PostOrder(bt->lchild);
		PostOrder(bt->rchild);
		cout << bt->data;
	}
}

template <class T>
void BiTree<T>::LevelOrder()
{
	queue<BiNode<T> *> Q;
	if(root == NULL)
		return;
	Q.push(root);
	while(!Q.empty()){
		BiNode<T> * q = Q.front();
		Q.pop();
		cout << q->data;
		if(q->lchild != NULL)
			Q.push(q->lchild);
		if(q->rchild != NULL)
			Q.push(q->rchild);
	}
}
