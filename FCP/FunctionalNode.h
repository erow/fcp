#pragma once
#include "AloneNode.h"
#include<functional>

template <class T>
class FunctionalNode :
	public AloneNode
{
protected:
	typedef void(*FunctionType)(const T&);
	int handleSelf(const json& msg)
	{
		if ((msg["type"] == FcpMessage_FcpType::FcpMessage_FcpType_Publish) ||
			msg["type"] == FcpMessage_FcpType::FcpMessage_FcpType_ExtPublish) {
			T t;
			t.ParseFromString(msg["data"]);
			Logger->debug("{} exec from {} ", m_path.toString(), msg["src_uri"].get<std::string>());
			m_fun(t);
			return 0;
		}

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
		return 0;
	}
};