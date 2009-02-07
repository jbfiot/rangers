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
#include "siftset.h"





class Bof_db
{

	/**
	*
	* Classe Bof_db : Gestion de la base de données de bag of features.
	*
	**/

public:


	Bof_db(string db_host="localhost", string db_username="ranger", string db_password="GoRangers!", string db_name="bof_db", string table_name="bof", int nb_k_centers=SAMPLE_LENGTH_FOR_K_MEANS);

	~Bof_db();
	void add_bof(Bof bag);
	void build_tree();
	void error_and_exit();

private:
    string db_name;
    string db_username;
    string db_password;
    string db_host;
    string table_name;
    int nb_k_centers;

	MYSQL* db_connection;
	unsigned int nrows;




};




#endif /*  bod_db.h */

