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

#include <vector>

std::vector<spdlog::sink_ptr> sinks{ 
	std::make_shared<spdlog::sinks::wincolor_stdout_sink_st>(),
	std::make_shared<spdlog::sinks::rotating_file_sink_st>("fcp.log", 1048576 * 5, 5) };

std::shared_ptr<spdlog::logger> Logger = std::make_shared<spdlog::logger>("fcp", begin(sinks), end(sinks));

MasterNode nh;
void test() {
	PathTest();
	 
	FunctionalNode<SType> f1([](const SType& a) {
		Logger->info(a.SerializeAsString());
		});
	FunctionalNode<SType> f2([](const SType& a) {
		Logger->info(a.SerializeAsString());
	});
	FunctionalNode<SType> f3([](const SType& a) {
		Logger->info(a.SerializeAsString());
	});
	FunctionalNode<SType> sub([](const SType& a) {
		Logger->info(a.SerializeAsString());
	});
	TcpNode tcp;
	
	nh.addNode("a", f1);
	nh.addNode("a", f2);
	f1.addNode("a", f3);
	f3.addSubscribe("/a:0", sub);


	f1.addNode("tcp", tcp);
	SType data;
	data="/a";
	//nh.publish("/a", data);

	//f1.publish("/a:0", data="/a:0");

	//f2.publish("/a:0/a", data = "/a:0/a");
	f3.publish("/a:0", data = "hello");

	string deal = "0.0.0.0:1314";
	tcp.Listen(deal);
	
	while (true)
	{
		tcp.Accept();
		if (tcp.Recv() < 0)
			continue;
	}
	
}
int main()
{
	spdlog::register_logger(Logger);
	/*log level*/
	Logger->set_level(spdlog::level::trace);
	//sinks[0]->set_level(spdlog::level::info);
	//spdlog::set_pattern("[%D %H:%M:%S.%f][%l]%v");
	
	/*win init socket*/
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		Logger->debug("WSAStartup failed with error: %d\n", iResult);
	}
	//test();
	TcpNode tcp;
	SType any;
	TcpNode asr;
	asr.Listen("0.0.0.0:1212");
	nh.addNode("asr", asr);
	
	TcpNode parser;
	parser.Listen("0.0.0.0:1213");
	nh.addNode("parser", parser);
	
	asr.AutoRun();
	parser.AutoRun();
	asr.m_thread.join();
	parser.m_thread.join();
	//nh.publish("fun", l);
	WSACleanup();
    return 0;
}

