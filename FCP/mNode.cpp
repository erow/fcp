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
�����ж��յ�����Ϣ�Ƿ���˭�ģ���
��Ϊ���ڵ㣬����sendMsg
Ϊ�Լ��ģ�����handleSelf��
Ϊ�ӽڵ㣬����handleChild��
Ϊ�ֵܽڵ㣬����Ҫ�жϷ���
/a:0/a �� brother /a:0/a:*

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

