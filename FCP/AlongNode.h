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
				if (dir.include(i))
				{
					t[i]->sendMsg(new_fcp);
					Logger->trace("{}::{}>>>{}", m_path.toString(), new_fcp.type(), dir.toString());
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
	virtual int handleMsg(const FcpMessage& fcp)
	{
		const string& uri = fcp.dst_uri();
		int rel = relation(m_path, UriPath(uri));
		Logger->info("Msg relation:{}", rel);
		FcpMessage new_fcp = fcp;
		if (rel &relType::PARENT) {
			new_fcp.set_direction(1);
			sendMsg(new_fcp);
		}
		if (rel &relType::SELF) {
			handleSelf(new_fcp);
		}
		if (rel&relType::CHILD)
		{
			new_fcp.set_direction(0);
			handleChild(new_fcp);
		}
		return rel;
	}

	int sendMsg(const FcpMessage & msg) {

	}
	//user api
	virtual void unregister(const std::string& uri){
		Logger->warn("unregister not implement");
	}


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
			publish from:{} to:{}", m_deal.c_str(), uri.c_str());
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

