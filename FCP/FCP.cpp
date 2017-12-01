// FCP.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Node_.h"
#include "FunctionalNode.h"
#include "msg/light.pb.h"
#include "MasterNode.h"
#include "TcpNode.h"
#include "UType.h"
#include <google\protobuf\map.h>
#include <google\protobuf\util\json_util.h>
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
		auto str = msg.DebugString();
		msg.SerializeAsString();
		Logger->info(str);
	});
	TcpNode tcp;
	tcp.setPath("/tcp:0");
	nh.addNode("fun", a);
	SType any;

	PbType<LightMessage> l;
	l->set_status(2);
	auto s=l.SerializeAsString();
	//Logger->debug(l.print());
	any = "hello world!";
	TcpNode tp;
	tp.Listen("0.0.0.0:1212");
	nh.addNode("tcp", tp);
	while (true)
	{
		while (tp.Accept() <= 0)
			;
		a.publish("/tcp/fun:0", any);
		while (tp.Recv() >= 0)
			;
	}
	
	//nh.publish("fun", l);
	WSACleanup();
    return 0;
}

