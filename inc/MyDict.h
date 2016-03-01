#ifndef _WD_MYDICT_H
#define _WD_MYDICT_H

#include <string>
#include <vector>
#include <set>
#include <map>
#include <utility>

namespace wd
{
class MyDict
{
public:
	static MyDict* createInstance(const char* dix=ctpath, const char* dictpath2);

	std::vector<std::pair<string, int> > &get_gict();
	std::map<std::string, std::set<int> > &get_index_table();

	void show_dict();
	void show_index_table();

private:
	MyDict(const char* dictpath, const char* dictpath2);
	void read_from(const* dictpath);
	void record_to_index(int idx);

private:
	static MyDict *pInstance;
	sts::vector<std::pair<std::string,int> > dict_;
	std::map<std::string, std::set<int> > index_table_;
};
}//end of namespace
#endif
