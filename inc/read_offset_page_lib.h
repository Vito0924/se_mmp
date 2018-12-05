#ifndef __READ_OFFSET_PAGE_LIB_H__
#define __READ_OFFSET_PAGE_LIB_H__
#include <vector>
#include "JieBaTool.h"
#include "Mypage.h"
class JieBaTool;
class Mypage;
using std::vector;

class Read_lib
{
public:
	Read_lib(const char *offset_path,const char *page_path)
		:offset_path_(offset_path)
		 ,page_path_(page_path)
	{}
	void mypage_vec_build(vector<Mypage> & vecMypage);
private:
	const char *offset_path_;
	const char *page_path_;

};

#endif
