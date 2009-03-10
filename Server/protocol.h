#include <iostream>
#include "winsock2.h"
#if defined(WIN32) || defined(WIN64)
	#include <winsock2.h>
#endif
#define BUF_SIZE 16384

#ifndef PROTOCOL
#define PROTOCOL

using namespace std;


	class Image {


	public:
		int **data;
		int x_size;
		int y_size;
		Image();
		Image(const Image &image);
		Image(const int x, const int y);
		
		~Image();
	};

	class Protocol {
	private:
		SOCKET soc;
		char buf[BUF_SIZE];
		string buf_str;
		int nb_recv;
		string recvline();
		int recvint();
		int recvint(string line);
		void recvintrow(int* row,int y); 

	public:
		Protocol(SOCKET socket); 


		string GetCmd();
		int SendCmd(string cmd);
		void GetImage(Image &image);
		int SendImage(Image image);

	};
	
	


#endif

	