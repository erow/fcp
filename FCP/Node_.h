#pragma once
#include<string>
#include<map>
#include<functional>
#include"msg/fcp.pb.h"
#include "path.h"
#include <spdlog\spdlog.h>

using std::string;

extern std::shared_ptr<spdlog::logger> Logger ;
class Node_ {
protected:
	NodePath m_path;
	string m_deal;
	string m_information;
	string m_buffer;
	int msg_size = 0;
	Node_* m_gateway = nullptr;
	int RxMsg(const std::string&);
public:
	virtual int sendMsg(const FcpMessage& ) =0;
	virtual int handleMsg(const FcpMessage& fcp) = 0;
	
	virtual int Tx(const std::string&) = 0;
	void setPath(const string& path);
	int Rx(const std::string&);
	void setGateway(Node_* top) { m_gateway = top; }
};