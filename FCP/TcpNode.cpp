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
	FD_ZERO(&readfds);
	FD_ZERO(&writefds);
	FD_ZERO(&exceptfds);
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
	listen(ListenSocket, 1);
	u_long ioctl_opt = 1;
	if (ioctlsocket(ListenSocket, FIONBIO, &ioctl_opt) == SOCKET_ERROR) {
		fprintf(stderr, "ioctlsocket failed %d\n", WSAGetLastError());
		WSACleanup();
		return -1;
	}

	return 0;
}
/*
return :: >0 成功
		  <0 错误
		  =0 等待
*/
int TcpNode::Accept() {
	//非阻塞accept http://blog.csdn.net/shellching/article/details/7663691
	//select socket可读
	
	FD_SET(ListenSocket, &readfds);
	timeval t;//非阻塞，0等待
 	auto  i = select(0, &readfds, &writefds, &exceptfds, &t);
	if (i == SOCKET_ERROR) {
		fprintf(stderr, "select failed %d\n", WSAGetLastError());
		return i;
	}
	else if (i == 0) {
		return i;
	}

	if (FD_ISSET(ListenSocket, &readfds)) {
		//
		// close the previous client socket.
		// We must also    clear it from the fdset    to prevent select()
		// from    failing.
		//
		closesocket(RemoteSocket);
		FD_CLR(RemoteSocket, &readfds);
		FD_CLR(RemoteSocket, &writefds);
		struct sockaddr from;
		int fromlen = sizeof(from);
		RemoteSocket = accept(ListenSocket, (struct sockaddr*)&from, &fromlen);
		if (RemoteSocket == INVALID_SOCKET) {
			fprintf(stderr, "accept failed %d\n", WSAGetLastError());
			return -1;
		}
		FD_SET(RemoteSocket, &writefds);
		FD_SET(RemoteSocket, &readfds);

		u_long ioctl_opt = 1;
		if (ioctlsocket(RemoteSocket, FIONBIO, &ioctl_opt) == SOCKET_ERROR) {
			fprintf(stderr, "RemoteSocket ioctlsocket failed %d\n", WSAGetLastError());
			WSACleanup();
			return -1;
		}

		Logger->info("accept from {}", from.sa_data);
		return 1;
	}
	// 非阻塞读写
	//if (FD_ISSET(RemoteSocket, &readfds)) {
	//	//
	//	// socket is ready to read,    i.e., there    is data    on the socket.
	//	//
	//	/*if (ReadAndEcho(RemoteSocket,Buffer,sizeof(Buffer))<0) {
	//	fprintf(stderr,"terminating connection\n");
	//	FD_CLR(RemoteSocket,&readfds);
	//	FD_CLR(RemoteSocket,&writefds);
	//	closesocket(RemoteSocket);
	//	continue;
	//	}*/
	//}
	//if (FD_ISSET(RemoteSocket, &writefds)) {
	//	/*if (WriteMessage(RemoteSocket,Buffer,sizeof(Buffer))    <=0) {
	//	fprintf(stderr,"terminating connection\n");
	//	FD_CLR(RemoteSocket,&readfds);
	//	FD_CLR(RemoteSocket,&writefds);
	//	closesocket(RemoteSocket);
	//	continue;
	//	}*/
	//}
	//FD_SET(RemoteSocket, &writefds);
	//FD_SET(RemoteSocket, &readfds);
	return -1;
}

/*
return :: 0 有连接无数据
		 >0 收到包的个数
		 <0 连接断开出错
*/
int TcpNode::Recv() {
	//timeval t;//非阻塞，0等待
	//auto  i = select(0, &readfds, &writefds, &exceptfds, &t);
	//if (FD_ISSET(RemoteSocket, &readfds))
	//{
	//	return 0;
	//}
		
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
		else if (WSAGetLastError() == WSAEWOULDBLOCK) {
			return 0;
		}
		else {
			printf("recv failed with error: %d\n", WSAGetLastError());
			FD_CLR(RemoteSocket, &readfds);
			FD_CLR(RemoteSocket, &writefds);
			closesocket(RemoteSocket);
			return -1;
		}
	} while (iResult > 0);
	FD_SET(RemoteSocket, &writefds);
	FD_SET(RemoteSocket, &readfds);
	return 0;
}

int TcpDownNode::Tx(const std::string & data) {
	if (m_socket == INVALID_SOCKET) {
		printf("accept failed with error: %d\n", WSAGetLastError());
		closesocket(m_socket);
		WSACleanup();
		return -1;
	}
	else
	{
		return send(m_socket, data.c_str(), data.size(), 0);
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
	return 1;
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
