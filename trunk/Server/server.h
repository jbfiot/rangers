
#ifndef SERVER
#define SERVER


#if defined(WIN32) || defined(WIN64)
	#include <winsock2.h>
#endif
class Server;



struct thread_param
{
       Server* ser;
       SOCKET soc;
};


class Server 
{
private: 
	int port;
	SOCKET ListeningSocket;
	bool running;
	SOCKADDR_IN ServerAddr;
	DWORD ClientThread(SOCKET);

public:
	Server(int p);
	int Init();
	int Start();
	int Pause();
	static DWORD WINAPI ThreadLauncher(void *p)
	{
		struct thread_param *Obj = reinterpret_cast<struct thread_param*>(p);               
		Server *s = Obj->ser;                          
		return s->ClientThread(Obj->soc);       
	}
};




#endif
