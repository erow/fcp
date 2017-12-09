#include "MasterNode.h"


MasterNode::MasterNode() 
{
	m_deal = "master";
	m_path;
}


MasterNode::~MasterNode()
{
}

//int MasterNode::handleMsg(const FcpMessage & fcp)
//{
//	if (fcp.type() == FcpMessage_FcpType::FcpMessage_FcpType_Publish)
//	{
//		FcpMessage new_fcp = fcp;
//		new_fcp.set_direction(0);
//		return DownNode_::handleMsg(new_fcp);
//	}
//	else if (fcp.type() == FcpMessage_FcpType::FcpMessage_FcpType_ExtPublish)
//	{
//		assert_log(fcp.direction() == 1);
//		Logger->trace("msg \n{}", fcp.DebugString());
//		auto ptr = m_subscriber_map.find(fcp.dst_uri());
//		if (ptr != m_subscriber_map.end()) {
//			FcpMessage new_fcp = fcp;
//			new_fcp.set_dst_uri(ptr->second);
//			new_fcp.set_direction(0);
//			sendMsg(new_fcp);
//		}
//	}
//	else if (fcp.type() == FcpMessage_FcpType::FcpMessage_FcpType_SUBSCRIBE)
//	{
//		m_subscriber_map[fcp.dst_uri()] = fcp.src_uri();
//	}
//	else if (fcp.type() == FcpMessage_FcpType::FcpMessage_FcpType_UNSUBSCRIBE)
//	{
//		m_subscriber_map.erase(fcp.data());
//	}
//
//	return 0;
//}