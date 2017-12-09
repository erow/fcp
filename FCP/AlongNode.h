#pragma once
#include "Node_.h"
class AlongNode :
	public Node_
{
public:
	AlongNode(){}
	~AlongNode(){}
protected:
	//string m_uri;//为了解决转发URI的问题
	std::map<string, std::vector<Node_*>> m_table;

	//int handlePublish(const FcpMessage & fcp);
	int handleChild(const FcpMessage & fcp) {
		FcpMessage new_fcp = fcp;
		new_fcp.set_direction(0);
		int find = 0;
		const string& uri = fcp.dst_uri();
		const string& src_node = fcp.src_uri();
		const string& data = fcp.data();

		UriPath uri_path(uri);
		auto dir = uri_path[m_path.size()];
		auto ptr = m_table.find(dir.m_name);
		if (ptr != m_table.end()) {
			auto& t = ptr->second;
			for (int i = 0; i < t.size(); i++)
			{
				if (dir.is_include(i))
				{
					t[i]->sendMsg(new_fcp);
					find = 1;
				}
			}
		}

		return find;
	}
	virtual int handleSelf(const FcpMessage & fcp)
	{
		Logger->warn("handleLocal not implement");
		return 0;
	}
public:
	virtual int diliverMsg(const FcpMessage& fcp) {
		const string& uri = fcp.dst_uri();
		int rel = relation(m_path, UriPath(uri));
		Logger->trace("({}) Msg::{} relation:{}", m_path.toString(),fcp.type(), rel);
		FcpMessage new_fcp = fcp;
		if (rel &relType::SELF) {
			UriPath newUri = UriPath(uri);
			if (newUri.size() == 0)
			{
				handleSelf(new_fcp);
			}
			else {
				handleSelf(new_fcp);
				newUri.get(m_path.size() - 1)->exclude(m_path[m_path.size() - 1].m_num);
				new_fcp.set_dst_uri(newUri.toString());
			}

		}
		if (rel &relType::PARENT) {
			new_fcp.set_direction(1);
			sendMsg(new_fcp);
		}
		if (rel&relType::CHILD)
		{
			new_fcp.set_direction(0);
			handleChild(new_fcp);
		}
		return rel;
	}
	virtual int handleMsg(const FcpMessage& fcp)
	{
		assert_log(fcp.direction() == 0);
		const string& uri = fcp.dst_uri();
		int rel = relation(m_path, UriPath(uri));
		if (rel &relType::SELF) {
			handleSelf(fcp);
			
		}
		assert_log(0==(rel &relType::PARENT));
		if (rel&relType::CHILD)
		{
			handleChild(fcp);
		}
		return rel;
	}

	virtual int sendMsg(const FcpMessage & msg) {
		Logger->trace_if(msg.direction() == 0, "({}) sendMsg::{} >>> ", m_path.toString(), msg.type());
		Logger->trace_if(msg.direction() == 1, "({}) sendMsg::{} <<< ", m_path.toString(), msg.type());
		if (msg.direction() == 0)
			return handleMsg(msg);
		else
			return m_gateway ? m_gateway->diliverMsg(msg) : -1;
	}
	//user api
	virtual void unregister(const std::string& uri){
		Logger->warn("({}) unregister not implement", m_path.toString());
	}


	void addSubscribe(std::string dst_uri, Node_& node)
	{

		
		int label_num = m_table["subscriber"].size();
		m_table["subscriber"].push_back(&node);
		string call_uri = m_path.toString("subscriber:" + std::to_string(label_num));
		string caller = m_path.toString(call_uri);
		FcpMessage msg;
		msg.set_dst_uri("/");
		msg.set_src_uri(caller);
		msg.set_type(FcpMessage_FcpType_SUBSCRIBE);
		msg.set_data(m_path.toString(dst_uri));
		Logger->info("Subscribe {} by {}", dst_uri, call_uri);
		node.setGateway(this);
		node.setPath(caller);
		diliverMsg(msg);

	}

	template<typename T>
	void publish(std::string uri, const T& data) {
		Logger->trace("publish begin from:{} to:{}", m_path.toString(), uri.c_str());
		FcpMessage fcp;
		fcp.set_dst_uri(m_path.toString(uri));
		fcp.set_src_uri(m_path.toString());
		fcp.set_type(FcpMessage_FcpType::FcpMessage_FcpType_Publish);
		fcp.set_data(data.SerializeAsString());

		diliverMsg(fcp);

		Logger->debug("publishEx -----------------------");
		//额外发送一个消息给master，由master转发给订阅者
		fcp.set_dst_uri("/");
		fcp.set_direction(1);
		fcp.set_src_uri(m_path.toString(uri));//复用src 作为转发的目的地
		fcp.set_type(FcpMessage_FcpType::FcpMessage_FcpType_ExtPublish);
		sendMsg(fcp);
		Logger->debug("publish end-----------------------");
	}

	void addNode(std::string node_name, Node_& node) {
		int label_num;
		if (m_table.find(node_name) != m_table.end())
		{
			label_num = m_table[node_name].size();
			m_table[node_name].push_back(&node);
			
			
		}
		else {
			label_num = 0;
			m_table[node_name].push_back(&node);
		}

		string path = m_path.toString(node_name + ":" + std::to_string(label_num));
		node.setGateway(this);
		node.setPath(path);
		Logger->info("addNode to {}", path);
	}
};

