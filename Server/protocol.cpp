#include <string>

#include "protocol.h"
#include <string>
#include <sstream>




	Protocol::Protocol(SOCKET socket) 
	{
		nb_recv = 0;
		soc = socket;
	}

	string Protocol::recvline() 
	{

		if ((buf_str.length() == 0) || buf_str.find("\r") == string::npos ) 
		{ 
			if (( nb_recv = recv(soc, buf, BUF_SIZE, 0)) == -1)
			{
				cout << "Connection.recvline(): error when calling recv()\n";
			}
			buf[nb_recv] = '\0';
			buf_str.append(string(buf));
		
		}

		int ind = buf_str.find("\r\n");
		buf[0] = '\0';

		string line((buf_str.substr(0, ind).c_str()));
		buf_str.erase(0,ind+2);

		return line;

	}

	int Protocol::recvint()
	{
		int result = 0;
		string line = recvline();

		for(int i = 0; i < line.length() ; i++) 
			result = result*10 + line[i] - '0';
		return result;
	}
	int Protocol::recvint(string line) 
	{	
		int result = 0;
		
		for(int i = 0; i < line.length() ; i++) 
			result = result*10 + line[i] - '0';
		return result;
	}
	
	int * Protocol::recvintrow(int y)
	{
		int *row = new int[y];
		string line = recvline();
		string subline;
		size_t pos;
		for(int i = 0; i < y; i++)
		{
			pos=line.find(" ");
			subline=line.substr(0,pos);
			row[i] = recvint(subline);
			line.erase(0, line.find(" ") +1);
		}

		return row;
	}
	// Le serveur attend une commande
	string Protocol::GetCmd() 
	{
		string cmd;
		cmd = recvline();
		return cmd;
	}

	void Protocol::GetImage(Image &image) 
	{
		string line;

		image.x_size = recvint();
		image.y_size = recvint();
		int *row = new int[image.y_size];
		image.data = new int*[image.x_size];
		for(int i = 0; i< image.x_size; i++) 
		{
			image.data[i] =  new int[image.y_size];
		}

		for(int i = 0; i < image.x_size;i++) 
		{
			row = recvintrow(image.y_size);
			for(int j = 0; j < image.y_size; j++)
			{
				image.data[i][j] = row[j];
			}
			cout << i << endl;
		}
	}

	int Protocol::SendImage(Image &image)
	{
		SendCmd("SENDIMAGE");
		int control = 0;
		string line;
		ostringstream size_im;
		size_im << image.x_size << "\r\n" << image.y_size << "\r\n";
		line = size_im.str();
		send(soc,line.c_str(),line.length(),0);


		for(int i = 0; i < image.x_size;i++)
		{
			line="";
			for(int j = 0; j < image.y_size; j++)
			{
				ostringstream oss;
	
				oss << image.data[i][j];
				
	
				line.append( oss.str().append(" "));
			}
			line.erase(line.length()-1,1);
			line.append("\r\n");
			if(send(soc, line.c_str(), line.length(), 0) == -1) 
				control = -1;

		}
		return control;
	}

	int Protocol::SendCmd(string cmd) 
	{
		int control;
		control = send(soc, cmd.append("\r\n").c_str(), cmd.length()+2, 0);
		return control;
	}


	// Methodes de la classe Image du namespace dataprotocol

	Image::Image() 
	{
		x_size = 1;
		y_size = 1;
		data = new int*[1];
		data[1] =new int[1];

	}
	Image::Image(const int x,const int y) 
	{
		x_size = x;
		y_size = y;
		
		data = new int*[x];
		for(int i = 0; i< x; i++) 
		{
			data[i] =  new int[y];
		}

	}

	// Copy constructor
	Image::Image(const Image &image) 
	{
		
		x_size = image.x_size;
		y_size = image.y_size;

		data = new int*[x_size];
		for(int i = 0; i< x_size; i++)
		{
			data[i] =  new int[y_size];
		}
		for(int i = 0; i < x_size; i++) 
		{
			for(int j = 0; j < y_size; j++) 
			{
				data[i][j] =  image.data[i][j];
			}
		}
	}
	
	// Destructor
	Image::~Image() 
	{
		for(int i = 0; i < x_size; i++ )
			delete data[i];
		delete [] data;
	}



	