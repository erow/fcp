// FCP.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Node_.h"

class Node:
	public Node_
{
public:
	Node();
	~Node();
	int handleMsg(const FcpMessage& fcp) {
		const string& uri = fcp.dst_uri();
		int rel = m_path.relation(uri);
		if (rel == (int)relType::parent) {
			FcpMessage t_fcp = fcp;
			t_fcp.set_type(FcpMessage_FcpType_POSTUP);
			sendMsg(t_fcp);
		}
		else if (rel == (int)relType::self) {

		}
		else if (rel == (int)relType::brother) {
			
		}
		else if (rel == (int)relType::child) {

		}
		return 0;
	}
	int Tx(const std::string& data) {
		return Rx(data);
	}
private:

};

Node::Node()
{
}

Node::~Node()
{
}
int main()
{
	Node a;
    return 0;
}

