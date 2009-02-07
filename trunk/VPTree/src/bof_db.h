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
	* Classe Bof_db : Gestion de la base de données de bag of features.
	*
	**/

public:
	Bof_db();
	~Bof_db();
	void add_bof(Bof bag);
	void build_tree();
	void error_and_exit();

private:
	MYSQL* db_connection;




};




#endif /*  bod_db.h */

