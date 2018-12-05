#include "JieBaTool.h"
#include <boost/regex.hpp>
#include <cmath>
using boost::regex;

void JieBaTool::segmentWord(Mypage &mypage)
{
	vector<string> words;
	vector<cppjieba::Word> jiebawords;
	regex reg("\\s*");
	string s=regex_replace(mypage.content_,reg,"");
	jieba_.Cut(s,words,true);
	vector<string>::iterator it;
	for(it=words.begin();it!=words.end();++it)
	{
		if((*it).size()>0)
		{
			if(mypage.wordFreMap_.find(*it)!=mypage.wordFreMap_.end())
			{
				++mypage.wordFreMap_[*it];				
			}
			else
			{
				mypage.wordFreMap_[*it]=1;
			}
		}
	}
}
void JieBaTool::segmentWord(string &query,map<string,double> &query_contain)
{
	vector<string> words;
	vector<cppjieba::Word> jiebawords;
	regex reg("\\s*");
	string s=regex_replace(query,reg,"");
	jieba_.Cut(s,words,true);
	map<string,int> mapTmp;
	for(auto elem:words)
	{
		++mapTmp[elem];
	}
	map<string,int>::iterator it;
	for(it=mapTmp.begin();it!=mapTmp.end();++it)
	{
		double weight=(1+log10(it->second));
		query_contain[it->first]=weight;
	}
	double real_weight=0.0;
	map<string,double>::iterator itt;
	for(itt=query_contain.begin();itt!=query_contain.end();++itt)
	{
		real_weight+=itt->second*itt->second;
	}
	real_weight=sqrt(real_weight);
	for(itt=query_contain.begin();itt!=query_contain.end();++itt)
	{
		itt->second=itt->second/real_weight;
	}
}
void JieBaTool::stopWord(vector<string> &vecStr,Mypage &mypage)
{
	vector<string>::iterator it;
	for(it=vecStr.begin();it!=vecStr.end();++it)
	{
		mypage.wordFreMap_.erase(*it);
	}
}
