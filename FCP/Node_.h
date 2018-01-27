#pragma once
#include<string>
#include<map>
#include<functional>
#include <json.hpp>
#include <spdlog\spdlog.h>
#include "path.h"
#include "UType.h"
using std::string;
using json = nlohmann::json;
extern std::shared_ptr<spdlog::logger> Logger ;
class Node_ {
protected:
	NodePath m_path;
	string m_deal;
	string m_information;
	int msg_size = 0;
	EncodeType m_encode;
	Node_* m_gateway = nullptr;
	//int RxMsg(const std::string&);
public:
	virtual int sendMsg(const json& ) =0;
	virtual int handleMsg(const json& fcp) = 0;
	virtual int diliverMsg(const json& fcp) { Logger->error("unimplement diliverMsg"); return 0; };
	//virtual int Tx(const std::string&) = 0;
	void setPath(const string& path);
	//int Rx(const std::string&);
	void setGateway(Node_* top) { m_gateway = top; }
};