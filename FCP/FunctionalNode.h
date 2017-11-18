#pragma once
#include "mNode.h"
#include<functional>
#include"msg/fcp.pb.h"
template <class T>
class FunctionalNode :
	public DownNode_
{
protected:
	typedef void(*FunctionType)(const T&);
	Node_* m_gateway = nullptr;
	int handleMsg(const FcpMessage& msg)
	{
		assert((msg.type() == FcpMessage_FcpType::FcpMessage_FcpType_Publish) || msg.type() == FcpMessage_FcpType::FcpMessage_FcpType_ExtPublish);
		T t;
		t.ParseFromString(msg.data());
		Logger->debug("exec from:{} to:{}\n", msg.src_uri().c_str(), msg.dst_uri().c_str());
		m_fun(t);
		return 0;
	}
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
	}
	void setGateway(Node_* top) {
		m_gateway = top;
	}
};