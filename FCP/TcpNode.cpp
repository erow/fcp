#include "TcpNode.h"
#pragma comment (lib, "Ws2_32.lib")


int TcpNode::Tx(const std::string & data)
{
	if (RemoteSocket == INVALID_SOCKET) {
		printf("accept failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
	}
	else
	{
		send(RemoteSocket, data.c_str(), data.size(), 0);
		printf("send %d\n", data.size());
	}
	return 0;
}

TcpNode::TcpNode()
{
	m_information = "Tcp node";

	// Create a SOCKET for connecting to server
	ListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);


}


TcpNode::~TcpNode()
{
}

int TcpNode::Listen(const string & deal) {
	m_deal = deal;
	auto vec = split(deal, ":");

	SOCKADDR_IN addr; // The address structure for a TCP socket
	addr.sin_family = AF_INET;      // Address family
	addr.sin_port = htons(std::stoi(vec[1]));  // Assign port to this socket
											   //Accept a connection from any IP using INADDR_ANY
											   //You could pass inet_addr("0.0.0.0") instead to accomplish the 
											   //same thing. If you want only to watch for a connection from a 
											   //specific IP, specify that //instead.
	addr.sin_addr.s_addr = inet_addr(vec[0].c_str());
	// Setup the TCP listening socket
	int iResult = bind(ListenSocket, (LPSOCKADDR)&addr, sizeof(addr));
	assert(iResult != SOCKET_ERROR);


	return listen(ListenSocket, 1);
}

int TcpNode::Accept() {
	//非阻塞accept http://blog.csdn.net/shellching/article/details/7663691
	//select socket可读
	RemoteSocket = accept(ListenSocket, NULL, NULL);
	int iResult;
	ioctlsocket(RemoteSocket, FIONBIO, (unsigned long *)&iResult);//设置成非阻塞模式。  
	assert(iResult != SOCKET_ERROR);
	return RemoteSocket;
}

int TcpNode::Recv() {
	int iResult;
	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;

	do {
		iResult = recv(RemoteSocket, recvbuf, recvbuflen, 0);
		if (iResult > 0) {
			printf("Bytes received: %d\n", iResult);
			string data;
			for (int i = 0; i < iResult; i++)
				data += recvbuf[i];
			return Rx(data);
		}
		else if (iResult == 0)
			break;
		else {
			printf("recv failed with error: %d\n", WSAGetLastError());
		}
	} while (iResult > 0);
	return 0;
}

int TcpDownNode::Tx(const std::string & data) {
	if (m_socket == INVALID_SOCKET) {
		printf("accept failed with error: %d\n", WSAGetLastError());
		closesocket(m_socket);
		WSACleanup();
	}
	else
	{
		send(m_socket, data.c_str(), data.size(), 0);
		printf("send %d\n", data.size());
	}
}

int TcpDownNode::Connect(const string & deal) {

	auto vec = split(deal, ":");
	//Fill out the information needed to initialize a socket…

	target.sin_family = AF_INET; // address family Internet
	target.sin_port = htons(std::stoi(vec[1])); //Port to connect on
	target.sin_addr.s_addr = inet_addr(vec[0].c_str()); //Target IP

	m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //Create socket
	if (m_socket == INVALID_SOCKET)
	{
		printf("Couldn't create the socket\n"); //Couldn't create the socket
	}

	if (connect(m_socket, (SOCKADDR *)&target, sizeof(target)) == SOCKET_ERROR)
	{
		printf("Couldn't connect %s\n", m_deal.c_str());
	}
	ioctlsocket(RemoteSocket, FIONBIO, (unsigned long *)&iResult);//设置成非阻塞模式。  
}

int TcpDownNode::Recv() {
	int iResult;
	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;

	do {
		iResult = recv(m_socket, recvbuf, recvbuflen, 0);
		if (iResult > 0) {
			printf("Bytes received: %d\n", iResult);
			string data;
			for (int i = 0; i < iResult; i++)
				data += recvbuf[i];
			return Rx(data);
		}
		else if (iResult == 0)
			break;
	} while (iResult > 0);
	return 0;
}
