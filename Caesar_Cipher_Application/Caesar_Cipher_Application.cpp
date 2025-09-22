#include <iostream>
#include <string>
#include <Windows.h>
//nokiax caesar cipher encode/decode program v1.42
//TODO:优化代码
//support:自动符号数字分离 符号原样输出 大小写自动分离移动
using namespace std;
int encrypt(string msg, int mvb)
{
	size_t msgsz;
	unsigned int i;			//unsigned int 是为了解决x86系统上i和msgsz变量类型不同的警告，应该不会出bug
	unsigned char errflag = 0;
	char tbr;
	mvb = mvb % 26;			//百分号一下以防止输入位移数字过大导致无法正确输出字符
	//cout << mvb;
	msgsz = msg.size();
	//cout << "size_t var: " << msgsz << endl;				//检查字符串长度 debug用
	cout << "encrypted output:" << "|";
	SetConsoleOutputCP(437);								//设置cmd窗口代码页防止ASCII字符显示错误
	for (i = 0; i < msgsz; i++)
	{
		//cout << i << endl;
		tbr = msg[i];
		errflag = 0;
		//cout << tbr << endl;
		//cout << (int)(tbr) << endl;
		//cout << (int)(tbr + mvb) << endl;
		if ( ((int)(tbr) < 65) || ((int)(tbr) > 90) && ((int)(tbr) <97) || ((int)(tbr) >122)  )
		{
			cout << tbr;
		}
		else
		{
			if (((int)(tbr) > 96) && ((int)(tbr) < 123))
			{
				//cout << "lowercase" << endl;
				if ((int)(tbr + mvb) > 122)
				{
					errflag = 1;
					cout << (char)((int)(tbr + mvb - 26));
				}
				if ((int)(tbr + mvb) < 97)
				{
					errflag = 2;
					cout << (char)((int)(tbr + mvb + 26));
				}
			}

			if (((int)(tbr) > 64) && ((int)(tbr) < 91))
			{
				//cout << "uppercase" << endl;
				if ( (int)(tbr + mvb) > 90 )
				{
					errflag = 3;
					cout << (char)((int)(tbr + mvb - 26));
				}
				if ((int)(tbr + mvb) < 65 )
				{
					errflag = 4;
					cout << (char)((int)(tbr + mvb + 26));
				}
			}
			//default char move
			if (errflag == 0)
			{
				cout << (char)((int)(tbr + mvb));
			}
		}
	}
	cout << "|" << endl;
	if (errflag == 1)
	{
		cout << "WARN:overflow! char z returned to a!" << endl;
	}
	if (errflag == 2)
	{
		cout << "WARN:overflow! char a returned to z!" << endl;
	}
	if (errflag == 3)
	{
		cout << "WARN:overflow! char Z returned to A!" << endl;
	}
	if (errflag == 4)
	{
		cout << "WARN:overflow! char A returned to Z!" << endl;
	}
	SetConsoleOutputCP(936);								//设置回来防止中文出现乱码
	return 0;
}

int main()
{
	string msg;
	long int mvb;
	bool err = false;
//	inpstr:													//作为函数跳转备用，写出来goto之后会莫名无限死循环故注释
	cout << "<!只支持ASCII内符号！禁止输入中文!>" << '\n' << "input the string to be encrypted: ";
	SetConsoleOutputCP(437);								//同时需要设置这里以保证输入的ASCII字符不会被GBK意外解码成乱码
	getline(cin, msg);
//	inpmv:													//作为函数跳转备用，写出来goto之后会莫名无限死循环故注释
	SetConsoleOutputCP(936);								//设置回来以显示中文
	cout <<"<!注意此处使用的是long int 请确保输入的数字是±2^32-1(x86)或±2^64-1(x86_64)以内的数!>"<<'\n' << "How many bit(s) the each char move?" << endl;	//<我没写位移合法性检查！请自行检查位移之后是否出现特殊字符！解密输入负值即可！>
	cout << "move bit(s):";																																//这句话已经可以删除，已经写出了特殊符号原样输出
	cin >> mvb;

	if (cin.fail()) {
		cerr << "ERR: Invalid input!" << endl;
		err = true;
		//goto inpmv;
	}
	if (msg.size() == 0) {
		cout << "ERR: The string is empty!" << endl;
		err = true;
		//goto inpstr;
	}
	if (err != true)
	{
		encrypt(msg, mvb);
	}

/**	cout << '\n' << '\n' << "----------Debug output----------" << endl;
	cout << "mov bts:" << mvb << endl;
	cout << "inp msg:" << msg << endl;
	cout << "string length:" << msg.size() << endl;	**/
	system("PAUSE");
	return 0;
}

// 运行程序 (Visusal Studio): Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单