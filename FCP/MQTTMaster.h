
#include "AloneNode.h"
#include "MQTTClient.h"
#include "MQTTClientPersistence.h"


#define ADDRESS     "tcp://shad.mqtt.iot.gz.baidubce.com:1883"
#define CLIENTID    "MQTTMaster"
#define QOS         1
#define TIMEOUT     10000L
#define USERNAME	"shad/led_0"
#define PASSWORD	"GzjsmmF1a+opPQ7rpLim3pMaQtFy4qZhxkb08nAhh6U="
class MQTTMaster :
	public AloneNode {
protected:
public:
	MQTTClient client;
	MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
	MQTTClient_SSLOptions ssl_opts = MQTTClient_SSLOptions_initializer;
	bool toStop = false;
	int rc;

	MQTTMaster(const string& node_name) {
		m_deal = "master";
		m_path= NodePath(node_name);

		MQTTClient_deliveryToken token;

		MQTTClient_create(&client, ADDRESS, CLIENTID,
			MQTTCLIENT_PERSISTENCE_NONE, NULL);
		conn_opts.keepAliveInterval = 20;
		conn_opts.cleansession = 1;
		conn_opts.username = USERNAME;
		conn_opts.password = PASSWORD;

		if ((rc = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS)
		{
			Logger->error("Failed to connect, return code %d\n", rc);
			exit(-1);
		}
		string topic = node_name + "/#";
		rc = MQTTClient_subscribe(client,topic.c_str() , QOS);

	}
	~MQTTMaster() {
		MQTTClient_disconnect(client, 10000);
		MQTTClient_destroy(&client);
	}
	virtual int sendMsg(const json & msg) {
		MQTTClient_message pubmsg = MQTTClient_message_initializer;
		MQTTClient_deliveryToken token;
		string payload = msg["data"].get<string>();

		pubmsg.payload =(void*) payload.c_str();
		pubmsg.payloadlen = payload.size();
		pubmsg.qos = QOS;
		pubmsg.retained = 0;
		MQTTClient_publishMessage(client, msg["dst_uri"].get<string>().c_str(), &pubmsg, &token);
		
		rc = MQTTClient_waitForCompletion(client, token, TIMEOUT);
		printf("Message with delivery token %d delivered\n", token);
		return rc;
	}
	int spin() {
		while (!toStop)
		{
			char* topicName = NULL;
			int topicLen;
			MQTTClient_message* message = NULL;

			rc = MQTTClient_receive(client, &topicName, &topicLen, &message, 1000);
			if (message)
			{
				//binary payload((unsigned char*)message->payload, (unsigned char*)(message->payload)+message->payloadlen);
				SType payload;
				payload->assign((char*)message->payload, message->payloadlen);
				publish(topicName, payload);
				message->payload;
				MQTTClient_freeMessage(&message);
				MQTTClient_free(topicName);
			}
			if (rc != 0)
				return rc;
		}
	}

};