//队列的应用----火车车厢重排
#include<cstdio>
#include<iostream>
#include<vector>

using namespace std;

const int QueueSize = 100;
class Queue{
	public:
		Queue(){
			front = rear = QueueSize - 1;  
		}
		~Queue(){}
		void EnQueue(int x);
		int DeQueue();
		int GetQueue();
		int GetRear(); 
		bool Empty(){
			return front == rear;
		}
		void PrintQu();
	private:
		int data[QueueSize];
		int front,rear;
};
int main()
{
	Queue in;		//入轨
	Queue out;		//出轨
	Queue cache[6];	//缓冲轨
	
	int n;			//车厢数量 
	cin >> n;
	int t;
	for(int i = 0; i < n; ++i){
		scanf("%d",&t);
		in.EnQueue(t);
	}
	int k;			//缓冲轨数量
	cin >> k;
	 
	bool cacheEmpty = 1;
	int nowOut = 1;
	while(!in.Empty() || !cacheEmpty){
		if(!in.Empty() && in.GetQueue() == nowOut){
			out.EnQueue(in.DeQueue());
			++nowOut;
			continue;
		}
		
		bool flag = false;
		for(int i = 0; i < k; ++i){
			if(!cache[i].Empty() && cache[i].GetQueue() == nowOut){
				out.EnQueue(cache[i].DeQueue());
				++nowOut;
				flag = true;
				break;
			}
		}
		if (flag) {
			cacheEmpty = 1;
			for (int i = 0; i < k; ++i) {
				if (!cache[i].Empty())
				{
					cacheEmpty = 0;
					break;
				}
			}

			continue;
		}
		
		int ok = 0;
		int j = -1;
		int t = 0;
		for(int i = 0; i < k; ++i){
			if (j < 0 && cache[i].Empty()) {
				j = i;
				ok = 1;
			}
			if(!cache[i].Empty() && cache[i].GetRear() < in.GetQueue()){
				if(cache[i].GetRear() > t){
					t = cache[i].GetRear();
					j = i;
				}
				ok = 1;
			}
		}
		if(ok){
			cache[j].EnQueue(in.DeQueue());
		}
		else{
			cerr << "无法重排！！！" << endl;
			return 0; 
		}

	}
	
	out.PrintQu();
	return 0;
}

void Queue::EnQueue(int x)
{
	if((rear+1)%QueueSize == front)
		throw "溢出";
	rear = (rear+1)%QueueSize;
	data[rear] = x; 
}
int Queue::DeQueue()
{
	if(front == rear)
		throw "溢出";
	front = (front+1)%QueueSize;
	return data[front];
}
int Queue::GetQueue()
{
	if(front == rear)
		throw "溢出";
	int i = (front+1)%QueueSize;
	return data[i];	
}
int Queue::GetRear()
{
	if(front == rear)
		throw "溢出";
	return data[rear]; 
}
void Queue::PrintQu()
{
	int i = front;
	while(i != rear){
		i = (i + 1) % QueueSize;
		cout << data[i] << " ";	
	}
}
