#include<iostream>
#include<random>
#include<ctime>
#include<thread>

#include"RedBlack.h"

using namespace std;

int dice(int range)
{
	uniform_int_distribution<unsigned> u(0, range);
	this_thread::sleep_for(1s);
	default_random_engine e((unsigned)time(0));
	return u(e);
}

template<typename T>
void testRedBlack(int n)
{
	RedBlack<T> rb;
	while (rb.size() < n) {
		T e = (T)dice(n * 3);	//[0,3n)范围内的e
		switch (dice(6))
		{
		case 0: {	//查找(概率：1/6)
			cout << "Searching for " << e << " ... " << endl;
			BinNodePosi(T) p = rb.search(e);
			cout << (p ? "Found" : "Not found") << endl;
			break;
		}
		case 1:
		case 2: {	//删除（概率：1/3）
			cout << "Removing " << e << " ... " << endl;
			rb.remove(e) ? (cout << "Done" << endl) : (cout << "Not exists" << endl);
			break;
		}
		default: {	//插入(概率：1/2)
			cout << "Inserting " << e << " ... " << endl;
			BinNodePosi(T) p = rb.insert(e);
			if (p->data != e)
				cout << p->data << "<>" << e << endl;
			cout << "Done!" << endl;
			break;
		}
		}
	}
	while (rb.size() > 0) {
		T e = (T)dice(n * 3);	//[0,3n)范围内的e
		cout << "Removing " << e << " ... " << endl;
		rb.remove(e) ? (cout << "Done" << endl) : (cout << "Not exists" << endl);
	}
}
int main()
{
	int size = 16;
	testRedBlack<int>(size);
	return 0;
}