#include "MasterNode.h"

int MasterNode::handleLocal(const FcpMessage & fcp)
{
	return DownNode_::handleLocal(fcp);
}

MasterNode::MasterNode() :
	DownNode_("master")
{
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
	return 0;
}
int MasterNode::handleMsg(const FcpMessage & fcp)
{
	if (fcp.type() == FcpMessage_FcpType_POSTDOWN)
	{
		handleLocal(fcp);
	}
	else if (fcp.type() == FcpMessage_FcpType::FcpMessage_FcpType_POSTUP)
	{
		FcpMessage new_fcp = fcp;
		new_fcp.set_type(FcpMessage_FcpType::FcpMessage_FcpType_POSTDOWN);
		handleLocal(new_fcp);
	}
	else if (fcp.type() == FcpMessage_FcpType::FcpMessage_FcpType_SUBSCRIBE)
	{
		m_subscriber_map[fcp.dst_uri()] = fcp.src_uri();
	}
	else if (fcp.type() == FcpMessage_FcpType::FcpMessage_FcpType_UNSUBSCRIBE)
	{
		m_subscriber_map.erase(fcp.data());
	}
	else if (fcp.type() == FcpMessage_FcpType::FcpMessage_FcpType_EXTPOST)
	{
		auto ptr = m_subscriber_map.find(fcp.dst_uri());
		if (ptr != m_subscriber_map.end()) {
			FcpMessage new_fcp = fcp;
			new_fcp.set_dst_uri(ptr->second);
			new_fcp.set_type(FcpMessage_FcpType::FcpMessage_FcpType_POSTDOWN);
			sendMsg(new_fcp);
		}
	}

	return 0;
}