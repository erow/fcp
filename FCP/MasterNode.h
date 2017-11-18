#pragma once
#include<string>
#include<map>
#include<functional>
#include<memory>
#include<vector>
#include "mNode.h"
using std::string;
class MasterNode :
	public DownNode_
{
protected:
	std::map<string, string> m_subscriber_map;

public:
	MasterNode();
	~MasterNode();
	void unregister(const std::string& uri);

	virtual int handleMsg(const FcpMessage& fcp);
	int Tx(const string&);
};