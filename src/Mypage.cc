#include "Mypage.h"
#include <stdlib.h>
Mypage::Mypage(const string &str,int docid)
	:docid_(docid)
	 ,content_(str)
{}
int Mypage::getdocid()const
{
	return docid_;
}
string Mypage::getcontent()const
{
	return content_;
}
