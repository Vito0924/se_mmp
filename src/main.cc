#include "pagelib_create.h"
#include "Mypage.h"
#include "JieBaTool.h"
#include "read_offset_page_lib.h"
#include <unordered_map>
#include <cmath>
#include <set>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <k_means.h>
using std::cin;
using std::set;
using std::unordered_map;
using std::pair;
const char* conf_path="/home/vito/se_mmp/path.conf";
const char* chi_stop_path="/home/vito/se_mmp/chi_stop_word.txt";
const char* eng_stop_path="/home/vito/se_mmp/eng_stop_word.txt";
const char* const dict_path="/home/vito/se_mmp/cppjieba/dict/jieba.dict.utf8";
const char* const hmm_path="/home/vito/se_mmp/cppjieba/dict/hmm_model.utf8";
const char* const user_dict_path="/home/vito/se_mmp/cppjieba/dict/user.dict.utf8";
const char* const idf_path="/home/vito/se_mmp/cppjieba/dict/idf.utf8";
const char* const stop_word_path="/home/vito/se_mmp/cppjieba/dict/stop_words.utf8";
void create_stopword_vec(const char *file_path,vector<string> & vecWord)
{
	ifstream ifs(file_path);
	if(!ifs.good())
	{
		std::cerr<<"open stop_word file fail"<<std::endl;
	}
	string tmp;
	while(ifs>>tmp)
	{
		vecWord.push_back(tmp);
	}
}
void create_weight(vector<Mypage> & page,unordered_map<string,vector<pair<int,double>>> & indexWeight)
{
	vector<Mypage>::iterator itMypage;
	auto N=page.size();
	double tf;
	for(itMypage=page.begin()+1;itMypage!=page.end();++itMypage)
	{
		map<string,int>::iterator it;
		for(it=(*itMypage).wordFreMap_.begin();it!=(*itMypage).wordFreMap_.end();++it)
		{
			tf=1+log10(it->second);
			pair<int,double> tmppair=std::make_pair((*itMypage).getdocid(),tf);
			indexWeight[it->first].push_back(tmppair);
		}
	}
	unordered_map<string,vector<pair<int,double>>>::iterator itWeight;
	for(itWeight=indexWeight.begin();itWeight!=indexWeight.end();++itWeight)
	{
		double idf=log10(N/itWeight->second.size());
		vector<pair<int,double>>::iterator vecpair;
		for(vecpair=itWeight->second.begin();vecpair!=itWeight->second.end();++vecpair)
		{
			(*vecpair).second=(*vecpair).second*idf;

		}

	}

}
double compare_two_text(vector<Mypage> & page,int docid1,int docid2)
{
	double similar=0;
	int len1=page[docid1].word_weight_.size();
	int len2=page[docid2].word_weight_.size();
	bool flag=len1>len2?false:true;
	map<string,double>::iterator it;
	int a[2];
	if(flag)
	{
		a[0]=docid1;
		a[1]=docid2;
	}
	else
	{
		a[0]=docid2;
		a[1]=docid1;
	}

	for(it=page[a[0]].word_weight_.begin();it!=page[a[0]].word_weight_.end();++it)
	{
		auto itt=page[a[1]].word_weight_.find(it->first);
		if(itt!=page[a[1]].word_weight_.end())
		{
			similar=similar+it->second*itt->second;
		}
		else
		{
			similar+=0;
		}
	}
	cout<<"第一篇文档是:"<<endl<<page[docid1].getcontent()<<endl;
	cout<<"第二篇文档是:"<<endl<<page[docid2].getcontent()<<endl;
	cout<<"余弦相似度是:"<<endl;
	return similar;
}
/*bool compByVal(pair<int,double> &lhs,pair<int,double> &rhs)
{
	return lhs.second>rhs.second;
}*/
void search_engine(map<string,double> &query_contain,unordered_map<string,vector<pair<int,double>>>& index,vector<Mypage> & mypage)
{
//	bool compByVal(pair<int,double>&,pair<int,double>&);
	map<int,double> result;
	map<string,double>::iterator query_it;
	for(query_it=query_contain.begin();query_it!=query_contain.end();++query_it)
	{
		if(index.find(query_it->first)!=index.end())
		{
			vector<pair<int,double>>::iterator vecIt;
			for(vecIt=index[query_it->first].begin();vecIt!=index[query_it->first].end();++vecIt)
			{
//				cout<<query_it->second<<endl;
//				cout<<vecIt->second<<endl;
				result[vecIt->first]=result[vecIt->first]+query_it->second*vecIt->second;
			//	cout<<result[vecIt->first]<<endl<<endl;
			}
		}
	}
//	sort(result.begin(),result.end(),compByVal);
	if (result.size()>0)
	{
	map<int,double>::iterator res_it;
	for(res_it=result.begin();res_it!=result.end();++res_it)
	{
		cout<<"文档号是:"<<" "<<res_it->first<<endl;
		cout<<"内容是:"<<endl;
		cout<<mypage[res_it->first].getcontent()<<endl;
		cout<<"余弦相似度是: "<<res_it->second<<endl;
	}
	}
	else
	{
		cout<<"not exit"<<endl;
	}
	
}
void build_tensor(vector<Mypage> &page,vector<vector<double>> & src_tens)
{
	set<string> title;
	vector<Mypage>::iterator pageIt;
	map<string,int>::iterator mapIt;
	for(mapIt=page[0].wordFreMap_.begin();mapIt!=page[0].wordFreMap_.end();++mapIt)
	{
		title.insert(mapIt->first);
	}
	set<string>::iterator setIt;

	for(pageIt=page.begin()+1;pageIt!=page.end();++pageIt)
	{
		vector<double> value;
		int i;
		for(i=0,setIt=title.begin();setIt!=title.end();++setIt,++i)
		{
			if(pageIt->word_weight_.find(*setIt)!=pageIt->word_weight_.end())
			{
				value.push_back(pageIt->word_weight_.find(*setIt)->second);
			}
			else 
			{
				value.push_back(0.0);
			}
		}
		src_tens.push_back(value);
	}

}
int main()
{
	ifstream path_extract(conf_path);
	string src_chi_path;
	string pageLibPath;
	string offsetLibPath;
	string tmp;
	while(getline(path_extract,tmp))
	{
		if(tmp.find("source_path")!=string::npos)
		{
			src_chi_path=tmp.substr(tmp.find(":")+1);
//			cout<<src_chi_path<<endl;
		}
		else if(tmp.find("page_lib_path")!=string::npos)
		{
			pageLibPath=tmp.substr(tmp.find(":")+1);

		}
		else if(tmp.find("offset_lib_path")!=string::npos)
		{
			offsetLibPath=tmp.substr(tmp.find(":")+1);
		}
	/*	else if(tmp.find("DICT_PATH")!=string::npos)
		{
			dict_path=tmp.substr(tmp.find(":")+1);
		}
		else if(tmp.find("HMM_PATH")!=string::npos)
		{
			hmm_path=tmp.substr(tmp.find(":")+1);
		}
		else if(tmp.find("USER_DICT_PATH")!=string::npos)
		{
			user_dict_path=tmp.substr(tmp.find(":")+1);
		}
		else if(tmp.find("IDF_PATH")!=string::npos)
		{
			idf_path=tmp.substr(tmp.find(":")+1);
		}
		else if(tmp.find("STOP_WORD_PATH")!=string::npos)
		{
			stop_word_path=tmp.substr(tmp.find(":")+1);
		}
		*/
	}
	vector<string> vecStopword;
	create_stopword_vec(chi_stop_path,vecStopword);

	info_lib_create libcreate(src_chi_path.c_str(),pageLibPath.c_str(),offsetLibPath.c_str());
	libcreate.text_process();

	Read_lib read_lib(offsetLibPath.c_str(),pageLibPath.c_str());
	vector<Mypage> mypage;
	read_lib.mypage_vec_build(mypage);
	vector<Mypage>::iterator it;
	JieBaTool jieba_tool(dict_path,hmm_path,user_dict_path,idf_path,stop_word_path);
	for(it=mypage.begin();it!=mypage.end();++it)
	{   	
		jieba_tool.segmentWord(*it);
		jieba_tool.stopWord(vecStopword,*it);
	}
/*	for(it=mypage.begin();it!=mypage.begin()+1;++it)
	{
		map<string,int>::iterator mapIt;
		for(mapIt=(*it).wordFreMap_.begin();mapIt!=(*it).wordFreMap_.end();++mapIt)
		{
			cout<<mapIt->first<<" "<<mapIt->second<<endl;
		}
	}*/
	unordered_map<string,vector<pair<int,double>>> index;
	create_weight(mypage,index);
	unordered_map<string,vector<pair<int,double>>>::iterator unit;
	for(unit=index.begin();unit!=index.end();++unit)
	{
	//	cout<<unit->first<<endl;
		vector<pair<int,double>>::iterator ittmp;
		for(ittmp=unit->second.begin();ittmp!=unit->second.end();++ittmp)
		{
			mypage[ittmp->first].word_weight_[unit->first]=ittmp->second;
		//	cout<<ittmp->first<<" "<<ittmp->second<<endl;
		}
	}
	vector<Mypage>::iterator newPagevecIt;
//	double real_weight=0.0;
	for(newPagevecIt=mypage.begin();newPagevecIt!=mypage.end();++newPagevecIt)
	{
		double total=0.0;
		map<string,double>::iterator mapIt;
		for(mapIt=(*newPagevecIt).word_weight_.begin();mapIt!=(*newPagevecIt).word_weight_.end();++mapIt)
		{
			total+=mapIt->second*mapIt->second;
		}
		total=sqrt(total);
		for(mapIt=(*newPagevecIt).word_weight_.begin();mapIt!=(*newPagevecIt).word_weight_.end();++mapIt)
		{
			mapIt->second=mapIt->second/total;

		}

	}
	for(unit=index.begin();unit!=index.end();++unit)
	{
		vector<pair<int,double>>::iterator it;
		for(it=unit->second.begin();it!=unit->second.end();++it)
		{
			it->second=mypage[it->first].word_weight_[unit->first];
		}
	}
	while(1)
	{
	cout<<"--------------------请选择功能:--------------------"<<endl;
	cout<<"-------------按 1 查询文本相似度查询;--------------"<<endl;
	cout<<"-----------------按 2 进行文本搜索;----------------"<<endl;
	cout<<"-------------按 3 进行文本k_means 聚类-------------"<<endl;
	cout<<"---------------按其他任意键退出系统.---------------"<<endl;
	int i;
	scanf("%d",&i);


	switch(i)
	{
	case 1:
		{
			system("clear");
			cout<<"请输入1-500任意两个文档号:"<<endl;
			int docid1,docid2;
			scanf("%d,%d",&docid1,&docid2);
			cout<<compare_two_text(mypage,docid1,docid2)<<endl;
			break;
		}
	case 2:
		{
			getchar();
			system("clear");
			cout<<"请输入关键词："<<endl;
			string query;
			getline(cin,query);
			map<string,double> query_contain;
			jieba_tool.segmentWord(query,query_contain);
//			map<string,double>::iterator it;
//			for(it=query_contain.begin();it!=query_contain.end();++it)
//			{
//				cout<<it->first<<" "<<it->second<<endl;
//			}
			search_engine(query_contain,index,mypage);
			break;
		}
	case 3:
		{
			cout<<"请输入要聚类的个数："<<endl;
			int i;
			int j;
			int k=0;
			scanf("%d",&i);
			cout<<"请选择是否设置迭代次数(输入1，设置迭代；输入0，不设置迭代)："<<endl;
			scanf("%d",&j);
			if(j==1)
			{
				cout<<"请输入要迭代的次数:"<<endl;
				scanf("%d",&k);	
			}
			vector<vector<double>> src_tens;
			map<int,int> cluster_result;		
			build_tensor(mypage,src_tens);	
			k_means my_kmeans(i);
/*			ofstream ofs("../tensor_data.txt",std::ios::out);
			for(auto & elem:src_tens)
			{
				for(auto elem1:elem)
				{
					ofs<<elem1<<" ";
				}
				ofs<<endl;
			}*/
			my_kmeans.do_k_means(src_tens,cluster_result,j,k);
			map<int,int>::iterator mapIt;
			map<int,vector<int>> mul_map;
			for(mapIt=cluster_result.begin();mapIt!=cluster_result.end();++mapIt)
			{
				cout<<"文档号: "<<mapIt->first+1<<"类号: "<<mapIt->second+1<<endl;
			//	mul_map[mapIt->second+1].push_back(mapIt->first+1);

			}
/*			map<int,int> max_three_class;
			map<int,vector<int>>::iterator mulIt;
			for(mulIt=mul_map.begin();mulIt!=mul_map.end();++mulIt)
			{
				max_three_class.insert(std::make_pair(mulIt->second.size(),mulIt->first));
			}
			auto ittt=--max_three_class.end();
			--ittt;
			--ittt;
			for(int i=0;i<3;++i)
			{
				for(auto & elem:mul_map[ittt->second])
				{
					cout<<"类号："<<ittt->second<<"文档号"<<elem<<" ";
				}
				++ittt;
				cout<<endl;
			}
*/
		//	vector<vector<double>>::iterator tmpIt;
		//	cout<<src_tens.size();
		//	for(tmpIt=src_tens.begin();tmpIt!=src_tens.end();++tmpIt)
		//	{
		//		cout<<"dimension "<<(*tmpIt).size()<<endl;
	//			for(auto elem:*tmpIt)
	//			{
	//				cout<<elem<<" ";
	//			}
		//	}
			break;
		}
	default:exit(0);
	}
	}	
	return 0;
}
