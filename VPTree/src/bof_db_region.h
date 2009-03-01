#ifndef BOF_DB_REGION
#define BOF_DB_REGION

#include "bof_region.h"

#include <string>
#include <vector>
#include <assert.h>

#if defined(WIN32) || defined(WIN64)
	#include <winsock.h>
#endif

#include <mysql.h>
#include "tools.h"
#include "vector.h"

#include <iostream>
#include "feature_db.h"




/**
 * Classe Bof_db : Gestion de la base de données de bag of features.
 **/
class Bof_db_Region
{
public:


	Bof_db_Region(Feature_db *fdb, int nb_k_centers, string db_host="localhost", string db_username="ranger",
		string db_password="GoRangers!", string db_name="bof_db_region", string table_name="bof");

	~Bof_db_Region();

	void add_bof(Bof_Region bag);
	void add_bof_region(Bof_Region bag);

	void build_tree();
	void error_and_exit();

	Feature_db *fdb;



private:
    string db_name;
    string db_username;
    string db_password;
    string db_host;
    string table_name;
	int nb_k_centers;

	MYSQL* db_connection;
	unsigned int nrows;

	unsigned int select_vp(int index_parent, int direction, Bof_Region &root);
	void select_random_set_indexes(int index_parent, int direction,
		std::vector<Vector> &sample_set, std::vector<int> &random_indexes,
		unsigned int not_this_one = 0);

    void set_mu_value(int index_root, double median);
	void set_parent_direction_fields(int parent, int direction, double median, int index_median);
	double get_median(int parent, int direction);
	void update_distances(int parent, int direction, Bof_Region &root);
	void set_son_value(int index_parent, int direction, int index_median);
	int count_elems(int parent, int direction, unsigned int not_this_one=0);

	void make_one_step(int index_parent, int direction);

	void set_parent_direction(int index, int index_parent, int direction);


};




#endif /*  bod_db.h */

