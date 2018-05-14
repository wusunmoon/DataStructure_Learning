//二叉表示树
//将算术表达式转化为二叉表示树
//对二叉表示树进行前序、中序和后序遍历，验证表达式的前缀、中缀和后缀形式
#include<iostream>
#include<string>
#include<stack>

using namespace std;

//树节点 
struct BrtNode{
	string data;
	BrtNode * lchild, * rchild;
};
// 左操作数 运算符 右操作数
struct LopR{
	string lopnd;
	string optr;
	string ropnd;
};
//运算符优先级				+	-	*	/	(	)	#
char OprRelation[7][7] = { '>','>','<','<','<','>','>',
						   '>','>','<','<','<','>','>',
						   '>','>','>','>','<','>','>',
						   '>','>','>','>','<','>','>',
						   '<','<','<','<','<','=','>',
						   '>','>','>','>','>','>','>',
						   '<','<','<','<','<','<','='
						};

class BrTree{
	public:
		BrTree();
		~BrTree(){Release(root);};
		void PreOrder(){PreOrder(root);}
		void InOrder(){InOrder(root);}
		void PostOrder(){PostOrder(root);}
	
	private:
		BrtNode * root;
		BrtNode * Creat(BrtNode * bt,string exp);
		void Release(BrtNode * bt);
		void PreOrder(BrtNode * bt);
		void InOrder(BrtNode * bt);
		void PostOrder(BrtNode * bt);
};

//前序遍历 
void BrTree::PreOrder(BrtNode * bt)
{
	if(bt != NULL){
		cout << bt->data << " ";
		PreOrder(bt->lchild);
		PreOrder(bt->rchild);
	}
}
//中序遍历 
void BrTree::InOrder(BrtNode * bt)
{
	if(bt != NULL){
		InOrder(bt->lchild);
		cout << bt->data << " ";
		InOrder(bt->rchild);
	}
}
//后序遍历 
void BrTree::PostOrder(BrtNode * bt)
{
	if(bt != NULL){
		PostOrder(bt->lchild);
		PostOrder(bt->rchild);
		cout << bt->data << " ";
	}
}
//析构函数调用释放内存 
void BrTree::Release(BrtNode * bt)
{
	if(bt != NULL){
		Release(bt->lchild);
		Release(bt->rchild);
		delete bt;
	}
}

//构造函数相关的函数声明 
bool IsOperator(char ch);
bool BeOperator(string exp);
int ConvertIndex(char optr);
char Precede(char optr1, char optr2);
LopR ConverLor(string exp);

BrTree::BrTree()
{
	string exp;
	cout << "请输入算术表达式：";
	cin >> exp;
	
	root = Creat(root,exp); 
}
//递归生成二叉树 
BrtNode * BrTree::Creat(BrtNode * bt,string exp)
{
	if(exp.size()!=0){
		if(!BeOperator(exp)){
			bt = new BrtNode{exp,NULL,NULL};
		}	
		else{
			LopR lopr =  ConverLor(exp);
			bt = new BrtNode{lopr.optr,NULL,NULL};
			bt->lchild = Creat(bt->lchild,lopr.lopnd);
			bt->rchild = Creat(bt->rchild,lopr.ropnd);
		}
	}
	return bt;
}
//表达式是否存在操作符 
bool BeOperator(string exp)
{
	for(int i = 0; i < exp.size(); ++i){
		char ch = exp[i];
		if(ch == '+' || ch == '-' | ch == '*' || ch == '/' ||
			ch == '(' || ch == ')' || ch == '#')
			return true;
	}
	return false;
}
//将表达式结合成“左操作数 运算符 右操作数” 
LopR ConverLor(string exp)
{
	LopR r;
	
	exp = exp + "#";
	
	stack<string> optr;
	stack<string> opnd;
	int i = 0;
	string ts;
	
	optr.push("#");
	char ch = exp[i++];
	while(ch != '#'){
		if(!IsOperator(ch)){
			ts = "";
			while(!IsOperator(ch)){
				ts += ch;
				ch = exp[i++];	
			}
			opnd.push(ts);
		}
		else{
			switch(Precede(optr.top()[0],ch)){
				case '<':
					ts = "a";//a仅用来占内存 
					ts[0] = ch;//将单字符-->>string 
					optr.push(ts);
					ch = exp[i++];
					break;
				case '=':
					optr.pop();
					ch = exp[i++];
					break;
				case '>':
					ts = "(";
					string ts2 = opnd.top();opnd.pop();
					string ts1 = opnd.top();opnd.pop();
					ts = ts + ts1 + optr.top() + ts2 + ")";
					optr.pop();
					opnd.push(ts);
					break;					
			}
		}
	}
	string rs = opnd.top();opnd.pop();
	string ls = opnd.top();opnd.pop();
	r.optr = optr.top();optr.pop();
	r.ropnd = BeOperator(rs)?rs.substr(1,rs.length()-2):rs;//存在操作符去括号 
	r.lopnd = BeOperator(ls)?ls.substr(1,ls.length()-2):ls;//不存在操作符不去括号
	return r;
} 
//两个操作符的运算优先级 
char Precede(char optr1, char optr2)
{
	int i = ConvertIndex(optr1);
	int j = ConvertIndex(optr2);
	return OprRelation[i][j];
}
//操作符---->>>>索引值 
int ConvertIndex(char optr)
{
	int index;
	switch(optr){
		case '+':
			index = 0;
			break;
		case '-':
			index = 1;
			break;
		case '*':
			index = 2;
			break;
		case '/':
			index = 3;
			break;
		case '(':
			index = 4;
			break;
		case ')':
			index = 5;
			break;
		case '#':
			index = 6;
			break;
		default:
			cerr << "error" << endl;
	}
	return index;
}
//字符是否是操作符 
bool IsOperator(char ch)
{
	if(ch == '+' || ch == '-' | ch == '*' || ch == '/' ||
		ch == '(' || ch == ')' || ch == '#')
		return true;
	else
		return false;
}
