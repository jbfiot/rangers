#include "bof_db.h"

#include <sstream>

template <class T>
inline std::string to_string (const T& t)
{
std::stringstream ss;
ss << t;
return ss.str();
}


#define db_host "localhost"
#define db_username "ranger"
#define db_password "GoRangers!"
#define db_name "bof_db"
#define table_name "bof"

#define COEFF_NB 10 // temporary value before the number of k-centers

/**
*   Constructor
*/

Bof_db::Bof_db (){

    /**
    *   Server Connexion
    */
	if (!(db_connection = mysql_init(NULL))) {
		error_and_exit();

	}

	if (mysql_real_connect(db_connection,db_host,db_username,db_password,NULL,0,NULL,0)) {
	    // Notice we do not specify the database because it might not exists.
	    cout << "SQL server connection: OK"<<endl;
	}
	else {
		error_and_exit();
	}


    /**
    *   Database creation
    */
	string db_creation_query = "CREATE DATABASE IF NOT EXISTS ";
	db_creation_query+=db_name;


	if (!mysql_query(db_connection, db_creation_query.c_str())) {
	    cout << "Database creation query: OK"<<endl;
	}
	else {
        error_and_exit();
	}


    /**
    *   Database selection
    */
	string db_selection_query = "USE ";
	db_selection_query+=db_name;

	if (!mysql_query(db_connection, db_selection_query.c_str())) {
	    cout << "Database selection query: OK"<<endl;
	}
	else {
        error_and_exit();
	}


    /**
    *   Table creation
    */
	string table_creation_query = "CREATE TABLE IF NOT EXISTS ";
	table_creation_query+=table_name;
	table_creation_query+=" (Bof_ID int (11) NOT NULL auto_increment,";

	string test="yeah";

	for (unsigned int i=1; i<=COEFF_NB;i++){
	    table_creation_query+="Coeff";
	    table_creation_query+=to_string(i);
	    table_creation_query+=" int (3) NOT NULL,";
	}

	table_creation_query+=" PRIMARY KEY(Bof_ID))";



	if (!mysql_query(db_connection, table_creation_query.c_str())) {
        cout << "Table creation query: OK."<<endl;
	}
	else {
        error_and_exit();
	}



}


/**
*   Destructor
*/
Bof_db::~Bof_db(){
    mysql_close(db_connection);
    cout << "Closing connection: OK."<<endl;
}


/**
*   Error function (display error and exit program).
*/
void Bof_db::error_and_exit(){
    printf("Error %u: %s\n", mysql_errno(db_connection), mysql_error(db_connection));
    exit(4);


}

/**
*   Add-feature function (add a line to the table).
*/

void Bof_db::add_bof(Bof bag) {
    // TO-DO
}
