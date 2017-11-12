#include "mNode.h"




int DownNode_::handleLocal(const FcpMessage & fcp)
{
	if (fcp.type() == FcpMessage_FcpType_POSTDOWN)
	{
		int find = 0;
		const string& uri = fcp.dst_uri();
		const string& src_uri = fcp.src_uri();
		const string& data = fcp.data();
		for (auto t : m_table) {
			auto path = m_path.abs_uri(t.first);
			if (inPath(uri, path)) {
				t.second->handleMsg(fcp);
				find = 1;
			}
		}

		if (find)
			return 0;
		else
			return -1;
	}
	return -2;
}

DownNode_::DownNode_(const string& deal)
{
	m_deal = deal;
	m_information = "DownNode_";
}


DownNode_::~DownNode_()
{
}


int DownNode_::handleMsg(const FcpMessage & fcp)
{
	const string& uri = fcp.dst_uri();
	int rel = m_path.relation(uri);
	if (rel == (int)relType::parent) {
		FcpMessage t_fcp = fcp;
		t_fcp.set_type(FcpMessage_FcpType_POSTUP);
		sendMsg(t_fcp);
	}
	else if (rel == (int)relType::self) {

	}
	else if (rel == (int)relType::brother) {
		if (fcp.type() == FcpMessage_FcpType::FcpMessage_FcpType_POSTDOWN)
			handleLocal(fcp);
		else
		{
			FcpMessage t_fcp = fcp;
			t_fcp.set_type(FcpMessage_FcpType_POSTUP);
			sendMsg(t_fcp);

		}
	}
	else if (rel == (int)relType::child) {
		FcpMessage t_fcp = fcp;
		t_fcp.set_type(FcpMessage_FcpType_POSTDOWN);
		handleLocal(t_fcp);
	}

	return 0;
}


void DownNode_::unregister(const std::string & uri)
{

}



TopNode_::TopNode_(const string & deal)
{
	m_deal = deal;
	m_information = "TopNode_";
}

TopNode_::~TopNode_()
{
}

int TopNode_::handleMsg(const FcpMessage& msg)
{
	if (msg.type() == FcpMessage_FcpType_POSTDOWN)
	{
		sendMsg(msg);
	}
	//下节点无法处理的消息，转交网关
	else if (true)
	{
		if (m_gateway)
			m_gateway->handleMsg(msg);
	}
	return 0;
}

void TopNode_::setGateway(Node_ * top)
{
	m_gateway = top;
}