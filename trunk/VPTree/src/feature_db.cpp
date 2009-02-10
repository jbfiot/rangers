
#include "feature_db.h"

#include <sstream>

template <class T>
inline std::string to_string (const T& t)
{
std::stringstream ss;
ss << t;
return ss.str();
}


#define NB_COEFF_FEATURES 128


/**
*   Constructor
*/


Feature_db::Feature_db (string db_host, string db_username,
				string db_password, string db_name, string table_name)
{
    this->db_name = db_name;
    this->db_username = db_username;
    this->db_password = db_password;
    this->db_host = db_host;
    this->table_name = table_name;

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
	table_creation_query+=" (Feature_ID int (10) NOT NULL auto_increment,X INT NOT NULL DEFAULT 0, Y INT NOT NULL DEFAULT 0,";

	string test="yeah";

	for (unsigned int i=1; i<=NB_COEFF_FEATURES;i++){
	    table_creation_query+="Coeff";
	    table_creation_query+=to_string(i);
	    table_creation_query+=" DOUBLE NOT NULL,";
	}

	table_creation_query+=" PRIMARY KEY(Feature_ID))";

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
Feature_db::~Feature_db(){
    mysql_close(db_connection);
    cout << "Closing connection: OK."<<endl;
}


/**
*   Error function (display error and exit program).
*/
void Feature_db::error_and_exit(){
    printf("Error %u: %s\n", mysql_errno(db_connection), mysql_error(db_connection));
	system("pause");
    exit(4);


}

/**
*   Fill the table with random
*/

void Feature_db::fill_with_random(int nb_features) {

    int* random_coeff = get_random_set_indexes(NB_COEFF_FEATURES,1000); // 1000 : max du coeff. (totalement arbitraire)


    string fill_with_random_query = "INSERT INTO ";
    fill_with_random_query+=table_name;
    fill_with_random_query+=" (";

    for (unsigned int i=1; i<=NB_COEFF_FEATURES; i++){
        fill_with_random_query+="Coeff";
        fill_with_random_query+=to_string(i);
        if (i!=NB_COEFF_FEATURES) {
            fill_with_random_query+=",";
        }
    }

    fill_with_random_query+=") VALUES (";

    for (unsigned int i=1; i<=NB_COEFF_FEATURES; i++){
        fill_with_random_query+=to_string(random_coeff[i-1]);
        if (i!=NB_COEFF_FEATURES) {
            fill_with_random_query+=",";
        }
    }
    fill_with_random_query+=")";
	cout << fill_with_random_query << endl;

    if (!mysql_query(db_connection, fill_with_random_query.c_str())) {
	    cout << "Fill-with-random-query: OK"<<endl;
	}
	else {
        error_and_exit();
	}

}




