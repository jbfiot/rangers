#include "server.h"

#include <iostream>

using namespace std;

int main(void) {
	Server *MyServer = new Server(60000);
	if(MyServer->Init() != 0) {
		cerr << "Initialisation failed" << endl;
		return 1;
	}
	if(MyServer->Start() != 0) {
		cerr << "Can't start server" << endl;
		return 1;
	}
	return 0;
}
