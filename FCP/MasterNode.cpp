#include "MasterNode.h"


//int MasterNode::handleMsg(const json & fcp)
//{
//	if (fcp.type() == FcpMessage_FcpType::FcpMessage_FcpType_Publish)
//	{
//		json new_fcp = fcp;
//		new_fcp["direction"]=0;
//		return DownNode_::handleMsg(new_fcp);
//	}
//	else if (fcp.type() == FcpMessage_FcpType::FcpMessage_FcpType_ExtPublish)
//	{
//		assert_log(fcp["direction"] == 1);
//		Logger->trace("msg \n{}", fcp.DebugString());
//		auto ptr = m_subscriber_map.find(fcp.dst_uri());
//		if (ptr != m_subscriber_map.end()) {
//			json new_fcp = fcp;
//			new_fcp["dst_uri"](ptr->second);
//			new_fcp["direction"]=0;
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