/*
                        哈夫曼算法应用----文件压缩
1.问题描述
    假设某文本文档只包含26个英文字母，应用哈夫曼算法对该文档进行压缩和解压缩操作，使得该文档占用较少的存储空间。
2.基本要求
  （1）假设文档内容从键盘输入
  （2）设计哈夫曼算法的存储结构
  （3）设计哈夫曼编码和解码算法
  （4）分析时间空间复杂度
3.设计思想
  （1）对于给定的文档，首先通过扫描确定文档中出现了哪些英文字母以及出现的次数，以出现的次数作为叶子节点的权值构造哈夫曼树，获得各字符哈夫曼编码；
  （2）然后在扫描一遍文档将其进行哈夫曼压缩编码，将文本文档转换为二进制编码输出；
  （3）最后将该二进制流进行解码，并与原文档进行对照，已验证算法的正确性。
4.思考题
    如果对任意以文件形式存在的文本文档，如何实现应用哈夫曼算法进行压缩和解压缩？
*/
#include<iostream>
#include<string>
#include<queue>
#include<vector>
#include<stack>
#include<functional>

using namespace std;

struct HFNode{
	char letter;
	int weight;
	HFNode * lchild,* rchild;	
};
struct cmp{
	bool operator()(HFNode * n1, HFNode * n2){
		return n1->weight>n2->weight?true:false;
	}
};
void Release(HFNode * bt)
{
	if(bt != NULL){
		Release(bt->lchild);
		Release(bt->rchild);
		delete bt;
	}
} 
string StackToStr(vector<string> &code)
{
	string str = "";
	for(int i = 0; i < code.size(); ++i){
		str += code[i];
	}
	return str;
}
void GetHuffCode(HFNode * bt, vector<string> &codes, vector<string> &code)
{
	if(bt != NULL){
		if(bt->lchild == NULL && bt->rchild == NULL){
			codes[bt->letter-'a'] = StackToStr(code);
		}
		code.push_back("0");
		GetHuffCode(bt->lchild,codes,code);
		code.pop_back();
		code.push_back("1");
		GetHuffCode(bt->rchild,codes,code);
		code.pop_back();
	}
}
int main()
{
	string text;
	cout << "输入文档内容：" << endl;
	cin >> text;
	
	//计算26个小写字母权值 
	vector<int> w(26,0);
	for(int i = 0; i < text.size(); ++i){
		++w[text[i]-'a']; 
	}
	
	//优先级队列 
	priority_queue<HFNode *,vector<HFNode *>,cmp> P_Q;
	//初始化优先级队列 
	for(int i = 0; i < w.size(); ++i){
		if(w[i] != 0){
			HFNode * nt = new HFNode{(char)(i+'a'),w[i],NULL,NULL};
			P_Q.push(nt);
		}
	}	
	//Huffman算法 
	while(P_Q.size() > 1){
		HFNode * lnode = P_Q.top();P_Q.pop();
		HFNode * rnode = P_Q.top();P_Q.pop();
		HFNode * tnode = new HFNode{0,lnode->weight+rnode->weight,lnode,rnode};
		P_Q.push(tnode);
	} 
	//huffman树根节点
	HFNode * root = P_Q.top();P_Q.pop();
	
	vector<string> codes(26,"");//编码表
	vector<string> code;
	GetHuffCode(root,codes,code);//获取字母编码表
	
	string codeStr = "";
	cout << "编码结果：" << endl; 
	for(int i = 0; i < text.size(); ++i){
		codeStr += codes[text[i]-'a'];
	} 
	cout << codeStr << endl;
	
	//对codestr进行解码
	string decodeStr = "";
	HFNode * bt = root;
	for(int i = 0; i < codeStr.size(); ++i){
		if(codeStr[i] == '0'){
			bt = bt->lchild;
		}
		else{
			bt = bt->rchild;
		}

		if(bt->lchild == NULL && bt->rchild == NULL){
			string s = "a";
			s[0] = bt->letter;
			decodeStr += s;
			bt = root;
		}
	} 
	cout << "解码结果：" << endl << decodeStr << endl;
	Release(root);
	return 0;
}

