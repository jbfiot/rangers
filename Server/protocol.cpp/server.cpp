/*
Code gérant la partie serveur du programme

*/

#include <iostream>

#include "server.h"
#include "protocol.h"

using namespace std;
using namespace dataprotocol;



Server::Server(int p) 
{
	port = p;
	running = false;
}

int Server::Init() 
{
	struct in_addr MyAddress;
	struct hostent *host;
	char HostName[100];
	strcpy(HostName, "localhost");
	WSADATA wsaData;

	if(WSAStartup(MAKEWORD(2,2), &wsaData ) != 0 )
	{
		cerr <<"WSAStartup failed "<< endl;
		return 1;
	}

	if( gethostname( HostName, 100 ) == SOCKET_ERROR )
	{
		cerr<< "gethostname() failed : "<< WSAGetLastError()  << endl;
		return 1;
	}
	
	if( (host = gethostbyname( HostName ) ) == NULL)
	{
		cerr <<"gethostbyname() failed : "<< WSAGetLastError()<< endl;
		return 1;
	}

	memcpy( &MyAddress.s_addr, host->h_addr_list[0], sizeof( MyAddress.s_addr ) );

	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_port = htons( port );    
	ServerAddr.sin_addr.s_addr = inet_addr( inet_ntoa( MyAddress ) );
	
	cout <<"Server initialised" << endl;    
	return 0;   
}

int Server::Start ()
{
	SOCKADDR_IN  			ClientAddr;
	int          			ClientAddrLen;
	HANDLE       			hProcessThread;
	SOCKET       			NewConnection;
	struct thread_param		p;
   
	if( ( ListeningSocket = socket( PF_INET, SOCK_STREAM, IPPROTO_TCP ) ) == INVALID_SOCKET )
	{
		cerr <<"Can't create socket. Error n° " << WSAGetLastError()<< endl;
		WSACleanup();
		return 1;
	}

	if( bind( ListeningSocket, (SOCKADDR *)&ServerAddr, sizeof( ServerAddr ) ) == SOCKET_ERROR )
	{
		cerr<<"bind failed : "<< WSAGetLastError()<< endl;
		cerr<<"The port may be already used"<< endl;
		closesocket( ListeningSocket );
		WSACleanup();
		return 1;
	}

	if( listen( ListeningSocket, 5 ) == SOCKET_ERROR )
	{
		cerr<<"listen() failed :"<< WSAGetLastError()<< endl;
		closesocket( ListeningSocket );
		WSACleanup();
		return 1;
	}

	cout <<"Server started, listening on "<<port<< endl; 
	running = true;
	ClientAddrLen = sizeof( ClientAddr );
            
	while(running)
	{
		if((NewConnection = accept( ListeningSocket, (SOCKADDR *) &ClientAddr, &ClientAddrLen)) == INVALID_SOCKET)
		{
			cerr  <<"accept failed :"<< WSAGetLastError() << endl;;
			closesocket( ListeningSocket );
			WSACleanup();
			return 1;
		}
		p.ser = this;
		p.soc = NewConnection;
		
		cout << "client connected ::  IP : "<<inet_ntoa( ClientAddr.sin_addr )<< " ,port = "<<ntohs( ClientAddr.sin_port )<< endl;
	
		hProcessThread = CreateThread(NULL, 0,&Server::ThreadLauncher, &p,0,NULL);
		if ( hProcessThread == NULL )
		{                       
			cerr << "CreateThread failed : " <<GetLastError()<< endl;
		}

	}
	return 0;     
}

int Server::Pause ()
{
	running = false;
	cout <<"Server paused"<< endl;
	closesocket( ListeningSocket );
	return 0; 
}

DWORD Server::ClientThread(SOCKET soc)
{
	cout << "Client connected\nThread started" << endl;
	string cmd;
	Image image2;
	

	Protocol Client(soc);
	cout << "Waiting for a command." << endl;
	cmd = Client.GetCmd();

	cout << cmd.c_str() << endl;
	
	if(cmd.compare("SENDIMAGE") == 0)
	{
		Client.GetImage(image2);
	}

	return 0;   
}

