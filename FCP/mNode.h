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
	//string m_uri;//为了解决转发URI的问题
	std::map<string,std::vector<Node_*>> m_table;

	//int handlePublish(const FcpMessage & fcp);
	int handleChild(const FcpMessage & fcp);
	virtual int handleSelf(const FcpMessage & fcp);
public:
	DownNode_();
	~DownNode_();
	virtual int handleMsg(const FcpMessage& fcp);
	int sendMsg(const FcpMessage & msg);
	//user api
	virtual void unregister(const std::string& uri);


	void addSubscribe(std::string dst_uri, Node_& node)
	{
		
		int label_num = m_table["subscriber"].size();
		m_table["subscriber"].push_back(&node);
		string call_uri = m_path.toString("subscriber:" + std::to_string(label_num));

		FcpMessage msg;
		msg.set_dst_uri(m_path.toString(dst_uri));
		msg.set_src_uri(m_path.toString(call_uri));
		msg.set_type(FcpMessage_FcpType_SUBSCRIBE);
		msg.set_data("");
		sendMsg(msg);

		Logger->debug("Subscribe {} by {}", dst_uri, call_uri);
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
		handleMsg(fcp);

		Logger->debug("publishEx -----------------------");
		fcp.set_dst_uri(m_path.abs_uri(uri));
		fcp.set_direction(1);
		fcp.set_type(FcpMessage_FcpType::FcpMessage_FcpType_ExtPublish);
		//额外发送一个消息给master，由master转发给订阅者
		sendMsg(fcp);
		Logger->debug("publish end-----------------------");
	}

	void addNode(std::string node_name, Node_& node) {
		if (m_table.find(node_name) != m_table.end())
		{
			int label_num = m_table[node_name].size();
			m_table[node_name].push_back(&node);
			node.setGateway(this);
			string path = m_path.toString(node_name + ":" + std::to_string(label_num));
			node.setPath(path);
			Logger->info("addNode to {}", path);
		}
	}
};

