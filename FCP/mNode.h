#pragma once
#include"Node_.h"
#include "AloneNode.h"


class DownNode_ :
	public AloneNode
{
public:
	DownNode_();
	~DownNode_();
protected:

	binary m_buffer;
	virtual int handleSelf(const json & fcp)
	{
		Logger->warn("handleLocal not implement");
		return 0;
	}

	int Rx(const binary &data)
	{
		//push to buffer
		for (auto c : data)
			m_buffer.push_back(c);

		if (m_buffer.empty() && msg_size == 0)
		{
			//header 4 bytes:  length:3|encode:1
			if (m_buffer.size() > 4)
			{
				m_encode = (EncodeType)m_buffer[3];
				msg_size = (*((unsigned int*)&m_buffer[0]))&0x00ffffff;
				return Rx(binary(m_buffer.begin()+4, m_buffer.end()));
			}else
			return 0;
		}
		else
		{
			if(m_buffer.size() >= msg_size){
				
				switch (m_encode)
				{
				case JSON:
					handleMsg(json::parse(m_buffer.begin(), m_buffer.begin() + msg_size));
					m_buffer.clear();
					msg_size = 0;
					return 1 + Rx(binary(m_buffer.begin()+msg_size,m_buffer.end()));
					break;
				case PB:
					Logger->error("wrong encode type{}", m_encode);
					break;
				default:
					Logger->error("wrong encode type{}",m_encode);
				}
			}else
			return 0;
		}
	}

	virtual int Tx(const binary &data) = 0;
public:
	int sendMsg(const json & msg);
};

class TopNode_ :
	public Node_
{
protected:
public:
	TopNode_();
	~TopNode_();
	virtual int Tx(const binary& ) = 0;
	virtual int handleMsg(const json& msg)
	{
		assert_log(msg["direction"] == 1);
		if (m_gateway)
			m_gateway->diliverMsg(msg);
		return 0;
	}
	int sendMsg(const json & msg)
	{
		//Logger->debug("{}/{}>>>", m_deal, msg.type());
		assert_log(msg["direction"] == 0);
		auto data = msg.dump();
		int len = data.size();
		binary head(4+ len);
		head[3]=EncodeType::JSON;
		(*((unsigned int*)&data[0]))= len;
		for (int i = 0; i < len; i++)
			head[i + 4] = data[i];
		return Tx(head);
	}

};