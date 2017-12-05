#include "mNode.h"
#include "Node_.h"

//int DownNode_::handlePublish(const FcpMessage & fcp)
//{
//	assert_log(fcp.type() == FcpMessage_FcpType::FcpMessage_FcpType_Publish);
//	assert_log(fcp.direction() == 0);
//	int find = 0;
//	const string& uri = fcp.dst_uri();
//	const string& src_node = fcp.src_node();
//	const string& data = fcp.data();
//	for (auto t : m_table) {
//		auto path = m_path.toString(t.first);
//		if (include(m_path,UriPath(path))) {
//			Logger->debug("{}::{}>>>{}", m_path.toString(), "publish", path);
//			t.second->handleMsg(fcp);
//			find = 1;
//		}
//	}
//	if (find)
//		return 1;
//	else
//		return 0;
//
//}

int DownNode_::handleChild(const FcpMessage & fcp)
{
	FcpMessage new_fcp = fcp;
	new_fcp.set_direction(0);
	int find = 0;
	const string& uri = fcp.dst_uri();
	const string& src_node = fcp.src_uri();
	const string& data = fcp.data();

	UriPath uri_path(uri);
	auto dir = uri_path[m_path.size()];
	auto ptr = m_table.find(dir.m_name);
	if (ptr != m_table.end()) {
		auto& t = ptr->second;
		for (int i = 0; i < t.size(); i++)
		{
			if (dir.include(i))
			{
				t[i]->sendMsg(new_fcp);
				Logger->trace("{}::{}>>>{}", m_path.toString(), new_fcp.type(), dir.toString());
				find = 1;
			}
		}
	}

	return find;
}

int DownNode_::handleSelf(const FcpMessage & fcp)
{
	Logger->warn("handleLocal not implement");
	return 0;
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
首先判断收到的消息是否是谁的？，
如为父节点，调用sendMsg
为自己的，调用handleSelf；
为子节点，调用handleChild；
为兄弟节点，则需要判断方向
/a:0/a 有 brother /a:0/a:*

*/
int DownNode_::handleMsg(const FcpMessage & fcp)
{
	const string& uri = fcp.dst_uri();
	int rel = relation(m_path, UriPath(uri));
	Logger->info("Msg relation:{}", rel);
	FcpMessage new_fcp = fcp;
	if (rel &relType::PARENT) {
		new_fcp.set_direction(1);
		sendMsg(new_fcp);
	}
	if (rel &relType::SELF) {
		handleSelf(new_fcp);
	}
	if (rel&relType::CHILD)
	{
		new_fcp.set_direction(0);
		handleChild(new_fcp);
	}
	return rel;
}

inline int DownNode_::sendMsg(const FcpMessage & msg)
{
	assert_log(msg.direction() == 1);
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
	assert_log(msg.direction() == 1);
	if (m_gateway)
			m_gateway->handleMsg(msg);
	return 0;
}

int TopNode_::sendMsg(const FcpMessage & msg)
{
	//Logger->debug("{}/{}>>>", m_deal, msg.type());
	assert_log(msg.direction() == 0);
	auto data = msg.SerializeAsString();
	return Tx(std::to_string(data.size()) + ":" + data);
}

void TopNode_::setGateway(Node_ * top)
{
	m_gateway = top;
}