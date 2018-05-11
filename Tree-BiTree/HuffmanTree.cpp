//哈夫曼算法

#include<iostream>

using namespace std;

typedef struct huffmannode{
	int w;
	int lchild,rchild,parent;
}HFNode;

void Select(HFNode huffTree[],int n,int &i1,int &i2);
void HuffmanTree(HFNode huffTree[],int w[],int n);
int main()
{
	int n;
	cin >> n;
	int * w = new int[n];
	for(int i = 0; i < n; ++i)
		cin >> w[i];
		 
	HFNode * huffTree = new HFNode[2*n-1];
	HuffmanTree(huffTree,w,n);
	
	for(int i = 0; i < 2*n-1; ++i){
		cout << huffTree[i].w << "  " << huffTree[i].parent << "  " << huffTree[i].lchild << "  " << huffTree[i].rchild;
		cout << endl; 
	}
	return 0;
}
void HuffmanTree(HFNode huffTree[],int w[],int n)
{
	for(int i = 0; i < 2 * n -1; ++i){
		huffTree[i].parent = -1;
		huffTree[i].lchild = -1;
		huffTree[i].rchild = -1;
		if(i < n){
			huffTree[i].w = w[i];
		}
	}
	
	for(int i = n; i < 2 * n - 1; ++i){
		int i1,i2;
		Select(huffTree,i,i1,i2);
		huffTree[i].lchild = i1;
		huffTree[i].rchild = i2;
		huffTree[i].w = huffTree[i1].w + huffTree[i2].w;
		
		huffTree[i1].parent = i;
		huffTree[i2].parent = i;
	}
}
void Select(HFNode huffTree[],int k,int &i1,int &i2)
{	
	int flag = 0;
	for(int i = 0; i < k; ++i){
		if(huffTree[i].parent == -1){
			if(flag == 0){
				i1 = i;
				++flag;
				continue;
			}
			if(flag == 1){
				huffTree[i1].w < huffTree[i].w ? (i2=i) : (i2=i1,i1=i);
				++flag;
				continue;
			}
			if(huffTree[i].w < huffTree[i1].w){
				i1 = i;
				continue;
			}
			if(huffTree[i].w >= huffTree[i1].w && huffTree[i].w < huffTree[i2].w){
				i2 = i;
				continue;
			}
		}
	}
}
