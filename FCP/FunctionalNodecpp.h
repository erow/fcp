#pragma once
#include "Node_.h"
#include<functional>
#include"msg/fcp.pb.h"
template <class T>
class FunctionalNode :
	public Node_
{
protected:
	typedef void(*FunctionType)(const T&);
	Node_* m_gateway = nullptr;
	int handleMsg(const FcpMessage& msg)
	{
		T t;
		t.ParseFromString(msg.data());
		Log(logger, "exec from:%s to:%s\n", msg.src_uri().c_str(), msg.dst_uri().c_str());
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
		return Rx(data);
	}
	void setGateway(Node_* top) {
		m_gateway = top;
	}
};