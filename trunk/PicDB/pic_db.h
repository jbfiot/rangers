#ifndef Pic_db_H
#define Pic_db_H

#include <iostream>
#include <string>
#include "boost/filesystem.hpp"


#if defined(WIN32) || defined(WIN64)
	#include <winsock.h>
#endif

#include <mysql.h>


using namespace std;
using namespace boost::filesystem;


class Pic_db
{

 public:
    Pic_db(string db_host="localhost", string db_username="ranger",string db_password="GoRangers!", string db_name="pic_db", string table_name="pics", path data_folder="./Data");
    ~Pic_db();
    void fill_db();


private:
    path data_folder;

    string db_name;
    string db_username;
    string db_password;
    string db_host;
    string table_name;

	MYSQL* db_connection;

    void add_file_to_db(string filename);
    void process_folder(path folder,std::vector<string> &files);
    void error_and_exit();
    void add_files_to_db(std::vector<string> &files);

};


#endif
