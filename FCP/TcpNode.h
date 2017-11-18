#pragma once
#include "mNode.h"
#include <winsock2.h>

#define DEFAULT_BUFLEN 512

class TcpNode :
	public TopNode_
{
private:
	SOCKET ListenSocket = INVALID_SOCKET;
	SOCKET RemoteSocket = INVALID_SOCKET;

	int Tx(const std::string&);
public:
	TcpNode();
	~TcpNode();

	int Listen(const string& deal);
	int Accept();

	int Recv();
	
};


class TcpDownNode :
	public DownNode_
{
private:
	SOCKADDR_IN target; //Socket address information
	SOCKET m_socket;

	int Tx(const std::string& data);
public:
	TcpDownNode(){}
	~TcpDownNode(){}

	int Connect(const string& deal);

	int Recv();

};