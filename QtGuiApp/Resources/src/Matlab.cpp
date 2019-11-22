#include "Matlab.H"

void Matlab::MatlabConnect()
{
	Port = 54000;
	tram1.Altitude = 0;
	tram1.Cap = 0;
	tram1.HSpeed = 0;
	tram1.VSpeed = 0;
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
	MatlabLisning();
}

void Matlab::MatlabDisconnect()
{
	qDebug("hello");
	timer->stop();
	disconnect(timer, SIGNAL(timeout()), this, SLOT(MatlabSend()));
	/*close the socket*/
	closesocket(clientSocket);

	/*cleanup winsock*/
	WSACleanup();


}

void Matlab::MatlabLisning()
{
	/*tell winsock the socket is for listening*/
	listen(listening, SOMAXCONN);

	/*wait for a connection*/



	clientSocket = accept(listening, (sockaddr*)&client, &clientSize);

	char host[NI_MAXHOST];
	char service[NI_MAXHOST];

	ZeroMemory(host, NI_MAXHOST);
	ZeroMemory(service, NI_MAXHOST);

	if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0) {
		qDebug("%s connected on port %s",host, service);
	}
	else {
		inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
		//qDebug() << host << " connected on port " <<
		//	ntohs(client.sin_port) ;
	}

	/*close listening socket*/
	closesocket(listening);
	
	
	connect(timer, SIGNAL(timeout()), this, SLOT(MatlabSend()));
	timer->start(25);
}

void Matlab::MatlabSend()
{
	/*while loop: accept and echo message back to client*/
	char buf[4096];

		ZeroMemory(buf, 4096);

		//wait for client data
		/*int bytesReceived = recv(clientSocket, buf, 4096, 0);
		if (bytesReceived == 0) {
			//cout << "client disconnected" << endl;
			MatlabDisconnect();
			return;
		}*/

		//echo message back to client
		int size = sizeof(double);
		memcpy(buf, &(tram1.Altitude), sizeof(double));
		memcpy(buf+size, &(tram1.Cap), sizeof(double));
		memcpy(buf+(2*size), &(tram1.VSpeed), sizeof(double));
		memcpy(buf+(3*size), &(tram1.HSpeed), sizeof(double));
		//buf[(4 * size) + 1] = '\0';
		send(clientSocket, buf, (4 * size), 0);
}




void Matlab::SetAlt(double altitude) {
	tram1.Altitude = altitude;
}
void Matlab::SetCap(double Cap) {
	tram1.Cap = Cap;
}
void Matlab::SetVSpeed(double VSpeed) {
	tram1.VSpeed = VSpeed;
}
void Matlab::SetHSpeed(double HSpeed) {
	tram1.HSpeed = HSpeed;
}


void Matlab::GetThrottle(double data) {
	qDebug("%f", data);
}

void Matlab::GetYoke(double datax, double datay ) {
	qDebug("yoke : %f | %f", datax, datay);
}




