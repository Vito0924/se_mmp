#include "Mypage.h"
#include "read_offset_page_lib.h"
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <stdlib.h>
using std::endl;
using std::cerr;
using std::ifstream;
void Read_lib::mypage_vec_build(vector<Mypage> & vecMypage)
{
	ifstream offset_lib(offset_path_);
	if(!offset_lib.good())
	{
		cerr<<"offset_lib open fail"<<endl;
		return;
	}
	ifstream page_lib(page_path_);
	if(!page_lib.good())
	{
		cerr<<"page_lib open fail"<<endl;
		return;
	}
	page_lib.seekg(0,page_lib.end);
	int total=page_lib.tellg();
	page_lib.seekg(0,page_lib.beg);
	char *tmp=new char[total];
	if(page_lib.is_open())
	{
		page_lib.read(tmp,total);
	}
	string offset_line;
	Mypage total_page_info(tmp,0);
	vecMypage.push_back(total_page_info);
	while(getline(offset_lib,offset_line))
	{
		unsigned int len;
		len=offset_line.find("offset");
		string strdocid=offset_line.substr(6,len-7);
		len=offset_line.find("length")-offset_line.find("offset")-8;
		string stroffset=offset_line.substr(offset_line.find("offset")+7,len);
		string strlength=offset_line.substr(offset_line.find("length")+7);
		int intdocid=strtod(&strdocid[0],NULL);
		int intoffset=strtod(&stroffset[0],NULL);
		int intlength=strtod(&strlength[0],NULL);
//		std::cout<<intoffset<<std::endl;
		string buffer(tmp,intoffset,intlength);
		Mypage mypage(buffer,intdocid);
		vecMypage.push_back(mypage);
	}
	delete [] tmp;
	offset_lib.close();
	page_lib.close();
}
