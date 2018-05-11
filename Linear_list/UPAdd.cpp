//一元多项式求和问题
#include<iostream>

using namespace std;

typedef struct node{
	int coef;           //系数
	int exp;            //指数
	struct node * next; 
}Node;

void UPAdd(Node * A,Node * B)
{
	Node * apre = A;
	Node * p = A->next;
	Node * bpre = B;
	Node * q = B->next;
	while(p!=NULL && q!=NULL){
		if(p->exp < q->exp){
			p = p->next;
			apre = apre->next;
		}
		else if(p->exp > q->exp){
			bpre->next = q->next;
			q->next = p;
			apre->next = q;
			apre = apre->next;
			q = bpre->next;
		}
		else{
			p->coef += q->coef;
			if(p->coef == 0){
				apre->next = p->next;
				delete(p);
				p = apre->next;
			}
			else{
				apre = apre->next;
				p = p->next;
			}
			q = q->next;
		}
	}
	if(q!=NULL){
		apre->next = bpre->next;
	}
}
int main()
{
	Node * A = new Node;
	Node * B = new Node;
	Node * p = A;
	Node * q = B;
	for(int i = 0;i < 4;++i){
		Node * t = new Node;
		t->coef = 1;
		t->exp = i;
		t->next = NULL;
		p->next = t;
		p = p->next;
	}
	Node * u = new Node;
	u->coef = 1;
	u->exp = 6;
	u->next = NULL;
	p->next = u;
	p=p->next;
	
	for(int i = 0;i < 4;++i){
		Node * t = new Node;
		t->coef = 2;
		t->exp = i;
		t->next = NULL;
		q->next = t;
		q = q->next;
	}
	Node * m = new Node;
	m->coef = 2;
	m->exp = 4;
	m->next = NULL;
	q->next = m;
	q=q->next;
	
	UPAdd(A,B);
	p = A->next;
	while(p!=NULL){
		cout << p->coef << " " << p->exp << endl;
		p=p->next;
	}
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
