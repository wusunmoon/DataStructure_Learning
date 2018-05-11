//迷宫问题求解

#include<iostream>
#include<stack>

using namespace std;

typedef struct point{
	int x,y;
}Point;
Point move[4];
typedef struct state{
	Point p;	//位置 
	int d;		//方向 
}State;

bool maze[][10]={
	1,1,1,1,1,1,1,1,1,1,
	1,0,0,1,1,0,1,1,1,1,
	1,1,0,0,0,1,1,1,1,1,
	1,0,1,0,0,0,0,0,1,1,
	1,0,1,1,1,0,1,1,1,1,
	1,1,0,0,1,0,0,0,0,1,
	1,0,1,1,0,0,1,1,0,1,
	1,1,1,1,1,1,1,1,1,1 
};
bool flag[8][10];

void MoveInit()
{
	move[0].x = 0;
	move[0].y = -1;
	move[1].x = 1;
	move[1].y = 0;
	move[2].x = 0;
	move[2].y = 1;
	move[3].x = -1;
	move[3].y = 0;	
}
int main()
{
	Point start,end;	//起始位置，终止位置 
	start.x = 1;
	start.y = 1;
	end.x = 6;
	end.y = 8;
	
	MoveInit();		
	
	State st0;
	st0.p = start;
	st0.d = -1; 
	stack<State> s;
	s.push(st0);
	flag[st0.p.x][st0.p.y] = 1;
	
	bool ok = false;
	while(!s.empty()){
		State st = s.top();
		s.pop();
		flag[st.p.x][st.p.y] = 0;
		++st.d;
		Point tmp;
		while(st.d < 4){
			tmp.x = st.p.x + move[st.d].x;
			tmp.y = st.p.y + move[st.d].y;
			if(maze[tmp.x][tmp.y] == 0 && !flag[tmp.x][tmp.y]){
				s.push(st);
				flag[st.p.x][st.p.y] = 1;
				st.p = tmp;
				if(st.p.x == end.x && st.p.y == end.y){
					ok = true;
					break;
				}
				else{
					st.d = 0;
				}
			}
			else{
				++st.d;
			}
		}
		if(ok){
			break;
		}
	}
	if(ok){
		cout << "存在" << endl;
	}
	else{
		cout << "不存在" << endl;		
	}
	return 0;
}
