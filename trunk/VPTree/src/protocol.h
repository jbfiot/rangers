#include <iostream>
#if defined(WIN32) || defined(WIN64)
	#include <winsock2.h>
#endif
#define BUF_SIZE 1024

using namespace std;


namespace dataprotocol {
	class Image;
	class Protocol {
	private:
		SOCKET soc;
		char buf[BUF_SIZE];
		string buf_str;
		int nb_recv;
		string recvline();
		int recvint();
		int recvint(string line);
		int * recvintrow(int y); 

	public:
		Protocol(SOCKET socket); 


		string GetCmd();
		int SendCmd(string cmd);
		void GetImage(Image &image);
		int SendImage(Image image);

	};
	
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


}

	