#include <string>
#include <fstream>
#include <iostream>
#include <list>
#include "sha512.h"
#include <thread>
#include <mutex>
#include <Windows.h>
using namespace std;
class Siganture
{
public:
	Siganture(string f1, string f2,int k);
	~Siganture();
	void readText();
	void writeHash();
	void startProc();
	void manager();
	class ErrorOpen
	{
	public:
		ErrorOpen(string s)
		{
			cout << s << endl;
		}
	};
private:
	ifstream infile;
	ofstream outfile;
	list <char*> blockList;
	int cntBlock = 0, cntOutBlock = 0;
	mutex m1;
	string toHash="";
	int size_block;
	bool EndBlock = false;
};

