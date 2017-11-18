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
	Path m_path;
	string m_deal;
	string m_information;
	string m_buffer;
	int msg_size = 0;

public:
	virtual int sendMsg(const FcpMessage&) =0;
	virtual int handleMsg(const FcpMessage&) = 0;
	void setPath(const string& path);
	int Rx(const std::string&);
	virtual int Tx(const std::string&) = 0;
};