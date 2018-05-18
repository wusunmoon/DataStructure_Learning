/*
                            K-近似匹配
1.问题描述
    在一个文本中查找某个给定的单词，由于单词本身可能有文法上的变化，加上书写和印刷方面的错误，实际应用中往往需要进行近似匹配。这种近似串匹配与串匹配不
同，实际问题中确定两个字符串是否近似匹配不是一个简单的问题，例如，可以说pattern与patern是近似的，但pattern与patient就不是近似的，这存在一个差别大小
的问题。
    设样本P=p1p2...pm,文本T=t1t2...tn,对于一个非负整数K，样本P在文本T中的K-近似匹配(K-approximate Match)是指P在T中包含至多K个差别的匹配（一般情况
下，假设样本是正确的）。这里的差别是指下列三种情况之一：
    （1）修改：P与T中对应字符不同。
    （2）删去：T中含有一个未出现在P中的字符。
    （3）插入：T中不含有出现在P中的一个字符。
2.基本要求
（1）设计算法判断样本P中是否是文本T的K-近似匹配；
（2）设计程序实现你设计的算法，并设计有代表性的测试数据；
（3）分析算法的时间复杂度。
3.设计思想
      样本P和文本T为K-近似匹配包含两层含义：
      （1）二者的差别数至多为K；
      （2）差别数是指二者在所有匹配对应方式下的最小编辑错误总数。
      下面介绍用动态规划法设计的算法。定义一个代价函数D（i，j）（0<=i<=m,0<=j<=n）表示样本前缀子串p1...pi与文本前缀子串t1...tj之间的最小差别数，则
D（m，n）表示样本P与文本T的最小差别数。根据近似匹配的定义，容易确定代价函数的初始值：
      （1）D（0，j）= 0，这是因为样本为空串，与文本t1...tj有0出差别；
      （2）D（i，0）= i，这是因为样本p1...pi与空文本t1...tj有i处差别。
      当样本p1...pi与文本t1...tj对应时，D(i,j)有以下4种可能的情况：
      （1）字符pi与tj相对应且pi=tj，则总差别数为D(i-1,j-1)；
      （2）字符pi与tj相对应且pi!=tj,则总差别数为D(i-1,j-1)+1；
      （3）字符pi为多余，即字符pi对应于tj后的空格，则总差别数为D(i-1,j)+1；
      （4）字符tj为多余，即字符tj对应于pi后的空格，则总差别数为D(i,j-1)+1。
      由此，得到如下递推式：
                  / 0                                        i=0
                /   i                                        j=0
      D(i,j) = |    min{D(i-1,j-1),D(i-1,j)+1,D(i,j-1)+1}    i>0,j>0,pi=tj
                \   min{D(i-1,j-1)+1,D(i-1,j)+1,D(i,j-1)+1}  i>0,j>0,pi!=tj
*/
#include<iostream>
#include<string>
#include<algorithm>

using namespace std;

bool ASM(string &P,string &T,int K);
int main()
{
	string p = "approximatly";
	string t = "aproxiomally";
	cout << ASM(p,t,3) << endl;
	return 0;
}

bool ASM(string &P,string &T,int K)
{
	int m = P.size();
	int n = T.size();
	int **D = new int*[m+1];
	for(int i = 0; i < m+1; ++i)
		D[i] = new int[n+1];
	
	for(int j = 0; j <= n; ++j)
		D[0][j] = 0;
	for(int i = 0; i <= m; ++i)
		D[i][0] = i;
	for(int j = 1; j <= n; ++j){
		for(int i = 1; i <= m; ++i){
			if(P[i] == T[j])
				D[i][j] = min({D[i-1][j-1],D[i-1][j]+1,D[i][j-1]+1});
			else
				D[i][j] = min({D[i-1][j-1]+1,D[i-1][j]+1,D[i][j-1]+1});				
		}
	}
	bool r = D[m][n]<=K?true:false;
	for(int i = 0; i < m+1; ++i)
		delete []D[i];
	delete []D;
	return r;
}
