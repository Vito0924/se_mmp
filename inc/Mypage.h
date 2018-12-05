#ifndef __MYPAGE_H__
#define __MYPAGE_H__
#include <string>
#include <map>
using std::map;
using std::string;
class JieBaTool;
class Read_lib;
class Mypage
{
	friend class JieBaTool;
	friend class Read_lib;
public:
	Mypage(const string &str,int docid);
	int getdocid()const;
	string getcontent()const;
private:
	int docid_;
	string content_;
public:
	map<string,int> wordFreMap_;
	map<string,double> word_weight_;
};

#endif 
