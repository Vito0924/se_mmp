#ifndef __JIEBATOOL_H__
#define __JIEBATOOL_H__
#include "Jieba.hpp"
#include "Mypage.h"
#include <string>
#include <map>
#include <vector>
using std::map;
using std::vector;
using std::string;
class JieBaTool
{
public:
	JieBaTool(const char *const DICT_PATH,
		const char *const HMM_PATH,const char *const USER_DICT_PATH,
		const char *const IDF_PATH,const char *const STOP_WORD_PATH)
		:jieba_(DICT_PATH,HMM_PATH,USER_DICT_PATH,IDF_PATH,STOP_WORD_PATH)
	{}
	void segmentWord(string &query,map<string,double> &query_contain);
	void segmentWord(Mypage &mypage);
	void stopWord(vector<string> &stopWord,Mypage &mypage);
private:
	cppjieba::Jieba jieba_;
};

#endif
