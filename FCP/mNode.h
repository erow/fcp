#pragma once
#include"Node_.h"


class TopNode_ :
	public Node_ 
{
protected:
	Node_* m_gateway = nullptr;
public:
	TopNode_();
	~TopNode_();
	virtual int handleMsg(const FcpMessage& msg);
	int sendMsg(const FcpMessage & msg);
	void setGateway(Node_* top);

};
class DownNode_ :
	public Node_
{
protected:

	string m_uri;//Ϊ�˽��ת��URI������
	std::vector< std::pair<std::string, Node_*> > m_table;

	int handlePublish(const FcpMessage & fcp);
	int handleLocal(const FcpMessage & fcp);
public:
	DownNode_();
	~DownNode_();
	virtual int handleMsg(const FcpMessage& fcp);
	int sendMsg(const FcpMessage & msg);
	//user api
	virtual void unregister(const std::string& uri);

	template<typename T>
	void addSubscribe(std::string dst_uri, T& node)
	{
		Logger->debug( "----------------------- \n\
			Subscribe from:{} to:{}\n", m_deal, uri);
		int n = -1;
		for (auto t = m_table.begin(); t != m_table.end(); t++) {
			if (belong(t->first, "subscriber")) {
				string number = split(t->first, ":")[1];
				int num = std::stoi(number);
				n = max(num, n);
			}
		}
		string call_uri = "subscriber:" + std::to_string(n+1);
		FcpMessage msg;
		msg.set_dst_uri(m_path.abs_uri(dst_uri));
		msg.set_src_uri(m_path.abs_uri(call_uri));
		msg.set_type(FcpMessage_FcpType_SUBSCRIBE);
		msg.set_data("");
		sendMsg(msg);

		m_table.push_back({ call_uri, &node });
	}

	template<typename T>
	void publish(std::string uri, const T& data) {
		Logger->debug("publish begin----------------------- \n\
			publish from:{} to:{}",m_deal.c_str(), uri.c_str());
		FcpMessage fcp;
		fcp.set_dst_uri(m_path.abs_uri(uri)); 
		fcp.set_src_uri(m_path.abs_uri());
		fcp.set_type(FcpMessage_FcpType::FcpMessage_FcpType_Publish);
		fcp.set_data(data.SerializeAsString());
		
		relType rel = m_path.relation(uri);
		if (rel == relType::child) {
			fcp.set_direction(0);
			handleMsg(fcp);
		}
		else {
			fcp.set_direction(1);
			sendMsg(fcp);
		}

		Logger->debug("publishEx -----------------------");
		fcp.set_dst_uri(m_path.abs_uri(uri));
		fcp.set_direction(1);
		fcp.set_type(FcpMessage_FcpType::FcpMessage_FcpType_ExtPublish);
		//���ⷢ��һ����Ϣ��master����masterת����������
		sendMsg(fcp);
		Logger->debug("publish end-----------------------");
	}

	template<typename T>
	void addNode(std::string path, T& node) {
		int n = -1;
		for (auto t = m_table.begin(); t != m_table.end(); t++) {
			if (belong(t->first, path)) {
				string number = split(t->first, ":")[1];
				int num = std::stoi(number);
				n = std::max(num, n);
			}
		}
		string node_uri = path + ":" + std::to_string(n+1);
		m_table.push_back({ node_uri , &node });
		node.setGateway(this);
		node.setPath(m_path.abs_uri(node_uri));
	}
};

