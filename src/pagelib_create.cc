#include "pagelib_create.h"
void info_lib_create::text_process()
{
	ofstream ofs(page_lib_path_,std::ios::app);
	if(!ofs.good())
	{
		cerr<<"page_lib open fail"<<endl;
		return;
	}
	ofstream offset(offset_lib_path_,std::ios::app);
	if(!offset.good())
	{
		cerr<<"offset_lib open fail"<<endl;
		return;
	}
	DIR* dir=opendir(source_path_);
	if(NULL==dir)
	{
		perror("dir open error");
		return;
	}
	struct dirent *pdir;
	vector<string> vecStr;
	while((pdir=readdir(dir))!=NULL)
	{
		if(strcmp(pdir->d_name,".")&&strcmp(pdir->d_name,".."))
		{
			string tmp=pdir->d_name;
			vecStr.push_back(tmp);
		}
	}
	vector<string>::iterator it=vecStr.begin();
	for(int idx=1;it!=vecStr.end();++it,++idx)
	{
		string s=string(source_path_)+"/"+*it;
		ifstream ifs(s.c_str());
		string tmp,content;
		while(ifs>>tmp)
		{
			content+=tmp;
		}
		offset<<"docid "<<idx<<","<<"offset "<<ofs.tellp()<<","<<"length "<<content.size()<<endl;
		ofs<<content;

	}
	ofs.close();
	offset.close();
}

