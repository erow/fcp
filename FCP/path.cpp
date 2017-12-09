#include "path.h"
#include <stdio.h>
#include <regex> 

void getDigitList(string str, vector<int>& result_list) {
	string tmp;
	for (int i = 0; i < str.size(); i++) {
		if ('0' <= str[i] && str[i] <= '9')
		{
			tmp.push_back(str[i]);
		}
		else {
			if (!tmp.empty())
			{
				result_list.push_back(std::stoi(tmp));
				tmp.clear();
			}
		}
	}
	if (!tmp.empty())
	{
		result_list.push_back(std::stoi(tmp));
		tmp.clear();
	}
}


void PathTest() {
	UriPath a("/a:0");
	assert_log(a.toString("a") == "/a:0/a");
	assert_log(a.toString("/a") == "/a");
	assert_log(a.toString("./a") == "/a:0/a");
	//assert_log(a.toString("../a") == "/a"); not supported for now
	assert_log(relation(NodePath("/a:1"), UriPath("/a")) == (relType::PARENT+ SELF));
	assert_log(relation(NodePath("a:1"), UriPath("/a!1")) == relType::PARENT);
	assert_log(relation(NodePath("/a:1/b:0"), UriPath("/a/b:0")) == (relType::PARENT + SELF));
	assert_log(relation(NodePath("/a:1/b:0"), UriPath("/a/b:0/c")) == (relType::PARENT + CHILD));
	assert_log(relation(NodePath("/a:1/b:0"), UriPath("/a:1/b:0!1")) == relType::SELF);
	assert_log(relation(NodePath("/a:1/b:0"), UriPath("/a:1/b:0!1/c")) == relType::CHILD);

}


//const string Path::toString(const string & uri)
//{
//	auto path = m_path;
//	if (uri[0] == '/')
//		return uri;
//	else if ((uri.substr(0, 2) == "./")|| (uri.substr(0, 3) == "../")) {
//		auto vec = split(uri, "/");
//		for (auto t : vec) {
//			if (t == "." || t.empty())
//				continue;
//			else if (t == "..")
//				path.pop_back();
//			else
//				path.push_back(t);
//		}
//		if (path.size() == 0)
//			return "/";
//		string absuri;
//		for (auto t : path)
//			absuri += "/" + t;
//		return absuri;
//	}
//	else {
//		string absuri;
//		for (auto t : path)
//			absuri += "/" + t;
//		return absuri + "/" + uri;
//	}
//}


