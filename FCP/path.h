#pragma once
#include<string>
#include<vector>
#include<regex>
#include <spdlog\spdlog.h>
#define assert_log(condition) spdlog::get("fcp")->error_if(!(condition), "{}:{} expression:: " #condition,__FILE__,__LINE__),assert(condition)
using std::string;
using std::vector;
/*
node_name :: [a-z]\\w*:\\d+(\\|\\d+)*
uri_name  :: [a-z]\\w*(:\\d+(\\|\\d+)*)?(!\\d+(\\|\\d+)*)?
node_path :: (/node_name)+|/
uri_path  :: (/uri_name)+|/
*/
void getDigitList(string str, vector<int>& result_list);
static std::regex reg_node_name("[a-z]\\w*:\\d+(\\|\\d+)*");
static std::regex reg_uri_name("[a-z]\\w*(:\\d+(\\|\\d+)*)?(!\\d+(\\|\\d+)*)?");
enum relType {
	SELF=1,
	PARENT=2,
	CHILD=4
};
class node_name {
public:
	string m_name;
	int m_num;

	node_name(const string& name) {
		assert_log(std::regex_match(name, reg_node_name));
		int index = name.find_first_of(':');
		m_name = name.substr(0, index);
		m_num = std::stoi(name.substr(index + 1));
	}

	string toString() {
		return m_name + ":" + std::to_string(m_num);
	}
};

class uri_name {
public:
	string m_name;
	vector<int> include_list, exclude_list;
	uri_name(const string& name) {
		std::smatch base_match;
		assert_log(std::regex_match(name, base_match, reg_uri_name));
		std::regex_search(name, base_match, std::regex("[a-z]\\w*"));
		m_name = base_match[0];
		regex_search(name, base_match, std::regex(":\\d+(\\|\\d+)*"));
		getDigitList(base_match.str(), include_list);
		regex_search(name, base_match, std::regex("!\\d+(\\|\\d+)*"));
		getDigitList(base_match.str(), exclude_list);
	}
	string toString() const {
		string str = m_name;
		auto ptr = include_list.begin();
		if (ptr != include_list.end()) {
			str += ":" + std::to_string(*ptr++);
			while (ptr != include_list.end())
			{
				str += "|" + std::to_string(*ptr++);
			}
		}
		ptr = exclude_list.begin();
		if (ptr != exclude_list.end())
		{
			str += "!" + std::to_string(*ptr++);
			while (ptr != exclude_list.end())
			{
				str += "|" + std::to_string(*ptr++);
			}
		}
		
		return str;
	}
	bool is_include(const node_name& n) const {
		if (n.m_name != m_name)
			return false;
		for (auto t : exclude_list)
			if (t == n.m_num)	return false;
		if (include_list.empty())
			return true;
		else {
			for (auto t : include_list)
				if (t == n.m_num) return true;
			return false;
		}
	}
	bool is_include(int n) const {
		for (auto t : exclude_list)
			if (t == n)	return false;
		if (include_list.empty())
			return true;
		else {
			for (auto t : include_list)
				if (t == n) return true;
			return false;
		}
	}
	void exclude(int n) {
		exclude_list.push_back(n);
	}
	
};
static bool operator==(const node_name& n, const uri_name& uri) {
	if (uri.include_list.size() == 1 && n.m_name == uri.m_name&&uri.include_list[0] == n.m_num)
		return true;
	else
		return false;
}
/*
node_name :: name:num
node_uri :: name[:num[|num..]] [!num[|num..]]

*/
template <class T>
class Path {
protected:
	vector<T> m_path;
public:
	Path() {}
	//path ��Ϊ����·��
	Path(const string& path) {
		string str;
		for (char c : path) {
			if (c == '/')
			{
				if (!str.empty())
					m_path.push_back(T(str));
				str = "";
			}
			else
				str += c;
		}
		if (!str.empty())
			m_path.push_back(T(str));
	}
	~Path() {}
	const T& operator[](int i) const{
		return m_path[i];
	}
	T* get(int i) {
		return &m_path[i];
	}
	size_t size() const {
		return m_path.size();
	}
	const string toString(const string& uri = "") {
		string str = "";
		for (auto t : m_path)
			str += "/" + t.toString();

		if (uri.empty())
			return str.empty() ? "/" : str;
		if (uri[0] == '.')
		{
			return str + "/" + uri.substr(2);
		}
		else if (uri[0] == '/')
			return uri;
		else
			return str + "/" + uri;
	}

	friend int relation(const Path<node_name>& node_path, const Path<uri_name>& uri_path);
};

typedef Path<node_name> NodePath;
typedef Path<uri_name> UriPath;

/*
possible value = (relType::PARENT+CHILD),(relType::PARENT+SELF),(relType::CHILD),(relType::PARENT),SELF
*/
static int relation(const Path<node_name>& node_path,const Path<uri_name>& uri_path) {
	bool match = true;
	if (uri_path.size() >= node_path.size()) {
		for(int i=0;i<node_path.size();i++)
			if (!(node_path[i] == uri_path[i]))
			{
				match = false; 
				break;
			}
		if (match)
			return uri_path.size() == node_path.size()?SELF:CHILD;
	}

	match = true;
	for (int i = 0; i < node_path.size(); i++)
	{
		if (i >= uri_path.size())
			return relType::PARENT;
		if (!uri_path[i].is_include(node_path[i]))
		{
			match = false;
		}
	}
	if(node_path.size() == uri_path.size())
		return match? relType::PARENT + relType::SELF : relType::PARENT;
	else if (node_path.size() < uri_path.size())
		return match ? relType::PARENT + relType::CHILD : relType::PARENT;
	else
		return relType::PARENT;
	
}
static bool is_include(const Path<node_name>& node_path, const Path<uri_name>& uri_path) {
	for (int i = 0; i < uri_path.size(); i++)
	{
		if (i >= node_path.size())
			break;
		if (!uri_path[i].is_include(node_path[i]))
		{
			return false;
		}
	}
	return true;
}

void PathTest();