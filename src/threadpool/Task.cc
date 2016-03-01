#include "Task.h"
#include "MyDict.h"
#include "Cache.h"
#include <iostream>
#include <unistd.h>

namespace wd
{
size_t nBytesCode(const char ch)
{
	size_t nBytes = 0;
	if(ch & (1<<7))
	{//对中文进行处理-uft8编码
		if((ch & 0xF0) == 0Xc0 || (ch & 0xF0) == 0xD0)
		{
			nBytes += 2;
		}
		else if((ch & 0xF0) == 0xE0)
		{
			nBytes += 3;
		}
		else if((ch & 0xF0) == 0xF0)
		{
			nBytes += 4;
		}
		else if((ch & 0xFF) == 0xF8)
		{
			nBytes += 5;
		}
		else if((ch & 0xFF) == 0xFE)
		{
			nBytes += 6;
		}
	}
	else//1字节编码或者英文
	{
		nBytes += 1;
	}
	return nBytes;
}

std::size_t length(const std::string &str)
{
	std::size_t ilen = 0;
	for(std::size_t idx = 0; idx != str.size(); ++idx)
	{
		int nBytes = nBytesCode(str[]);
		idx += (nBytes - 1);
		++ilen;
	}
	return ilen;
}

int triple_min(const int &a, const int &b, const int &c)
{
	return a<b ? (a<c ? a : c) : (b<c ? b : c);
}

Task::Task(const std::string &expr, int sockfd,MyDict &mydict)
	:expr_(expr),
	 sockfd_(sockfd),
	 mydict_(mydict)
{}

void Task::execute(Cache &cache)//在Cache中查找关键字，如果有发送
{
	std::string str = cache.query_cache(expr_);
	if(str != std::string)//不为空
	{
		int nwrite = write(sockfd_, str.c_str(), str.size());
		if(nwrite == -1)
		{
			std::cout << "responce error" << std::endl;
		}
		std::cout << "from cache responce client: " << str << std::endl;
		return ;
	}

	//如果cache中没有，则要通过计算得到结果
	query_idx_table();
	responce(cache);
}

void Task::query_idx_table()//查看字符串编码方式，并截取出来当前字符，用于索引查找
{
	std::string ch;
	quto idx_table = mydict_.get_index_table();
	for(std::size_t idx = 0; idx != expr_.size(); ++idx)
	{
		size_t nBytes = nBytesCode(expr_[idx]);
		ch = expr_.substr(idx,nBytes);
		if(idx_table.count(ch))
		{
			statistic(idx_table[ch]);
		}
	}
}


void statistic(std::set<int> &set)
{
	auto dict = mydict_.get_dict();
	auto iter = iset.begin();
	for(;iter != iset.end(); ++iter)
	{
		std::string rhs_word = dict[*iter].first;//vector存放的关键字单词，也就是key
		int idist = distance(rhs_word);
		if(idist < 3)
		{
			MyResult res;
			res.idist_ = idist;//最小编辑距离
			res.ifreq_ = dict[*iter].second;//词频，vector的值,也就是value
			que_res_.push(res);//插入优先级队列，会自动排序
		}

	}
}
}//end of namespace 
