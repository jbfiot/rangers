#include "pic_db.h"
#include <vector>


/**
*   Constructor
*/
Pic_db::Pic_db(string db_host, string db_username,string db_password, string db_name, string table_name, path data_folder){

    this->data_folder = data_folder;
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
	table_creation_query+=" (Pic_ID int NOT NULL auto_increment,Filename TEXT,";



	table_creation_query+=" PRIMARY KEY(Pic_ID))";

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
Pic_db::~Pic_db(){
	mysql_close(db_connection);
	cout << "Closing connection: OK."<<endl;
}


/**
*   Error function (display error and exit program).
*/
void Pic_db::error_and_exit(){
	printf("Error %u: %s\n", mysql_errno(db_connection), mysql_error(db_connection));
	system("pause");
	exit(4);
}




void Pic_db::add_file_to_db(string filename)
{
    cout << "      " << filename << endl;

	string fill_query = "INSERT INTO ";
	fill_query+=table_name;
	fill_query+=" (";
	fill_query+="Filename";

	fill_query+=") VALUES (\"";
	fill_query+=filename;
	fill_query+="\")";

	if (!mysql_query(db_connection, fill_query.c_str())) {
		//cout << "Fill-query: OK"<<endl;
	}
	else {
		error_and_exit();
	}

}





void Pic_db::add_files_to_db(std::vector<string> &files)
{
	string fill_query = "INSERT INTO ";
	fill_query+=table_name;
	fill_query+=" (";
	fill_query+="Filename";

	fill_query+=") VALUES (\"";

	for (int i=1;i<=files.size();i++) {
        fill_query+=files[i-1];
        if (i!=files.size())
            fill_query+="\"),(\"";
	}

	fill_query+="\")";

	if (!mysql_query(db_connection, fill_query.c_str())) {
		//cout << "Fill-query: OK"<<endl;
	}
	else {
		error_and_exit();
	}



}



void Pic_db::process_folder(path folder,std::vector<string> &files) {
    cout << "Processing "<<folder.native_directory_string() << " folder... "<<endl;
    if ( !exists(folder ) ) {
        cout << "Folder not found. Aborting.";
        exit(1);
    }

    directory_iterator itr(folder), end_itr;

    for ( ; itr != end_itr; ++itr ){
        /*if (is_directory(itr->status())){
            // Pour la recursion, non utilise pour l'instant.
            process_folder(itr->path());
        }
        else*/ if (is_regular(itr->status())) {
            string filename = itr->leaf();
            if (filename.substr(filename.length()-3,3) == "jpg") {
                //cout<<itr->leaf()<< " => jpg found!!"<< endl;
                //add_file_to_db(folder.native_directory_string()+"/"+itr->leaf());
                //add_file_to_db(itr->leaf());
                files.push_back(itr->leaf());
            }
        }

    }
    cout << "Done." << endl;
}

void Pic_db::fill_db(){
    std::vector<string> files;
    process_folder(data_folder,files);
    add_files_to_db(files);

}
