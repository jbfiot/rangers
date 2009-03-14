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
#include "tools.h"
#include "vector.h"

#include <iostream>





class Bof_db
{

	/**
	*
	* Classe Bof_db : Gestion de la base de données de bag of features.
	*
	**/

public:


	Bof_db(std::vector<Vector> centers, Vector sigmas, string db_host="localhost", string db_username="ranger",
		string db_password="GoRangers!", string db_name="bof_db", string table_name="bof");

	~Bof_db();

	void add_bof(Bof bag);
	void add_bof_region(Bof bag);

	void build_tree();

	unsigned int find_nearest_leaf(Vector &bof);
	
	//En public pour les tests
	void get_bof_number(int index, Vector &res, double &mu, double &son1, double &son2);



private:
    string db_name;
    string db_username;
    string db_password;
    string db_host;
    string table_name;
	int nb_k_centers;
    std::vector<Vector> centers;
	Vector sigmas;

	MYSQL* db_connection;
	unsigned int nrows;

	void error_and_exit();

	unsigned int select_vp(int index_parent, int direction, Vector &root);
	void select_random_set_indexes(int index_parent, int direction,
		std::vector<Vector> &sample_set, std::vector<int> &random_indexes,
		unsigned int not_this_one = 0);

    void set_mu_value(int index_root, double median);
	void set_parent_direction_fields(int parent, int direction, double median, int index_median);
	double get_median(int parent, int direction);
	void update_distances(int parent, int direction, Vector &root);
	void set_son_value(int index_parent, int direction, int index_median);
	int count_elems(int parent, int direction, unsigned int not_this_one=0);

	void make_one_step(int index_parent, int direction);

	void set_parent_direction(int index, int index_parent, int direction);

	unsigned int get_root_node();
	

};




#endif /*  bod_db.h */

