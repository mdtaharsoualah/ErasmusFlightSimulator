#include "MatlabRcv.h"



void MatlabRcv::MatlabRcvStart()
{
	Port = 53000;
	/*init socket*/


	int wsOk = WSAStartup(ver, &wsData);
	if (wsOk != 0) {
		//error
	}

	/*Create a socket*/
	listening = socket(AF_INET, SOCK_STREAM, 0);
	if (listening == INVALID_SOCKET) {
		//error
	}

	/*Bind an ip addres and port to socket*/

	hint.sin_family = AF_INET;
	hint.sin_port = htons(Port); //conversion big and litle endian
	hint.sin_addr.S_un.S_addr = INADDR_ANY;

	bind(listening, (sockaddr*)&hint, sizeof(hint));
	MatlabLisningRcv();
}

void MatlabRcv::MatlabDisconnectRcv()
{
	qDebug("hello");
	/*close the socket*/
	closesocket(clientSocket2);

	/*cleanup winsock*/
	WSACleanup();


}

void MatlabRcv::MatlabLisningRcv()
{
	/*tell winsock the socket is for listening*/
	listen(listening, SOMAXCONN);

	/*wait for a connection*/



	clientSocket2 = accept(listening, (sockaddr*)&client, &clientSize);

	char host[NI_MAXHOST];
	char service[NI_MAXHOST];

	ZeroMemory(host, NI_MAXHOST);
	ZeroMemory(service, NI_MAXHOST);

	if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0) {
		qDebug("%s connected on port %s", host, service);
	}
	else {
		inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
		//qDebug() << host << " connected on port " <<
		//	ntohs(client.sin_port) ;
	}

	/*close listening socket*/
	closesocket(listening);

	MatlabRcvFun();
}

void MatlabRcv::MatlabRcvFun() {
	char buf[MAX_LENGTH_BUF];
	int  bytesReceived = recv(clientSocket2, buf, MAX_LENGTH_BUF, 0);
	if (bytesReceived == 0) {
		//cout << "client disconnected" << endl;
		emit MatlabDisconnect();
		return;
	}
	memcpy(&Throttle, buf, size);
	//memcpy(&YokeX, buf + size, size);
	//memcpy(&YokeY, buf + (2 * size), size);
	emit MatlabThrottle(Throttle);
	//emit MatlabYoke(YokeX, YokeY);
	MatlabRcvFun();
}