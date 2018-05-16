/**********信号放大器
1.问题描述：
    天然气经过管道网络从其生产基地输送到消耗地，在传输过程中，其性能的某一个或几个方面可能会有所衰减（例如气压）。为了保证衰减不超过容忍值，应在网络中
的合适位置放置放大器以增加信号（例如气压）使其与源端相同。设计算法确定把信号放大器放在何处，能使所用的放大器数目最少并且保证信号衰减不超过给定的容忍值。
2.基本要求：
    （1）建立模型，设计数据结构
    （2）设计算法完成放大器的放置
    （3）分析算法的时间复杂度
3.设计思想：
  为了简化问题，假设分布网络是二叉树结构，源端是树的根节点，信号从一个节点流向其孩子节点，树中的每一个节点（除了根）表示一个可以用来放置放大器的位置。
                     A                右图是一个网络示意图，边上标出的是父节点到子节点的信号衰减量。
                 /      \             对于网络中的任一节点i，设d(i)表示节点i与其父节点间的衰减量，D(i)为从节点i到节点i的子树中任一叶子节点的衰减
                1        3        量的最大值，并有如下递推公式：
               /          \           /D(i)=0                 若i为叶节点
              B            C          \D(i)=max{D(j)+d(j)}    若i不是叶节点且j是i的孩子
             / \          / \     在此公式中，要计算某节点的D值，必须先计算其孩子节点的D值，因而必须后序遍历二叉树，当访问一个节点时，计算其D值。
            2   2        1   2
           /     \      /     \
          D       E    F       G
         / \           |       |
        2   1          2       2
       /     \         |       |
      H       I        J       K
4.思考题
    上述设计思想中，假设分布网络是一棵二叉树结构，如果分布网络是树结构应如何设计算法？
*/
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<queue>
#include<algorithm>

#define THRESHOLD 3//容忍值
using namespace std;

struct element{
	char name;		//节点名称 
	int D;			//从该节点到该节点子树中任一叶子节点的衰减量的最大值 
	int d;			//该节点与其父节点间的衰减量 
	bool boost;		//当且仅当该节点放置放大器时，boost==true 
};
struct BiNode{
	element data;
	BiNode * lchild, * rchild;
}; 

void InOrder(BiNode * bt);
void InitTree(BiNode * &bt);
void SetBoost(BiNode * bt);
void Print(BiNode * bt);

int main()
{
	BiNode * root = NULL;
	InitTree(root);
	SetBoost(root);
	cout << "信号放大器放置位置为：";
	Print(root);
	cout << endl;
	return 0;
}

//初始化树
void InitTree(BiNode * &bt)
{
	//从文件读取网络图 
	ifstream fs("F:\\c++ project\\netdis.txt",ifstream::in);
	string line;
	
	//根节点 
	bt = new BiNode;
	getline(fs,line);
	stringstream ss(line);
	ss >> (bt->data).name;
	(bt->data).D = 0;
	(bt->data).d = 0;
	(bt->data).boost = false;
	bt->lchild = NULL;
	bt->rchild = NULL;
	 
	BiNode * p = NULL, * q = NULL;
	char ch1,ch2;
	int val;
	queue<BiNode *> Q;
	Q.push(bt);
	while(getline(fs,line)){
		stringstream liness(line);
		liness >> ch1 >> ch2 >> val;
		p = new BiNode;
		(p->data).name = ch2;
		(p->data).D = 0;
		(p->data).d = val;
		p->lchild = NULL;
		p->rchild = NULL;
		Q.push(p);
		while(!Q.empty()){
			q = Q.front();
			if((q->data).name != ch1)
				Q.pop();
			else{
				if(q->lchild == NULL)
					q->lchild = p;
				else{
					q->rchild = p;
				}
				break;
			}
		}
	}
} 
//放置放大器
void SetBoost(BiNode * bt)
{
	if(bt != NULL){
		SetBoost(bt->lchild);
		SetBoost(bt->rchild);
		if(bt->lchild != NULL){
			element t = (bt->lchild)->data;
			if((t.D + t.d) > THRESHOLD){
				(bt->lchild)->data.boost = true;
				(bt->lchild)->data.D = 0;
				return;
			}
			else{
				bt->data.D = max(bt->data.D,t.D+t.d);
			}
		}
		if(bt->rchild != NULL){
			element t = (bt->rchild)->data;
			if((t.d+t.d) > THRESHOLD){
				(bt->rchild)->data.boost = true;
				(bt->rchild)->data.D = 0;
				return;
			}
			else{
				bt->data.D = max(bt->data.D,t.D+t.d);
			}
		}
	}
} 
//输出结果 
void Print(BiNode * bt)
{
	if(bt != NULL){
		Print(bt->lchild);
		if((bt->data).boost)
			cout << (bt->data).name << " "; 
		Print(bt->rchild);
	}
}
