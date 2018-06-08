/*
程序：散列查找
作者：moyu 
*/
#include<iostream>
#include<vector>
#include<random>
#include<ctime>

using namespace std;

const int Max = 11;
inline int Hash(int k)
{
	return k%Max;
}
bool HashSearch(vector<int> &ht,int k, int &index, int &count)
{
	int h = Hash(k);
	count = 1;
	int i;
	if(ht[h] == k){
		index = h;
		return true;
	}
	else if(ht[h] == 0){
		ht[h] = k;
		return false;
	}
	else{
		i = (h + 1) % Max; 
		while(ht[i] != 0 && i != h && ht[i] != k){
			++count;
			i = (i + 1) % Max;
		}
		if(ht[i] == 0){
			ht[i] = k;
			return false;
		}
		if(i == h){
			cout << "溢出" << endl;
			return false;
		}
		if(ht[i] == k){
			index = i;
			return true;
		}
			
	}
}
int main()
{
	int index;
	int count;
	vector<int> s = {47, 7, 29, 11, 16, 92, 22, 8, 3};
	vector<int> ht(Max,0);
	for(auto i : s)
		HashSearch(ht,i,index,count);
	
	for(auto i : ht)
		cout << i << " ";
	cout << endl;
	
	uniform_int_distribution<unsigned> u(0,8);
	default_random_engine e(time(0));
	int t = s[(u(e) + u(e)) / 2];
	cout << "查找元素 " << t << endl;
	if(HashSearch(ht,t,index,count)){
		cout << "查找成功！" << "元素 " << t << "的下表为" << index;
		 cout << " 共比较 " << count << " 次" << endl;
	}
	return 0;
}
