#ifndef _WD_CACHE_H
#define _WD_CACHE_H

#include "MutexLock.h"
#include <ext/hash_map>
#include <string>

namespace wd
{
struct MyHashFn
{
	std::size_t operator()(const std::string &str)const
	{
		//使用系统定义的hash函数
		return __gun_cxx::__stl_hash_string(str.c_str());
	}
};

class Cache
{
public:
	typedef __gun_cxx::hash_map<std::string,std::string,MyHashFn> HashMap;
	typedef __gun_cxx::hash_map<std::string,std::string,MyHashFn>::iterator HashMap_it;
	typedef __gun_cxx::hash_map<std::string,std::string,MyHashFn>::const_iterator HashMap_cit;

	Cache(const int num = 100);
	Cache(const Cache &cache);

	void map_to_cache(std::string &key,std::string &value);

	//HashMap_it is_mapped(const std::string *word);

	std::string query_cache(const std::string &word);

	void write_to_file(std::ofstream &fout);

	void read_from_file(const std::string &filename);

	void add_elements(const Cache &cache);
	
private:
	HashMap hashmap_;
	MutexLock mutex_;
};
}//end of namespace
#endif
