#pragma once
#include"Node_.h"
#include "AlongNode.h"


class DownNode_ :
	public AlongNode
{
public:
	DownNode_();
	~DownNode_();
protected:
	
	virtual int handleSelf(const FcpMessage & fcp)
	{
		Logger->warn("handleLocal not implement");
		return 0;
	}

	int Rx(const std::string &data)
	{
		if (m_buffer.empty() && msg_size == 0)
		{
			for (int i = 0; i < data.size(); i++)
			{
				if (data[i] == ':') {
					msg_size = std::stoi(m_buffer);
					m_buffer.clear();
					//Logger->trace("recv a msg with size of {}", msg_size);
					return Rx(data.substr(i + 1));
				}
				else {
					m_buffer += data[i];
				}
			}
		}
		else
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
		return 0;
	}

	virtual int Tx(const std::string &data) = 0;
public:
	int sendMsg(const FcpMessage & msg);
};

class TopNode_ :
	public DownNode_
{
protected:
public:
	TopNode_();
	~TopNode_();
	virtual int handleMsg(const FcpMessage& msg)
	{
		assert_log(msg.direction() == 1);
		if (m_gateway)
			m_gateway->diliverMsg(msg);
		return 0;
	}
	int sendMsg(const FcpMessage & msg)
	{
		//Logger->debug("{}/{}>>>", m_deal, msg.type());
		assert_log(msg.direction() == 0);
		auto data = msg.SerializeAsString();
		return Tx(std::to_string(data.size()) + ":" + data);
	}

};