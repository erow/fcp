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
//		if (is_include(m_path,UriPath(path))) {
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


DownNode_::DownNode_()
{
	m_deal = "un init";
	m_information = "DownNode_";
}


DownNode_::~DownNode_()
{
}

/*
�����ж��յ�����Ϣ�Ƿ���˭�ģ���
��Ϊ���ڵ㣬����sendMsg
Ϊ�Լ��ģ�����handleSelf��
Ϊ�ӽڵ㣬����handleChild��
Ϊ�ֵܽڵ㣬����Ҫ�жϷ���
/a:0/a �� brother /a:0/a:*

*/

int DownNode_::sendMsg(const FcpMessage & msg)
{
	assert_log(msg.direction() == 1);
	auto data = msg.SerializeAsString();
	return Tx(std::to_string(data.size()) + ":" + data);
}



TopNode_::TopNode_()
{
	m_deal = "un init";
	m_information = "TopNode_";
}

TopNode_::~TopNode_()
{
}

