//集合的基本运算实现
#include<iostream>

using namespace std;

typedef struct node{
	int data;
	struct node * next;
}Node;

bool IsEqual(Node * A,Node * B)
{
	Node * pa = A->next;
	Node * pb = B->next;
	while(pa != NULL && pb != NULL){
		if(pa->data == pb->data){
			pa = pa->next;
			pb = pb->next;
		}
		else
			break;
	}
	if(pa==NULL && pb==NULL)
		return true;
	else
		return false;
}
void Intersection(Node * A,Node * B)
{
	Node * pre = A;
	Node * p = A->next;
	Node * q = B->next;
	while(p!=NULL && q!=NULL){
		if(p->data < q->data){
			pre->next = p->next;
			delete(p);
			p = pre->next;
		}
		else if(p->data > q->data){
			q = q->next;
		}
		else{
			pre = pre->next;
			p = p->next;
			q = q->next;
		}
	}
	if(p != NULL){
		p = NULL;
	}
}
void Union(Node * A,Node * B)
{
	Node * apre = A;
	Node * p = A->next;
	Node * bpre = B;
	Node * q = B->next;
	while(p!=NULL && q!=NULL){
		if(q->data < p->data){
			bpre = q->next;
			q->next = p;
			apre->next = q;
			q = bpre->next;
			apre = apre->next;
		}
		else if(q->data > p->data){
			p = p->next;
			apre = apre->next;
		}
		else{
			p=p->next;
			apre = apre->next;
			q=q->next;
			bpre = bpre->next;
		}
	}
	if(q!=NULL){
		apre->next = bpre->next;
	}
}
void Diff(Node * A,Node * B)
{
	Node * pre = A;
	Node * p = A->next;
	Node * q = B->next;
	while(p!=NULL && q!=NULL){
		if(p->data < q->data){
			p = p->next;
			pre = pre->next;
		}
		else if(p->data > q->data){
			q = q->next;
		}
		else{
			pre->next = p->next;
			delete(p);
			p = pre->next;
		}
	}
}
int main()
{
	Node * A = new Node;
	Node * p = A;
	Node * B = new Node;
	Node * q = B;
	for(int i = 1;i <= 9;++i){
		Node * t = new Node;
		t->data = i;
		t->next = NULL;
		p->next = t;
		p = p->next;
	}
	for(int i=2;i < 19;i+=2){
		Node * t = new Node;
		t->data = i;
		t->next = NULL;
		q->next = t;
		q = q->next;
	}
	
	cout << IsEqual(A,B) << endl;
//	Intersection(A,B);
//	Union(A,B);
	Diff(A,B);
	p = A->next;
	while(p!=NULL){
		cout << p->data << " ";
		p = p->next;
	}
	cout << endl;
	
	//释放内存
	while(A!=NULL){
		p = A;
		A = A->next;
		delete(p);
	} 
	while(B!=NULL){
		q = B;
		B = B->next;
		delete(q);
	}
	return 0;
} 
