#include<iostream>
#include<random>
#include<ctime>

#include"btree.h"

using namespace std;

int dice(int range)
{
	uniform_int_distribution<unsigned> u(0, range);
	default_random_engine e((unsigned)time(0));
	return u(e);
}

template<typename T>
void testBTree(int order, int n)
{
	BTree<T> bt(order);
	while (bt.size() < n) {
		T e = (T)dice(n * 3);	//[0,3n)范围内的e
		switch (dice(3))
		{
		case 0: {	//查找，成功率 <= 33.3%
			cout << "Searching for " << e << " ... ";
			BTNodePosi(T) p = bt.search(e);
			cout << (p ? "Found" : "Not found") << endl;
			break;
		}
		case 1: {	//删除，成功率 <= 33.3%
			cout << "Removing " << e << " ... ";
			bt.remove(e) ? (cout << "Done" << endl) : (cout << "Not exists" << endl);
			break;
		}
		default: {	//插入，成功率 == 100%
			cout << "Inserting " << e << " ... ";
			int oldSize = bt.size();
			bt.insert(e) ? (cout << "Done" << endl) : (cout << "Dup key" << endl);
			break;
		}
		}
	}
	while (bt.size() > 0) {
		T e = (T)dice(n * 3);	//[0,3n)范围内的e
		cout << "Removing " << e << " ... ";
		bt.remove(e) ? (cout << "Done" << endl) : (cout << "Not exists" << endl);
	}
}
int main()
{
	int order = 3;
	int size = 5;
	testBTree<int>(order, size);
	return 0;
}