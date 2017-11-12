// FCP.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Node_.h"
#include "FunctionalNodecpp.h"
#include "msg/light.pb.h"
#include "MasterNode.h"

MasterNode nh;
int main()
{
	FunctionalNode<LightMessage> a([](const LightMessage& msg) {
		printf("call fun. status:%d\n", msg.status());
	});
	LightMessage l;
	l.set_status(32);
	FcpMessage msg;
	msg.set_data(l.SerializeAsString());
	a.sendMsg(msg);
    return 0;
}

