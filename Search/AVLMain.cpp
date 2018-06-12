/*
	程序：个人电话号码查询系统（基于AVL树） 
	作者：Moyu 
	1.问题描述
		人们在日常生活中经常需要查找某个人或某个单位的电话号码，本实验将实现
	一个简单的个人电话号码查询系统，根据用户输入的信息（例如姓名等）进行快速查询。
	2.基本要求
		（1）在外存上，用文件保存电话号码信息；
		（2）在内存中，设计数据结构存储电话号码信息； 
		（3）提供查询功能，如根据姓名实现快速查询；
		（4）提供其他维护功能，例如插入、删除、修改等。 
*/
#include"AVL.hpp"
#include<string>
#include<fstream>
#include<sstream>

using namespace std;

const string fpath = "PhoneBook.txt";		//电话簿文件路径 

class TeleNumber{
	public:
		friend bool operator==(const TeleNumber &tn1, const TeleNumber &tn2); 
		friend bool operator!=(const TeleNumber &tn1, const TeleNumber &tn2);
		friend bool operator<(const TeleNumber &tn1, const TeleNumber &tn2);
		friend bool operator>(const TeleNumber &tn1, const TeleNumber &tn2);
		friend ostream &operator<<(ostream &os, const TeleNumber &item);

		TeleNumber() = default;
		TeleNumber(string name, string phoneNumber="", 
					string mobileNumber="", string email=""):
					name(name),phoneNumber(phoneNumber),
					mobileNumber(mobileNumber),email(email){}
		inline string GetName() const {return name;}
		inline void SetName(string value){name = value;}
		inline string GetPhone() const {return phoneNumber;}
		inline void SetPhone(string value){phoneNumber = value;}
		inline string GetMobile() const {return mobileNumber;}
		inline void SetMobile(string value){mobileNumber = value;}
		inline string GetEmail() const {return email;}
		inline void SetEmail(string value){email = value;}

	private:
		string name;
		string phoneNumber;
		string mobileNumber;
		string email;
};
bool operator==(const TeleNumber &tn1, const TeleNumber &tn2){
	return tn1.name==tn2.name;
} 
bool operator!=(const TeleNumber &tn1, const TeleNumber &tn2){
	return !(tn1==tn2);
} 
bool operator<(const TeleNumber &tn1, const TeleNumber &tn2){
	return tn1.name<tn2.name;
} 
bool operator>(const TeleNumber &tn1, const TeleNumber &tn2){
	return tn1.name>tn2.name;
} 
ostream &operator<<(ostream &os, const TeleNumber &item){
	os << "--------------------------------------------" << endl;
	os << item.name << endl << "电话：" << item.phoneNumber << endl
		<< "手机：" << item.mobileNumber << endl << "电子邮箱：" 
		<< item.email << endl; 
	os << "--------------------------------------------" << endl;
	return os;
}
inline void OutPut(const TeleNumber &x)
{
	cout << x;
}
void OutFile(const TeleNumber &x)
{
	ofstream fs(fpath,ofstream::out | ofstream::app);
	string line = x.GetName() + " " + x.GetPhone() + " " + 
				x.GetMobile() + " " + x.GetEmail();
	fs << line << endl;
}
void Read(AVLTree<TeleNumber> &TNinfo);
void Save(AVLTree<TeleNumber> &TNinfo);
void Search(AVLTree<TeleNumber> &TNinfo);
void Add(AVLTree<TeleNumber> &TNinfo);
void Delete(AVLTree<TeleNumber> &TNinfo);
void Modify(AVLTree<TeleNumber> &TNinfo);
int main()
{
	AVLTree<TeleNumber> TNinfo;
	Read(TNinfo);
	cout << "欢迎进入个人电话号码查询系统。。。" << endl;
	cout << "功能表：1.查询	   2.添加    3.删除    4.修改" << endl;
	int funID;
	cout << "请输入功能编号：(输入0退出)";
	while(cin >> funID){
		if(funID == 0)
			break; 
		switch(funID){
			case 1:
				Search(TNinfo);
				cout << endl;
				break;
			case 2:
				Add(TNinfo);
				cout << endl;
				break;
			case 3:
				Delete(TNinfo);
				cout << endl;
				break;
			case 4:
				Modify(TNinfo);
				cout << endl;
				break;
			default:
				cout << "没有此项功能" << endl;
		}
		cout << "功能表：1.查询	   2.添加    3.删除    4.修改" << endl;
		cout << "请输入功能编号：(输入0退出)";
	}
	string m;
	cout << "是否保存修改：（Y/N）";
	cin.clear();
	cin.sync();
	while(cin >> m){
		if(m[0] == 'Y'){
			Save(TNinfo);
			break;
		}
		else if(m[0] == 'N')
			break;
		else
			cout << "请输入Y/N；";
	}
	return 0;
}
void Modify(AVLTree<TeleNumber> &TNinfo)
{
	TeleNumber mtn;
	string name,phone,mobile,email;
	
	cout << "修改姓名：";
	cin >> name;
	mtn.SetName(name);
	
	TNinfo.Search(mtn);
	cout << mtn;
	
	int mID;
	cout << "修改项：1.电话号码    2.手机号码    3.电子邮箱" << endl;
	cout << "请输入修改项编号：(输入0结束)";
	while(cin >> mID){
		if(mID == 0)
			break;
		switch(mID){
			case 1:
				cout << "新电话号码：";
				cin >> phone;
				mtn.SetPhone(phone);
				break;
			case 2:
				cout << "新手机号码：";
				cin >> mobile;
				mtn.SetMobile(mobile);
				break;
			case 3:
				cout << "新电子邮箱：";
				cin >> email;
				mtn.SetEmail(email);
				break;
			default:
				cout << "没有此修改项！！！" << endl;
				break; 
		}
		cout << "请输入修改项编号：(输入0结束)";
	}
	if(TNinfo.Modify(mtn))
		cout << "操作成功！！！" << endl;
	else
		cout << "操作失败！！！" << endl; 
		
}
void Delete(AVLTree<TeleNumber> &TNinfo)
{
	string name;
	cout << "删除姓名：";
	cin >> name;
	TeleNumber dtn;
	dtn.SetName(name);
	if(TNinfo.Delete(dtn))
		cout << "操作成功！！！" << endl;
	else
		cout << "操作失败！！！" << endl; 
}
void Add(AVLTree<TeleNumber> &TNinfo)
{
	TeleNumber atn;
	string name,phone,mobile,email;
	cout << "请输入姓名：";
	cin >> name;
	atn.SetName(name);
	cout << "请输入电话号码：";
	cin >> phone;
	atn.SetPhone(phone);
	cout << "请输入手机号码：";
	cin >> mobile;
	atn.SetMobile(mobile);
	cout << "请输入电子邮箱：";
	cin >> email;
	atn.SetEmail(email);
	if(TNinfo.Insert(atn))
		cout << "操作成功！！！" << endl;
	else
		cout << "操作失败！！！" << endl; 
}
void Search(AVLTree<TeleNumber> &TNinfo)
{
	string name;
	cout << "查询姓名：";
	cin >> name;
	TeleNumber stn;
	stn.SetName(name);
	if(TNinfo.Search(stn)){
		cout << stn;
	}
	else{
		cout << "未找到记录！！！" << endl;
	}
}
void Read(AVLTree<TeleNumber> &TNinfo)
{
	ifstream fs(fpath,ifstream::in);
	TeleNumber tn;
	string line;
	while(getline(fs,line)){
		stringstream liness(line);
		string name,phone,mobile,email;
		getline(liness,name,' ');
		getline(liness,phone,' ');
		getline(liness,mobile,' ');
		liness >> email;
		tn.SetName(name);
		tn.SetPhone(phone);
		tn.SetMobile(mobile);
		tn.SetEmail(email);
		TNinfo.Insert(tn);
	}
}
void Save(AVLTree<TeleNumber> &TNinfo)
{
	ofstream fs(fpath, ofstream::trunc);
	TNinfo.PreOrder(OutFile);
}
