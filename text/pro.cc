#include <iostream>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
int main()
{
	ifstream ifs("./comp");
	string tmp;
	string name;
	vector<string> vecstr;
	while(getline(ifs,tmp))
	{
		auto len=tmp.find(":");
		len=len-5;
		name=tmp.substr(5,len);
		vecstr.push_back(name);

	}
	string src;
	for (auto elem:vecstr)
	{
		tmp=string("./chi_text/")+elem;
		src=string("./joke/")+elem;
		rename(src.c_str(),tmp.c_str());
	}
	return 0;
}
