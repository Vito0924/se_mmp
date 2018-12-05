#include "k_means.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
using std::pair;
void k_means::do_k_means(vector<vector<double>>& src_tensor,map<int,int>& cluster_result,bool set_flag,int iterate_count=0)
{
	const int tensor_sum=src_tensor.size();
	const int tensor_dimension=src_tensor[0].size();
//	std::cout<<tensor_sum<<" "<<tensor_dimension<<std::endl;
	double **center=new double *[k_];
	int i,j;
	for(i=0;i<k_;++i)
	{
		center[i]=new double[tensor_dimension];
	}
	srand(time(NULL));
	//找k个随机点
	int *rand_center=new int[k_]();
	for(i=0;i<k_;++i)
	{
		rand_center[i]=rand()%tensor_sum;
//		std::cout<<rand_center[i]<<std::endl;
	}
	//保存k个随机点向量的分量值
	for(i=0;i<k_;++i)
	{
		for(j=0;j<tensor_dimension;++j)
		{
			center[i][j]=src_tensor[rand_center[i]][j];
	//		std::cout<<center[i][j]<<" ";
		}
//		std::cout<<std::endl;
	}
	bool flag=true;
	
	int count=1;
	while(flag)
	{
		if(set_flag)
		{
			if(iterate_count<=0)
			{
				break;
			}
			else
			{
				--iterate_count;
			}
		}
		std::cout<<count++<<std::endl;
	//	--;
		flag=false;
		//开始聚类，当遇到每一簇的质心值改变时，flag为true；
		for(i=0;i<tensor_sum;++i)
		{
			map<double,int> save_tmp_distance;
			for(j=0;j<k_;++j)
			{
				double distance=0.0;
				for(int k=0;k<tensor_dimension;++k)
				{
					distance=distance+(center[j][k]-src_tensor[i][k])*(center[j][k]-src_tensor[i][k]);

				}
				save_tmp_distance.insert(std::make_pair(distance,j));
			}
			cluster_result.insert(std::make_pair(i,save_tmp_distance.begin()->second));
		}
		//计算新的质心
		map<int,int>::iterator mapIt;
		for(i=0;i<k_;++i)
		{
			int count=0;
			double *newcenter=new double[tensor_dimension]();
			for(mapIt=cluster_result.begin();mapIt!=cluster_result.end();++mapIt)
			{
				if(mapIt->second==i)
				{
					++count;
					for(j=0;j<tensor_dimension;++j)
					{
						newcenter[j]+=src_tensor[mapIt->first][j];
					}	
				}
			}
			for(j=0;j<tensor_dimension;++j)
			{
				if(center[i][j]!=newcenter[j]/count)
				{
					flag=true;
					center[i][j]=newcenter[j]/count;
				}
			}
			delete [] newcenter;
		}

	}	
	for(i=0;i<k_;++i)
	{
		delete [] center[i];
	}
	delete [] center;
	delete [] rand_center;
}
