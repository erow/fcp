// FCP.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Node_.h"
#include "FunctionalNode.h"

#include "MQTTMaster.h"
#include "UType.h"
#include <vector>

std::vector<spdlog::sink_ptr> sinks{ 
	std::make_shared<spdlog::sinks::wincolor_stdout_sink_mt>(),
	std::make_shared<spdlog::sinks::rotating_file_sink_mt>("fcp.log", 1048576 * 5, 5) };

std::shared_ptr<spdlog::logger> Logger = std::make_shared<spdlog::logger>("fcp", begin(sinks), end(sinks));


MQTTMaster nh("/pc:0");
void test() {
	PathTest();
	 
	FunctionalNode<SType> f1([](const SType& a) {
		nh.publish("/pc:0/fo", a);
		Logger->info("f1 {}", a.SerializeAsString());
		});
	FunctionalNode<SType> f2([](const SType& a) {
		Logger->info("f2 {}",a.SerializeAsString());
	});
	FunctionalNode<SType> f3([](const SType& a) {
		Logger->info(a.SerializeAsString());
	});
	FunctionalNode<SType> sub([](const SType& a) {
		Logger->info(a.SerializeAsString());
	});
	nh.addNode("f", f1);
	nh.addNode("fo", f2);
	SType str; str.ParseFromString("\"[1,2,3]\"");
	nh.publish("/pc:0/f", str);
	nh.publish("/a", str);

	nh.spin();
}
int main()
{
	spdlog::register_logger(Logger);
	/*log level*/
	Logger->set_level(spdlog::level::trace);
	//sinks[0]->set_level(spdlog::level::info);
	//spdlog::set_pattern("[%D %H:%M:%S.%f][%l]%v");
	
	/*win init socket*/

	test();
    return 0;
}


