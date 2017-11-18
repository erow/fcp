#include "MasterNode.h"


MasterNode::MasterNode() 
{
	m_deal = "master";
	m_path;
}


MasterNode::~MasterNode()
{
}



void MasterNode::unregister(const std::string & uri)
{
	//m_table.erase(uri);
}

int MasterNode::Tx(const string &data) {
	return Rx(data);
}
int MasterNode::handleMsg(const FcpMessage & fcp)
{
	if (fcp.type() == FcpMessage_FcpType::FcpMessage_FcpType_Publish)
	{

		return DownNode_::handlePublish(fcp);
	}

	else if (fcp.type() == FcpMessage_FcpType::FcpMessage_FcpType_ExtPublish)
	{
		assert(fcp.direction() == 1);

		auto ptr = m_subscriber_map.find(fcp.dst_uri());
		if (ptr != m_subscriber_map.end()) {
			FcpMessage new_fcp = fcp;
			new_fcp.set_dst_uri(ptr->second);
			new_fcp.set_direction(0);
			sendMsg(new_fcp);
		}
	}
	else if (fcp.type() == FcpMessage_FcpType::FcpMessage_FcpType_SUBSCRIBE)
	{
		m_subscriber_map[fcp.dst_uri()] = fcp.src_uri();
	}
	else if (fcp.type() == FcpMessage_FcpType::FcpMessage_FcpType_UNSUBSCRIBE)
	{
		m_subscriber_map.erase(fcp.data());
	}

	return 0;
}