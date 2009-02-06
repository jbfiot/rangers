#ifndef BOF_DB
#define BOF_DB

#include "Bof.h"

#include <string>
#include <vector>
#include <assert.h>

#if defined(WIN32) || defined(WIN64)
	#include <winsock.h>
#endif

#include <mysql.h>



#include <iostream>





class Bof_db
{

	/**
	*
	* Classe Bof_db : Gestion de la base de données de features.
	*
	**/

public:
	Bof_db(string db_name);
	~Bof_db();
	void add_bof(Bof bag);
	void build_tree();


private:
	string db_name;
	//MYSQL connection;


};




#endif

