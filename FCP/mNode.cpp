#include "mNode.h"




int DownNode_::handlePublish(const FcpMessage & fcp)
{
	assert(fcp.type() == FcpMessage_FcpType::FcpMessage_FcpType_Publish);
	{
		int find = 0;
		const string& uri = fcp.dst_uri();
		const string& src_uri = fcp.src_uri();
		const string& data = fcp.data();
		for (auto t : m_table) {
			auto path = m_path.abs_uri(t.first);
			if (inPath(uri, path)) {
				Logger->debug("{}/{}>>>{}", m_deal, fcp.type(), t.first);
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

int DownNode_::handleLocal(const FcpMessage & fcp)
{
	if (FcpMessage_FcpType::FcpMessage_FcpType_Publish == fcp.type())
		return handlePublish(fcp);

	return -1;
}

DownNode_::DownNode_()
{
	m_deal = "un init";
	m_information = "DownNode_";
}


DownNode_::~DownNode_()
{
}

/*
�����ж��յ�����Ϣ�Ƿ������Լ�������������handlePublish
/a:0/a �� brother /a:0/a:*

*/
int DownNode_::handleMsg(const FcpMessage & fcp)
{
	const string& uri = fcp.dst_uri();
	int rel = m_path.relation(uri);

	if (rel == (int)relType::parent) {
		sendMsg(fcp);
	}
	else if (rel == (int)relType::self) {
		handleLocal(fcp);
	}
	//���Լ��븸���й�
	else if (rel == (int)relType::brother) {
		handleLocal(fcp);
		if (fcp.direction() == 1)
			sendMsg(fcp);
	}
	//���Լ��޹أ�ֻ�뺢���й�
	else if (rel == (int)relType::child) {
		FcpMessage t_fcp = fcp;
		t_fcp.set_direction(0);
		handleLocal(t_fcp);
	}

	return 0;
}

inline int DownNode_::sendMsg(const FcpMessage & msg)
{
	Logger->debug("<<<{}/{}",  m_deal,msg.type());
	assert(msg.direction() == 1);
	auto data = msg.SerializeAsString();
	return Tx(std::to_string(data.size()) + ":" + data);
}


void DownNode_::unregister(const std::string & uri)
{

}



TopNode_::TopNode_()
{
	m_deal = "un init";
	m_information = "TopNode_";
}

TopNode_::~TopNode_()
{
}

int TopNode_::handleMsg(const FcpMessage& msg)
{
	if (msg.direction() == 0)
	{
		sendMsg(msg);
	}
	//�½ڵ��޷��������Ϣ��ת������
	else 
	{
		if (m_gateway)
			m_gateway->handleMsg(msg);
	}
	return 0;
}

int TopNode_::sendMsg(const FcpMessage & msg)
{
	Logger->debug("{}/{}>>>", m_deal, msg.type());
	assert(msg.direction() == 0);
	auto data = msg.SerializeAsString();
	return Tx(std::to_string(data.size()) + ":" + data);
}

void TopNode_::setGateway(Node_ * top)
{
	m_gateway = top;
}