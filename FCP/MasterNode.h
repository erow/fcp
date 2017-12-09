#pragma once
#include<string>
#include<map>
#include<functional>
#include<memory>
#include<vector>
#include "AlongNode.h"
using std::string;
class MasterNode :
	public AlongNode
{
protected:
	std::map<string, string> m_subscriber_map;
	int handleSelf(const FcpMessage & fcp)
	{
		if (fcp.type() == FcpMessage_FcpType::FcpMessage_FcpType_Publish)
		{
			Logger->warn("publish to master");
		}
		else if (fcp.type() == FcpMessage_FcpType::FcpMessage_FcpType_ExtPublish)
		{
			//assert_log(fcp.direction() == 1);
			Logger->trace("msg \n{}", fcp.DebugString());
			auto ptr = m_subscriber_map.find(fcp.src_uri());
			if (ptr != m_subscriber_map.end()) {
				
				FcpMessage new_fcp ;
				new_fcp.set_dst_uri(ptr->second);
				new_fcp.set_src_uri("/");
				new_fcp.set_direction(0);
				new_fcp.set_data(fcp.data());
				handleMsg(new_fcp);
			}
		}
		else if (fcp.type() == FcpMessage_FcpType::FcpMessage_FcpType_SUBSCRIBE)
		{
			assert_log(fcp.dst_uri() == "/");
			m_subscriber_map[fcp.data()] = fcp.src_uri();
		}
		else if (fcp.type() == FcpMessage_FcpType::FcpMessage_FcpType_UNSUBSCRIBE)
		{
			assert_log(fcp.dst_uri() == "/");
			m_subscriber_map.erase(fcp.data());
		}
		return 1;
	}
	int handleMsg(const FcpMessage& fcp)
	{
		FcpMessage new_fcp = fcp;
		new_fcp.set_direction(0);
		return AlongNode::handleMsg(new_fcp);
	}

public:
	MasterNode();
	~MasterNode();
	
};