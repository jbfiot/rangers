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
#include "tools.h"
#include <string>
#include "vector.h"
#include "feature.h"

#define SAMPLE_LENGTH_FOR_K_MEANS 100


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
	void insert_feature(Feature &feature);
    void fill_with_random(int nb_images, int nb_features);

	void do_k_means(int k, std::vector<Vector> &centers);
	unsigned int get_nbfeatures();
	unsigned int get_nbimages();

	//A IMPLEMENTER
	void get_feature_number(int index, Vector &vec);
	void get_all_features_in_image(int index, std::vector<Feature> &features);



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

