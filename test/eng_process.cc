#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;
int main()
{
	ifstream text("./eng.txt");
	string tmp;
	vector<string> word;
	while(text>>tmp)
	{
		word.push_back(tmp);
	}
	ifstream stop("../eng_stop_word.txt");
	vector<string> stopword;
	while(stop>>tmp)
	{
		stopword.push_back(tmp);
	}
	for(auto elem:word)
	{
		if(find(stopword.begin(),stopword.end(),elem)==stopword.end())
		{
			cout<<elem<<" ";
		}
	}
	cout<<endl;
}
