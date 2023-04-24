#include<fstream>  
#include<iostream>
using namespace std;

int main()
{
	ifstream in;
	ofstream out;
	in.open("project1.txt");  //读取文件
	out.open("project2.txt");//打开写文件
	if (!in|| !out)
	{
		cout << "打开失败！" << endl;
		return 0;
	}
	else {
		cout << "打开成功" << endl;
	}
	
	char x;
	while (in >> x)   //复制
	{
		out << x;
	}
	cout << "复制完成"<<endl;
	out.close();//关闭文件
	in.close();
	return 0;
}
