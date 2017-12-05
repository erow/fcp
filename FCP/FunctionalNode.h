#pragma once
#include "mNode.h"
#include "Node_.h"
#include<functional>
#include"msg/fcp.pb.h"
template <class T>
class FunctionalNode :
	public DownNode_
{
protected:
	typedef void(*FunctionType)(const T&);
	Node_* m_gateway = nullptr;
	/*int handleMsg(const FcpMessage& msg)
	{
		assert_log((msg.type() == FcpMessage_FcpType::FcpMessage_FcpType_Publish) || 
			msg.type() == FcpMessage_FcpType::FcpMessage_FcpType_ExtPublish);

		if (msg.direction() == 0) {
			T t;
			t.ParseFromString(msg.data());
			Logger->debug("exec from:{} to:{}", msg.src_uri().c_str(), msg.dst_uri().c_str());
			m_fun(t);
			return 0;
		}
		else if (msg.direction() == 1)
		{
			sendMsg(msg);
			return 1;
		}

	}*/
	std::function<void(const T&)> m_fun;
public:
	FunctionalNode(FunctionType fun)
	{
		m_fun = fun;
		m_information = typeid(T).name();
		m_deal = "functional";
	}
	~FunctionalNode()
	{
	}
	int Tx(const std::string& data)
	{
		if(m_gateway)
			return m_gateway->Rx(data);
		return 0;
	}
	int sendMsg(const FcpMessage& fcp) {
		if (fcp.direction() == 1)
		{
			if (m_gateway)
				m_gateway->handleMsg(fcp);
		}
		else {
			handleMsg(fcp);
		}
	}
	void setGateway(Node_* top) {
		m_gateway = top;
	}
};