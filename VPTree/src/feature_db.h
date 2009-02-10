
#ifndef FEATURE_DB
#define FEATURE_DB

#include "feature_db.h"

#include <string>
#include <vector>
#include <assert.h>

#if defined(WIN32) || defined(WIN64)
	#include <winsock.h>
#endif

#include <mysql.h>


#include <iostream>
#include "siftset.h"
#include "tools.h"



class Feature_db
{

	/**
	*
	* Classe Feature_db : Gestion de la base de données de features.
	*
	**/

public:


	Feature_db(string db_host="localhost", string db_username="ranger",string db_password="GoRangers!", string db_name="feature_db", string table_name="features");

	~Feature_db();
    void fill_with_random(int nb_features);

	void error_and_exit();

private:
    string db_name;
    string db_username;
    string db_password;
    string db_host;
    string table_name;

	MYSQL* db_connection;


};




#endif /*  feature_db.h */

