#include "Node_.h"
#include "path.h"

int Node_::sendMsg(const FcpMessage & msg)
{
	Log(logger, "sendMsg from: %s-%s\n", m_deal.c_str(), m_path.abs_uri().c_str());
	auto data = msg.SerializeAsString();
	return Tx(std::to_string(data.size()) + ":" + data);
}

void Node_::setPath(const string & path)
{
	m_path = Path(path);
}
//返回得到的消息数目
int Node_::Rx(const std::string &data)
{
	if (m_buffer.empty() && msg_size == 0) {
		for (int i = 0; i < data.size(); i++)
		{
			if (data[i] == ':') {
				msg_size = std::stoi(m_buffer);
				m_buffer.clear();
				return Rx(data.substr(i + 1));
			}
			else {
				m_buffer += data[i];
			}
		}
		return 0;
	}
	else {
		for (int i = 0; i < data.size(); i++)
		{
			m_buffer += data[i];
			if (m_buffer.size() == msg_size)
			{
				FcpMessage msg;
				msg.ParseFromString(m_buffer);
				handleMsg(msg);
				m_buffer.clear();
				msg_size = 0;
				return 1 + Rx(data.substr(i + 1));
			}
		}
		return 0;
	}
}
