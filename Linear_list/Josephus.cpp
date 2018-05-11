/*
    约瑟夫环问题
*/
#include<iostream>

using namespace std;

typedef struct node{
	int data;
	struct node * next;
}Node;
int main()
{
	int n,m;
	cin >> n >> m;
	
	Node * first = NULL;
	Node * rear = NULL;
	for(int i = 1;i <= n;++i){
		Node * p = new Node;
		p->data = i;
		if(i==1){
			first=p;
			p->next=p;
			rear=p;
		}
		p->next = rear->next;
		rear->next = p;
		rear=rear->next;
	}
	
	Node * t = first;
	for(int i = 0;i < n;++i){
		cout << t->data << " ";
		t=t->next;
	}
	cout << endl;
	
	Node * pre = first;
	Node * p = first->next;
	int count = 2;
	while(pre != p){
		if(count == m){
			cout << p->data << " ";
			pre->next = p->next;
			delete(p);
			p = pre->next;
			count = 1;
		}
		pre = p;
		p = p->next;
		++count;
	}
	cout << p->data << endl;
	delete(p);
	return 0;
}
