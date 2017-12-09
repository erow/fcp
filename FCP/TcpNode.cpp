#include "TcpNode.h"
#include <thread>
#include "Node_.h"
#pragma comment (lib, "Ws2_32.lib")

std::mutex TcpNode::m_mtx;
int TcpNode::Tx(const std::string & data)
{
	if (RemoteSocket == INVALID_SOCKET) {
		Logger->warn("error:{}. Tx without connection ", WSAGetLastError());
		//closesocket(ListenSocket);
		//WSACleanup();
	}
	else
	{
		send(RemoteSocket, data.c_str(), data.size(), 0);
		Logger->info("send {}", data.size());
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
	int t = deal.find(':');
	string ip = deal.substr(0,t);
	string port = deal.substr(t + 1);
	FD_ZERO(&readfds);
	FD_ZERO(&writefds);
	FD_ZERO(&exceptfds);
	SOCKADDR_IN addr; // The address structure for a TCP socket
	addr.sin_family = AF_INET;      // Address family
	addr.sin_port = htons(std::stoi(port));  // Assign port to this socket
											   //Accept a connection from any IP using INADDR_ANY
											   //You could pass inet_addr("0.0.0.0") instead to accomplish the 
											   //same thing. If you want only to watch for a connection from a 
											   //specific IP, specify that //instead.
	addr.sin_addr.s_addr = inet_addr(ip.c_str());
	// Setup the TCP listening socket
	int iResult = bind(ListenSocket, (LPSOCKADDR)&addr, sizeof(addr));
	assert_log(iResult != SOCKET_ERROR);
	listen(ListenSocket, 1);
	if (!block)
	{
		u_long ioctl_opt = 1;
		if (ioctlsocket(ListenSocket, FIONBIO, &ioctl_opt) == SOCKET_ERROR) {
			fprintf(stderr, "ioctlsocket failed {}\n", WSAGetLastError());
			WSACleanup();
			return -1;
		}
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
	m_buffer.clear();
	msg_size = 0;
	struct sockaddr from;
	int fromlen = sizeof(from);
	if (!block)
	{
		FD_SET(ListenSocket, &readfds);
		timeval t;//非阻塞，0等待
		auto  i = select(0, &readfds, &writefds, &exceptfds, &t);
		if (i == SOCKET_ERROR) {
			fprintf(stderr, "select failed {}\n", WSAGetLastError());
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

			RemoteSocket = accept(ListenSocket, (struct sockaddr*)&from, &fromlen);
			if (RemoteSocket == INVALID_SOCKET) {
				Logger->warn("accept failed {}\n", WSAGetLastError());
				return -1;
			}
			FD_SET(RemoteSocket, &writefds);
			FD_SET(RemoteSocket, &readfds);

			u_long ioctl_opt = 1;
			if (ioctlsocket(RemoteSocket, FIONBIO, &ioctl_opt) == SOCKET_ERROR) {
				Logger->error("RemoteSocket ioctlsocket failed {}\n", WSAGetLastError());
				//WSACleanup();
				return -1;
			}
			return 1;
		}
	}
	else {
		closesocket(RemoteSocket);
		RemoteSocket = accept(ListenSocket, (struct sockaddr*)&from, &fromlen);
		if (RemoteSocket == INVALID_SOCKET) {
			Logger->warn("accept failed {}\n", WSAGetLastError());
			return -1;
		}
	}
	Logger->info("accept from {}:{}", inet_ntoa(((sockaddr_in*)&from)->sin_addr), ((sockaddr_in*)&from)->sin_port);
	return 1;
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
			Logger->debug("Bytes received: {}", iResult);
			string data;
			for (int i = 0; i < iResult; i++)
				data += recvbuf[i];

			m_mtx.lock();
			int ret = Rx(data);
			m_mtx.unlock();
			return ret;
		}
		else if (WSAGetLastError() == WSAEWOULDBLOCK) {
			return 0;
		}
		else {
			Logger->info("recv failed with error: {}", WSAGetLastError());
			if (!block) {
				FD_CLR(RemoteSocket, &readfds);
				FD_CLR(RemoteSocket, &writefds);
			}
			closesocket(RemoteSocket);
			return -1;
		}
	} while (iResult > 0);
	if (!block) {
		FD_CLR(RemoteSocket, &readfds);
		FD_CLR(RemoteSocket, &writefds);
	}
	return 0;
}

void TcpNode::AutoRun()
{
	m_thread = std::thread([&]() {
		while (true)
		{
			Accept();
			while (true)
			{
				int ret = Recv();
				if (ret < 0)
					break;
			}
		}
	});
}

int TcpDownNode::Tx(const std::string & data) {
	if (m_socket == INVALID_SOCKET) {
		Logger->debug("accept failed with error: {}\n", WSAGetLastError());
		closesocket(m_socket);
		Connect(m_deal);
		Logger->info("re connected!");
		return -1;
	}
	else
	{
		return send(m_socket, data.c_str(), data.size(), 0);
	}
}

int TcpDownNode::Connect(const string & deal) {
	m_deal = deal;
	int t = deal.find(':');
	string ip = deal.substr(0, t);
	string port = deal.substr(t + 1);
	//Fill out the information needed to initialize a socket…

	target.sin_family = AF_INET; // address family Internet
	target.sin_port = htons(std::stoi(port)); //Port to connect on
	target.sin_addr.s_addr = inet_addr(ip.c_str()); //Target IP

	m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //Create socket
	if (m_socket == INVALID_SOCKET)
	{
		Logger->debug("Couldn't create the socket\n"); //Couldn't create the socket
	}

	if (connect(m_socket, (SOCKADDR *)&target, sizeof(target)) == SOCKET_ERROR)
	{
		Logger->debug("Couldn't connect {}\n", m_deal.c_str());
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
			Logger->debug("Bytes received: {}\n", iResult);
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
