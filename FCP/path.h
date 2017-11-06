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
	//path ��Ϊ����·��
	Path(const string& path);
	~Path();
	int relation(const Path& path);
	int relation(const string& abs_uri);
	const string abs_uri(const string& uri);
	const string abs_uri();
	Path cd(string&);
};