//括号匹配
#include<iostream>
#include<string>

using namespace std;

bool isMatch(string exp)
{
	char stack[exp.size()];
	int top=-1;
	
	bool r = 1;
	for(int i = 0;i < exp.size(); ++i){
		if(top == -1 || exp[i] == '('||exp[i] == '['||exp[i] == '{')
			stack[++top] = exp[i];
		else if(exp[i] == ')'||exp[i] == ']'||exp[i] == '}'){
			if(exp[i] == ')' && stack[top] == '(' ||
				exp[i] == ']' && stack[top] == '[' ||
				exp[i] == '}' && stack[top] == '{')
				--top;
			else
				r = 0;
		}
		else
			continue;	
	}
	if(top != -1 || r == 0)
		return false;
	else
		return true;
}
int main()
{
	string exp;
	cin >> exp;
	cout << isMatch(exp) << endl;
	return 0;
}
