#include "mNode.h"
#include "Node_.h"

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

int DownNode_::sendMsg(const json & msg)
{
	assert_log(msg["direction"] == 1);
	auto data = msg.dump();
	int len = data.size();
	binary head(4 + len);
	head[3] = EncodeType::JSON;
	(*((unsigned int*)&m_buffer[0])) = len;
	for (int i = 0; i < len; i++)
		head[i + 4] = data[i];
	return Tx(head);
}



TopNode_::TopNode_()
{
	m_deal = "un init";
	m_information = "TopNode_";
}

TopNode_::~TopNode_()
{
}

