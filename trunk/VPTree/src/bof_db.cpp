#include "bof_db.h"

#include <sstream>

template <class T>
inline std::string to_string (const T& t)
{
std::stringstream ss;
ss << t;
return ss.str();
}


/**
*   Constructor
*/


Bof_db::Bof_db (string db_host, string db_username, string db_password, string db_name, string table_name,int nb_k_centers){

    this->db_name = db_name;
    this->db_username = db_username;
    this->db_password = db_password;
    this->db_host = db_host;
    this->table_name = table_name;
    this->nb_k_centers = nb_k_centers;


    /**
    *   Server Connexion
    */
	if (!(db_connection = mysql_init(NULL))) {
		error_and_exit();

	}

	if (mysql_real_connect(db_connection,db_host.c_str(),db_username.c_str(),db_password.c_str(),NULL,0,NULL,0)) {
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
	table_creation_query+=" (Bof_ID int (10) NOT NULL auto_increment,";

	string test="yeah";

	for (unsigned int i=1; i<=nb_k_centers;i++){
	    table_creation_query+="Coeff";
	    table_creation_query+=to_string(i);
	    table_creation_query+=" int (3) NOT NULL,";
	}
	table_creation_query+=" Parent int(10) NOT NULL, Direction int(2) NOT NULL,";

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
    string add_bof_query = "INSERT INTO ";
    add_bof_query+=db_name;
}
