//KMP算法实现
#include<iostream>
#include<cstdlib>
#include<cstring>

using namespace std;

int * BuildNext(char * p);
int Match(char * P, char * T);
 
int main()
{
	char T[] = "abcabcacb";
	char P[] = "abcac";
	int r = Match(P,T);
	if(r > strlen(T) - strlen(P))
		cout << "匹配失败" << endl; 
	else{
		cout << "匹配成功；在文本串位置为" << r << endl; 
	} 
	return 0;
}
//KMP----字符串匹配
int Match(char * P, char * T)
{
	int * next = BuildNext(P);//构建next表 
	int n = (int)strlen(T),i=0;//文本串指针 
	int m = (int)strlen(P),j=0;// 模式串指针
	while(j < m && i < n){//自左向右逐个比对字符 
		if(0 > j || T[i] == P[j]){//若匹配，或P已移出最左侧（两个判断次序不可交换） 
			++i;
			++j;//则转到下一字符 
		}
		else{//否则 
			j = next[j];//模式串右移（注：文本串不用回退） 
		}
	} 
	delete [] next;
	return i-j;//若匹配成功，返回文本串匹配位置i-j，若匹配失败，返回i-j=n-j>n-m 
 } 
//构造next表
int * BuildNext(char * P)//构造模式串P的next表 
{
	size_t m = strlen(P), j=0; //“主”串指针
	int * N = new int[m];//next表
	int t = N[0] = -1;//模式串指针
	 
	while(j < m-1){
		if(0 > t || P[j] == P[t]){
			++j;
			++t;
			N[j] = t;//可改进为：N[j] = (P[j] != P[t]?t:N[t]); 
		}
		else//失配 
			t = N[t];
	} 
	return N;
} 
