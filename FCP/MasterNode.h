#pragma once
#include<string>
#include<map>
#include<functional>
#include<memory>
#include<vector>
#include "AloneNode.h"
using std::string;
class MasterNode :
	public AloneNode
{
protected:
	std::map<string, string> m_subscriber_map;
	int handleSelf(const json & fcp)
	{
		if (fcp["type"] == FcpMessage_FcpType::FcpMessage_FcpType_Publish)
		{
			Logger->warn("publish to master");
		}
		else if (fcp["type"] == FcpMessage_FcpType::FcpMessage_FcpType_ExtPublish)
		{
			//assert_log(fcp["direction"] == 1);
			Logger->trace("msg \n{}", fcp.dump(2));
			auto ptr = m_subscriber_map.find(fcp["src_uri"]);
			if (ptr != m_subscriber_map.end()) {
				
				json new_fcp ;
				new_fcp["dst_uri"]=(ptr->second);
				new_fcp["src_uri"]=("/");
				new_fcp["direction"]=0;
				new_fcp["data"]=(fcp["data"]);
				handleMsg(new_fcp);
			}
		}
		else if (fcp["type"] == FcpMessage_FcpType::FcpMessage_FcpType_SUBSCRIBE)
		{
			assert_log(fcp["dst_uri"] == "/");
			m_subscriber_map[fcp["data"]] = fcp["src_uri"];
		}
		else if (fcp["type"] == FcpMessage_FcpType::FcpMessage_FcpType_UNSUBSCRIBE)
		{
			assert_log(fcp["dst_uri"] == "/");
			
			m_subscriber_map.erase(fcp["data"].get<std::string>());
		}
		return 1;
	}
	int handleMsg(const json& fcp)
	{
		json new_fcp = fcp;
		new_fcp["direction"]=0;
		return AloneNode::handleMsg(new_fcp);
	}

public:
	MasterNode()
	{
		m_deal = "master";
		m_path;
	}
	~MasterNode()
	{
	}
	
	virtual int sendMsg(const json & msg) {
		Logger->trace_if(msg["direction"] == 0, "({}) sendMsg::{} >>> ", m_path.toString(), msg["type"].get<int>());
		Logger->trace_if(msg["direction"] == 1, "({}) sendMsg::{} <<< ", m_path.toString(), msg["type"].get<int>());
		if (msg["direction"] == 0)
			return handleMsg(msg);
		else
			return m_gateway ? m_gateway->diliverMsg(msg) : -1;
	}
};