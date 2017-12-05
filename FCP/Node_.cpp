#include "Node_.h"
#include "path.h"

void Node_::setPath(const string & path)
{
	m_path = NodePath(path);
}
//返回得到的消息数目
int Node_::Rx(const std::string &data)
{
	assert_log(m_buffer.empty() && msg_size == 0);
	for (int i = 0; i < data.size(); i++)
	{
		if (data[i] == ':') {
			msg_size = std::stoi(m_buffer);
			m_buffer.clear();
			Logger->trace("recv a msg with size of {}", msg_size);
			return RxMsg(data.substr(i + 1));
		}
		else {
			m_buffer += data[i];
		}
	}
	return 0;
}

int Node_::RxMsg(const std::string & data)
{
	assert_log(m_buffer.size() <= msg_size);
	for (int i = 0; i < data.size(); i++)
	{
		m_buffer.push_back(data[i]);
		if (m_buffer.size() == msg_size)
		{
			FcpMessage msg;
			msg.ParseFromString(m_buffer);
			Logger->trace("recv msg:{}", msg_size);
			handleMsg(msg);
			m_buffer.clear();
			msg_size = 0;
			return 1 + Rx(data.substr(i + 1));
		}
	}
	return 0;
}