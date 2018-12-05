#ifndef __PAGELIB_CREATE_H__
#define __PAGELIB_CREATE_H__
#include <sys/stat.h>
#include <sys/types.h>
#include <cstring>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

using std::stringstream;
using std::vector;
using std::cout;
using std::endl;
using std::string;
using std::ofstream;
using std::ifstream;
using std::cerr;

//static int id=1;

class info_lib_create
{
public:
	info_lib_create(const char *source_path,const char *page_lib_path,const char *offset_lib_path)
		:source_path_(source_path)
		,page_lib_path_(page_lib_path)
		,offset_lib_path_(offset_lib_path)
	{}
	void text_process();
private:
	const char* source_path_;
	const char* page_lib_path_;
	const char* offset_lib_path_;
	
};

#endif
