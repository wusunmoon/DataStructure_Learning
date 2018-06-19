/*
	程序： 基于链表的直接插入排序
	作者：Moyu 
*/
#include<iostream>
#include<vector>
#include<random>
#include<ctime>

using namespace std;

const int Size = 16;

struct Node{
	int data;
	Node * next;
};
void InitRandomArr(Node * &first, int n);
void OutPut(Node * first);
void InsertSortLink(Node * first);
int main()
{
	Node * first = NULL;
	InitRandomArr(first,Size);
	cout << "随机数组排序：" << endl; 
	OutPut(first);
	InsertSortLink(first);
	cout << "排序结果：" << endl;
	OutPut(first);
	while(first != NULL){
		Node * p = first->next;
		delete first;
		first = p;
	}
	return 0;
}
/*
	函数：初始化随机数链表 
	参数：first：链表首指针 	n：初始化大小 
	Bug修复：first要使用引用类型 
*/ 
void InitRandomArr(Node * &first, int n)
{
	first = new Node{0,NULL};//头结点 
	Node * p = first; 
	uniform_int_distribution<unsigned> u(1,n);
	default_random_engine e(time(0));
	for(size_t i = 0; i < n; ++i){
		int t = u(e);
		p->next = new Node{t,NULL};
		if(p->next != NULL)
			p = p->next;
		else{
			cerr << "内存不足！！！" << endl;
			exit(0);
		}
	} 
}
/*
	函数：输出链表 
	参数：first：链表首指针 
*/ 
void OutPut(Node * first)
{
	Node * p = first->next;
	while(p != NULL){
		cout << p->data << " ";
		p = p->next;
	}
	cout << endl;
}
/*
	函数：基于链表的直接插入排序
	参数：first：链表首指针 
*/
void InsertSortLink(Node * first)
{
	Node * p = first;
	Node * pre = p->next;
	Node * q = pre->next;
	while(q != NULL){
		while(p->next != q){
			if(p->next->data <= q->data)
				p = p->next;
			else
				break;
		}
		if(p->next != q){
			pre->next = q->next;
			q->next = p->next;
			p->next = q;
			q = pre->next;
		}
		else{
			pre = q;
			q = q->next;
		}
		p = first;
	} 
}
