#include "MyDict.h"
#include <iostream>

namespace wd
{
MyDict *MyDict::pInstance = NULL;

MyDict* MyDict::createInstance(const char* dictpath, const char* dictpath2)
{
	if(NULL == pInstance)
	{
		pInstance = new MyDict(dictpath,dictpath2);
	}
	return pInstance;
}

std::vector<std::pair<std::string, int> > &MyDict::get_dict()
{
	return dict_;
}

std::map<std::string, std::set<int> > &MyDict::get_index_tab()
{
	return index_table_;
}

void MyDict::show_dict()
{
	auto iter = dict_.begin();
	for(; iter != dict_.end(); ++iter)
	{
		std::cout << iter->first << "-->"
				  << iter->second << std::endl;
	}
}

void MyDict::show_index_table()
{
	auto iter = index_table_.begin();
	for(; iter != index_table_.end(); ++iter)
	{
		std::cout << iter->first << "-->";
		auto sit = iter->second.begin();
		for(; sit != iter->second.end(); ++sit)
		{
			std::cout << *sit << " ";
		}
		std::cout << std::endl;
	}
}

void 
}//end o namespace


