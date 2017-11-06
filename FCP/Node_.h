#pragma once
#include<string>
#include<map>
#include<functional>
#include"msg/fcp.pb.h"
#include "path.h"
using std::string;
#define DEBUG
#ifdef DEBUG

#define Log(logger,format, ...) printf("D>> " format,##__VA_ARGS__)
#else
#endif // DEBUG


class Node_ {
protected:
	Path m_path;
	string m_deal;
	string m_information;
	string m_buffer;
	int msg_size = 0;

public:
	int sendMsg(const FcpMessage&);
	void setPath(const string& path);
	int Rx(const std::string&);

	virtual int handleMsg(const FcpMessage&) = 0;
	virtual int Tx(const std::string&) = 0;
};