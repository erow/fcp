// FCP.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Node_.h"
#include "FunctionalNode.h"
#include "msg/light.pb.h"
#include "MasterNode.h"
#include "TcpNode.h"
std::shared_ptr<spdlog::logger> Logger = spdlog::stdout_color_mt("console");
MasterNode nh;
int main()
{
	/*win init socket*/
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed with error: %d\n", iResult);
	}
	/*log level*/
	Logger->set_level(spdlog::level::debug);

	FunctionalNode<LightMessage> a([](const LightMessage& msg) {
		printf("call fun. status:%d\n", msg.status());
	});
	nh.addNode("fun", a);


	TcpNode tp;
	tp.Listen("0.0.0.0:1212");

	tp.Accept();
	tp.Recv();











	LightMessage l;
	l.set_status(32);
	FcpMessage msg;
	msg.set_data(l.SerializeAsString());

	a.publish("fun",msg);
	nh.publish("fun", msg);

	WSACleanup();
    return 0;
}

