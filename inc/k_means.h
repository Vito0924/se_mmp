#ifndef __K_MEANS_H__
#define __K_MEANS_H__
#include <map>
#include <vector>
using std::map;
using std::vector;
class k_means
{
public:
	k_means(int k)//cluster k class,data dimension 
		:k_(k)
	{}
	//src_tensor.size()所有向量化的数据数量;src_tensor[i].size()向量化数据的维度
	//cluster_result.first=docid，cluster_result.second=所属类
	void do_k_means(vector<vector<double>>& src_tensor,map<int,int>& cluster_result,bool set_flag,int iterate_count);
private:
	int k_;
};
#endif
