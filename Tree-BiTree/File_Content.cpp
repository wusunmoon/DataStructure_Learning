/*
                  文件/目录树
    UNIX的文件/目录结构如图1所示，*表示目录，括号内的数字是文件/目录的大小。
    （1）试设计一种数据结构表达这种关系。
    （2）设计算法输出如图2所示的结果（要求次序和数字不能改变）。
     __________________________                        —————————————
    | /usr*       (1)          |                      | hw.c(3)     |
    |   mark*       (1)        |                      | aa.txt(12)  |
    |     hw.c        (3)      |                      | course(13)  |
    |     course*       (1)    |                      | mark(17)    |
    |       aa.txt        (12) |                      | hw.c(5)     |
    |   alex*   (1)            |                      | alex(6)     |
    |     hw.c    (5)          |                      | aa.txt(13)  |
    |   bak*    (1)            |                      | bak(14)     |
    |     aa.txt    (13)       |                      | /usr(38)    |  
    |__________________________|                      |_____________|  
       图1 UNIX的文件/目录结构                            图2 输出结果
*/
#include<iostream>
#include<string>
#include<queue>
#include<fstream>
#include<sstream>

using namespace std;

struct TNode{
	string fname;
	int fsize;
	int size;
	TNode * firstchild, * rightsib;
};

void Init(TNode * &t);
void PostOrder(TNode * t);

int main()
{
	TNode * root;
	Init(root);
	PostOrder(root);
	return 0;
}

void PostOrder(TNode * t)
{
	if(t != NULL){
		PostOrder(t->firstchild);
		if(t->firstchild != NULL){
			TNode * p = t->firstchild;
			while(p->rightsib != NULL){
				PostOrder(p->rightsib);
				p = p->rightsib;
			}
		}
		t->size = t->fsize;
		if(t->firstchild != NULL){
			TNode * p = t->firstchild;
			while(p != NULL){
				t->size += p->size;
				p = p->rightsib;
			}			
		}
		cout << t->fname << "(" << t->size << ")" << endl;
	}
}

//初始化文件/目录树 
void Init(TNode * &t)
{
	string filename;
	int filesize;
	cout << "输入根目录文件名及其文件大小：";
	getline(cin,filename,' ');
	cin >> filesize;
	t = new TNode{filename,filesize,0,NULL,NULL};
	TNode * p = t;
	
	queue<TNode *> q;
	q.push(p);

	ifstream fs("FileStruct.txt",ifstream::in);
	string line;
	
	string str,str1;
	int size;
	while(getline(fs,line)){
		stringstream liness(line);
		getline(liness,str,' ');
		getline(liness,str1,' ');
		liness >> size;
		p = new TNode{str1,size,0,NULL,NULL};
		q.push(p); 
		while(!q.empty()){
			TNode * tp = q.front();
			if(tp->fname != str){
				q.pop();
				continue;
			}
			else{
				if(tp->firstchild == NULL){
					tp->firstchild = p;
				}
				else{
					tp = tp->firstchild;
					while(tp->rightsib != NULL){
						tp = tp->rightsib;
					}
					tp->rightsib = p;
				}
				break;
			}
		} 
	}
}
