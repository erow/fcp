#include "path.h"
#include <stdio.h>
#include <regex> 

vector<string> split(string str, string token) {
	vector<string>result;
	while (str.size()) {
		int index = str.find(token);
		if (index != string::npos) {
			result.push_back(str.substr(0, index));
			str = str.substr(index + token.size());
			if (str.size() == 0)result.push_back(str);
		}
		else {
			result.push_back(str);
			str = "";
		}
	}
	return result;
}

bool belong(string a, string b) {
	vector<string>& p1 = split(a, ":");
	vector<string>& p2 = split(b, ":");
	if (p1[0] != p2[0])
		return false;
	if (p2.size() == 1)
		return true;
	return p1[1] == p2[1];
}

bool inPath(const string target, string path) {
	vector<string>& p1 = split(target, "/");
	vector<string>& p2 = split(path, "/");
	auto ptr = p2.begin();
	for (auto t : p1) {
		if (t.empty())
			continue;
		while (*ptr == "") {
			ptr++;
		}
		if (belong(*ptr, t)) {
			do {
				ptr++;
				if (ptr == p2.end())
					return true;
			} while (*ptr == "");
		}
		else {
			return false;
		}
	}
	return false;
}

void Test() {
	string a, b;
	a = "a:1"; b = "a";
	printf("%s in %s :%d \n", a.c_str(), b.c_str(), belong(a, b));
	a = "/a"; b = "a:0";
	printf("%s in %s :%d \n", a.c_str(), b.c_str(), inPath(a, b));

	a = "/a:0/b:0"; b = "/a:0/b:1";
	printf("%s in %s :%d \n", a.c_str(), b.c_str(), inPath(a, b));
	a = "/a:1/b"; b = "/a:1/b:1";
	printf("%s in %s :%d \n", a.c_str(), b.c_str(), inPath(a, b));
}

using std::regex_match;
using std::regex;
Path::Path()
{

}

Path::Path(const string & path)
{

	m_path = split(path.substr(1), "/");
	regex reg("(\\w|\\d)+:(\\d)+");
	for (auto t : m_path)
	{
		if (!regex_match(t, reg))
		{
			exit(-1);
			m_path.clear();
			return;
		}
	}
}

Path::~Path()
{
}

relType Path::relation(const Path & path)
{
	bool match = true;
	auto vec = path.m_path;
	for (int i = 0; i < m_path.size(); i++)
	{

		if (vec[i] != m_path[i])
			match = false;
		if (!belong(m_path[i], vec[i]))
			return relType::parent;
	}
	if (m_path.size() > vec.size())
		return relType::parent;
	if (vec.size() == m_path.size())
		return match ? relType::self : relType::brother;
	return relType::child;
}

relType Path::relation(const string & abs_uri)
{
	bool match = true;
	auto vec = split(abs_uri,"/");
	vec.erase(vec.begin());
	for (int i = 0; i < m_path.size(); i++)
	{
		if (vec[i] != m_path[i])
			match = false;
		if (!belong(m_path[i], vec[i]))
			return relType::parent;
	}
	if (m_path.size() > vec.size())
		return relType::parent;
	if (vec.size() == m_path.size())
		return match ? relType::self : relType::brother;
	return relType::child;
}

const string Path::abs_uri(const string & uri)
{
	auto path = m_path;
	if (uri[0] == '/')
		return uri;
	else if ((uri.substr(0, 2) == "./")|| (uri.substr(0, 3) == "../")) {
		auto vec = split(uri, "/");
		for (auto t : vec) {
			if (t == "." || t.empty())
				continue;
			else if (t == "..")
				path.pop_back();
			else
				path.push_back(t);
		}
		if (path.size() == 0)
			return "/";
		string absuri;
		for (auto t : path)
			absuri += "/" + t;
		return absuri;
	}
	else {
		string absuri;
		for (auto t : path)
			absuri += "/" + t;
		return absuri + "/" + uri;
	}
}

const string Path::abs_uri()
{
	string absuri;
	for (auto t : m_path)
		absuri += t;
	return "/" + absuri;
}

Path Path::cd(string &)
{
	return Path();
}
