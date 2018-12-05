#include "Jieba.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
using std::ifstream;
using std::cout;
using std::endl;
using std::vector;
using std::string;
int main()
{
	ifstream stop("../chi_stop_word.txt");
	vector<string> vec_stop;
	string strstop;
	while(stop>>strstop)
	{
		vec_stop.push_back(strstop);
	}
	string tmp;
	string tmp1;
	ifstream ifs("../text/chi_text/100.txt");
	while(ifs>>tmp1)
	{
		tmp+=tmp1;
	}
	const char *const DICT_PATH="./dict/jieba.dict.utf8";
	const char *const HMM_PATH="./dict/hmm_model.utf8";
	const char *const USER_DICT_PATH="./dict/user.dict.utf8";
	const char *const IDF_PATH="./dict/idf.utf8";
	const char *const STOP_WORD_PATH="./dict/stop_words.utf8";
	
	cppjieba::Jieba jieba(DICT_PATH,HMM_PATH,USER_DICT_PATH,IDF_PATH,STOP_WORD_PATH);
	vector<string> words;
	jieba.Cut(tmp,words,true);
	for(auto elem:words)
	{
		if(std::find(vec_stop.begin(),vec_stop.end(),elem)==vec_stop.end()){
		cout<<elem<<"/";
		}
	}
	cout<<endl;
	return 0;


}
