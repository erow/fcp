#pragma once
#include<string>
#include<vector>
using std::string;
using std::vector;

vector<string> split(string str, string token);
bool belong(string a, string b);
bool inPath(const string target, string path);

enum class relType {
	parent,
	self,
	brother,
	child
};

class Path {
private:
	vector<string> m_path;
public:
	Path();
	//path 需为绝对路径
	Path(const string& path);
	~Path();
	relType relation(const Path& path);
	relType relation(const string& abs_uri);
	const string abs_uri(const string& uri);
	const string abs_uri();
	Path cd(string&);
};