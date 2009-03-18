#include "bof_db_region.h"
using namespace std;

#define RANDOM_SET_MAX_LENGTH 100
#define MAX_ROWS_BY_DISTANCE_REQUEST 100

/**
 *   Constructor
 **/
Bof_db_Region::Bof_db_Region (Feature_db *feature_db,  int k, string db_host, string db_username,
				string db_password, string db_name, string table_name)
{
	this->db_name = db_name;
	this->db_username = db_username;
	this->db_password = db_password;
	this->db_host = db_host;
	this->table_name = table_name;
	this->nb_k_centers = k;
	this->fdb = feature_db;

	//Server Connexion
	if (!(db_connection = mysql_init(NULL)))
		error_and_exit();

	if (mysql_real_connect(db_connection,db_host.c_str(),db_username.c_str(),db_password.c_str(),NULL,0,NULL,0))
		// Notice we do not specify the database because it might not exists.
		cout << "SQL server connection: OK"<<endl;
	else
		error_and_exit();

	//Database creation
	string db_creation_query = "CREATE DATABASE IF NOT EXISTS ";
	db_creation_query += db_name;


	if (!mysql_query(db_connection, db_creation_query.c_str()))
		cout << "Database creation query: OK"<<endl;
	else
		error_and_exit();


	//Database selection
	string db_selection_query = "USE ";
	db_selection_query += db_name;

	if (!mysql_query(db_connection, db_selection_query.c_str()))
		cout << "Database selection query: OK"<<endl;
	else
		error_and_exit();


	//Table creation
	string table_creation_query = "CREATE TABLE IF NOT EXISTS ";
	table_creation_query += table_name;
	table_creation_query += " (Bof_Region_ID int NOT NULL auto_increment,";

	for (unsigned int i=1; i<=this->nb_k_centers; i++)
	{
		table_creation_query += "Coeff";
		table_creation_query += to_string(i);
		table_creation_query += " DOUBLE NOT NULL,";
	}
	table_creation_query += " Parent int DEFAULT 0, Direction int DEFAULT 0, Mu double, Son1 int DEFAULT 0, Son2 int DEFAULT 0,";
	table_creation_query += " PRIMARY KEY(Bof_Region_ID))";

	if (!mysql_query(db_connection, table_creation_query.c_str()))
		cout << "Table creation query: OK."<<endl;
	else
		error_and_exit();
}


/**
*   Destructor
*/
Bof_db_Region::~Bof_db_Region()
{
	mysql_close(db_connection);
	cout << "Closing connection: OK."<<endl;
}


/**
 *   Error function (display error and exit program).
 **/
void Bof_db_Region::error_and_exit()
{
	printf("Error %u: %s\n", mysql_errno(db_connection), mysql_error(db_connection));
	system("pause");
	exit(4);
}




/**
 *   Add-Bag of Features function (add a line to the table).
 **/
void Bof_db_Region::add_bof(Bof_Region &bag)
{
	Vector histogram;
	bag.get_histogram(histogram);

	string add_bof_region_query = "INSERT INTO ";
	add_bof_region_query += table_name;
	add_bof_region_query += " (";

	for (unsigned int i=0; i<this->nb_k_centers; i++)
	{
		add_bof_region_query += "Coeff";
		add_bof_region_query += to_string(i+1);
		if (i != this->nb_k_centers - 1)
			add_bof_region_query += ",";
	}
	add_bof_region_query += ") VALUES (";

	for (unsigned int i=0; i<this->nb_k_centers; i++)
	{
		add_bof_region_query += to_string(histogram[i]);
		if (i != this->nb_k_centers - 1)
			add_bof_region_query += ",";
	}
	add_bof_region_query += ")";


	if (mysql_query(db_connection, add_bof_region_query.c_str()))
		error_and_exit();

}




/**
 * PARTIE CONSTRUCTION DE L'ARBRE
 **/



/**
 * Sélectionne un random set aléatoire de résultats parmi les résultats de la requete:
 * PARENT = parent et DIRECTION = direction
 **/
void Bof_db_Region::select_random_set_indexes(int index_parent, int direction,
									   std::vector<Vector> &sample_set, std::vector<int> &random_indexes,
									   unsigned int not_this_one)
{
	//1- Compter le nombre de résultats de la requete
	int nb = this->count_elems(index_parent, direction, not_this_one);

	//RECUPERATION DU CONTENU
	//Declaration des pointeurs de structure
	MYSQL_RES *result = NULL;
	MYSQL_ROW row = NULL;

	//2- Sélectionner un random set sur la liste des indexes
    sample_set.resize(min(RANDOM_SET_MAX_LENGTH,nb));
    random_indexes.resize(min(RANDOM_SET_MAX_LENGTH,nb));

    string random_query = "SELECT Bof_Region_ID, ";

    for (unsigned int k=1; k<=nb_k_centers;k++)
    {
        random_query+="Coeff";
        random_query+=to_string(k);
        if (k!= nb_k_centers)
            random_query+=" ,";
    }

    random_query+=" FROM ";
    random_query+=table_name;
    random_query+=" WHERE Parent = ";
    random_query+=to_string(index_parent);
    random_query+=" and Direction = ";
    random_query+=to_string(direction);

	if (not_this_one != 0)
	{
		random_query += " and BoF_Region_ID != ";
		random_query += to_string(not_this_one);
	}


    random_query+=" ORDER BY RAND() LIMIT ";
    random_query+=to_string(RANDOM_SET_MAX_LENGTH);


    if (!mysql_query(db_connection, random_query.c_str()))
    {
        //cout << "Random query (Random) : OK"<<endl;
    }
    else
        error_and_exit();

    result = mysql_use_result(db_connection);

    int i=0;
    Vector res;
    res.resize(nb_k_centers);

    while(row = mysql_fetch_row(result))
	{
        //Primary key of random result
        random_indexes[i] = strtodouble(row[0]);

        //Random BOF
        for (int j=0; j<nb_k_centers;j++)
            res[j] = strtodouble(row[j+1]);

        sample_set[i] = res;
        i++;
    }

    //Liberation du jeu de resultat
    mysql_free_result(result);
}


/**
 * Sélectionne la racine du VP-Tree
 **/
unsigned int Bof_db_Region::select_vp(int index_parent, int direction, Bof_Region &root)
{
	std::vector<Vector> sample_set;
	std::vector<int> random_indexes_candidates;
	select_random_set_indexes(index_parent, direction, sample_set, random_indexes_candidates);

	double best_spread = 0;

	unsigned int best_candidate = random_indexes_candidates[0];
	root = Bof_Region(sample_set[0], this->fdb);

	if (random_indexes_candidates.size() == 1)
		//Il n'a qu'un seul élément dans l'ensemble
		return best_candidate;

	std::vector<Vector> rand_set_for_med_test;
	for (int i=0; i<sample_set.size(); ++i)
	{
		//Sélection d'un set aléatoire de l'espace qui nous intéresse
		Bof_Region candidate_region(sample_set[i], this->fdb);

		std::vector<int> rand_set_for_med_test_indexes;
		select_random_set_indexes(index_parent, direction,
			rand_set_for_med_test, rand_set_for_med_test_indexes, random_indexes_candidates[i]);
		

		//Précalcul des distances entre le candidat et les régions du sample_set
		Vector distances_p_rand_set;
		distances_p_rand_set.resize(rand_set_for_med_test.size());
		for (int j=0; j<distances_p_rand_set.size(); ++j)
		{
			Bof_Region random_region(rand_set_for_med_test[j], this->fdb);
			double tmp = candidate_region - random_region;
			distances_p_rand_set[j] = tmp;
		}

		//Calcul de la variance de cet ensemble de distances (calculée avec la médiane)
		double median = distances_p_rand_set.compute_median();
		double spread = distances_p_rand_set.compute_second_moment(median);
		//cout << "Répartition des distances: " << distances_p_rand_set
		//	<< " spread: " << spread << " median: " << median << endl;

		if (spread > best_spread)
		{
			best_spread = spread;
			best_candidate = random_indexes_candidates[i];
			root = candidate_region;
		}

		rand_set_for_med_test.clear();

	}

	return best_candidate;
}


void Bof_db_Region::build_tree()
{
	//Initialisation des champs temporaires
	string set_son_query = "UPDATE ";
	set_son_query += table_name;
	set_son_query += " SET Parent=0, Direction=0, Son1=0, Son2=0, Mu=0";
	mysql_query(db_connection, set_son_query.c_str());

	//Fonction récursive construisant l'arbre
	make_one_step(0,0);
}




void Bof_db_Region::make_one_step(int index_parent, int direction)
{

	static int compt=0;

	cout << endl << "--------------------------------" << endl;
	cout << "ITERATION " << compt << ": Parent " << index_parent << " direction " << direction << endl;
	cout << "--------------------------------" << endl;
	compt ++;

	//1- Sélectionner la racine parmi un random set
	Bof_Region root;
	unsigned int median_index = select_vp(index_parent, direction, root);

	cout << "RACINE CHOISIE: " << median_index << endl;

	//2- Choisir la distance critique:
	// C'est la médiane des distances du noeud à tous les éléments de l'ensemble

	//2-1) Calcul des distances à la racone dans la database
	this->update_distances(index_parent, direction, root);

	//2-2) Calcul de la médiane par la database
	double mu = this->get_median(index_parent, direction);
	cout << "Seuil choisi : " << mu << endl;

	//3- Set parent and directions to nodes of the set
	this->set_parent_direction_fields(index_parent, direction, mu, median_index);

	//4- Mise à jour du Son correspondant pour le parent
	if (index_parent != 0)
		this->set_son_value(index_parent, direction, median_index);

	//5- Mise à jour du Mu pour la racine trouvée
	this->set_mu_value(median_index, mu);

	//6- Mise à jour du parent de la racine
	this->set_parent_direction(median_index, index_parent, direction);

	//7- Obtenir le nombre de noeuds à gauche et à droite
	int nb_son_1 = this->count_elems(median_index, 1);
	int nb_son_2 = this->count_elems(median_index, 2);

	//Si pas de noeud dans le sous-arbre de gauche...
	if (nb_son_1 == 0)
	{
		//On met 0 comme sous-arbre de de gauche
		this->set_son_value(median_index, 1, 0);
	}
	//Si pas de noeud dans le sous-arbre de gauche...
	if (nb_son_2 == 0)
	{
		//On met 0 comme sous-arbre de de gauche
		this->set_son_value(median_index, 2, 0);
	}

	cout << "Répartition : " << nb_son_1 << " | " << nb_son_2 << endl;

	//4- Si il y a au moins un élément dans le sous-arbre de gauche
	if (nb_son_1>0)
		make_one_step(median_index, 1);
	//	 Si il y a au moins un élément dans le sous-arbre de droite
	if (nb_son_2>0)
		make_one_step(median_index, 2);


}


/**
* Update les champs Son1 ou Son2 du parent
**/
void Bof_db_Region::set_son_value(int index_parent, int direction, int index_median)
{
	string son;
	if (direction == 1)
		son = "Son1";
	else
		son = "Son2";

	string set_son_query = "UPDATE ";
	set_son_query += table_name;
	set_son_query += " SET ";
	set_son_query += son;
	set_son_query += "=";
	set_son_query += to_string(index_median);

	set_son_query += " WHERE Bof_Region_ID=";
	set_son_query += to_string(index_parent);

	if (!mysql_query(db_connection, set_son_query.c_str()))
	{
		//cout << "Set Son Value Query: OK"<<endl;
	}
	else
		error_and_exit();

}



/**
 * Insère les distances à la racine dans le champ mu
 **/
void Bof_db_Region::update_distances(int parent, int direction, Bof_Region &root)
{
	Vector distances;
	Vector ids;

	int offset = 0;

	while (true)
	{
		//######################################
		// Sélection des 1000 premières régions
		//######################################
		MYSQL_RES *result = NULL;
		MYSQL_ROW row = NULL;

		string distances_query = "SELECT Bof_Region_ID, ";

		for (unsigned int k=1; k<=nb_k_centers;k++)
		{
			distances_query += " Coeff";
			distances_query += to_string(k);
			if (k!= nb_k_centers)
				distances_query += " ,";
			else
				distances_query += " FROM ";
		}

		distances_query += table_name;
		distances_query += " WHERE parent = ";
		distances_query += to_string(parent);
		distances_query += " and direction = ";
		distances_query += to_string(direction);
		distances_query += " LIMIT ";
		distances_query += to_string(MAX_ROWS_BY_DISTANCE_REQUEST);
		distances_query += " OFFSET ";
		distances_query += to_string(offset);

		if (!mysql_query(db_connection, distances_query.c_str()))
		{
			//cout << "# of distances of query: OK" << endl;
		}
		else
			error_and_exit();

		result = mysql_use_result(db_connection);
		unsigned int num_champs = mysql_num_fields(result);

		//on stocke les valeurs de la ligne choisie
		ids.clear();
		distances.clear();
		int nb_results = 0;
		while (row = mysql_fetch_row(result))
		{
			ids.push_back(strtodouble(row[0]));

			//On fait une boucle pour avoir la valeur de chaque champ
			Vector feat;
			for (int i = 1; i < num_champs; i++)
				feat.push_back(strtodouble(row[i]));

			double dist = Bof_Region(feat, this->fdb) - root;
			distances.push_back(dist);

			nb_results ++;
		}

		if (nb_results == 0)
			//Mise à jour des distances finie!
			break;

		//########################################
		// Insertion des 1000 distances calculées
		//########################################
		string distances_insertion_query = "UPDATE ";
		distances_insertion_query += table_name;
		distances_insertion_query += " SET Mu = CASE Bof_Region_ID ";

		for (int i=0; i<nb_results; ++i)
		{
			distances_insertion_query += " WHEN ";
			distances_insertion_query += to_string(ids[i]);
			distances_insertion_query += " THEN ";
			distances_insertion_query += to_string(distances[i]);
		}
		distances_insertion_query += " ELSE Mu END";

		if (mysql_query(db_connection, distances_insertion_query.c_str()))
			error_and_exit();

		mysql_free_result(result);

		if (nb_results != MAX_ROWS_BY_DISTANCE_REQUEST)
			//Il n'y a pas plus de 1000 résultats => 
			break;

		offset += nb_results;
	}

}


/**
 * Calcul de la médiane par le serveur SQL (prend en paramètres le nombre de décimales)
 * Nécessite d'installer la fonction médiane de UDF
 **/
double Bof_db_Region::get_median(int parent, int direction)
{
	// REQUETE SQL
	string get_median_query = "SELECT median(Mu,10) FROM "; // 10 : nb de chiffres significatifs de la fonction median
	get_median_query += table_name;
	get_median_query += " WHERE Parent=";
	get_median_query += to_string(parent);
	get_median_query += " AND Direction=";
	get_median_query += to_string(direction);

	if (!mysql_query(db_connection, get_median_query.c_str()))
	{
		//cout << "Get median query: OK"<<endl;
	}
	else
		error_and_exit();

	//RECUPERATION DU CONTENU
	//Declaration des pointeurs de structure
	MYSQL_RES *result = NULL;
	MYSQL_ROW row = NULL;

	//On met le jeu de resultat dans le pointeur result
	result = mysql_use_result(db_connection);

	row = mysql_fetch_row(result);

	double median = strtodouble(row[0]);

	//Liberation du jeu de resultat
	mysql_free_result(result);

	return median;
}


/**
* Met à jour les champs Parent et Direction des noeuds membres de l'ensemble considéré
**/
void Bof_db_Region::set_parent_direction_fields(int parent, int direction, double median, int index_median)
{
	string set_son_query = "UPDATE ";
	set_son_query += table_name;
	set_son_query += " SET Parent=";
	set_son_query += to_string(index_median);
	set_son_query += ", Direction=(SIGN(Mu-";
	set_son_query += to_string(median);
	set_son_query += ")+1)/2+1";

	set_son_query += " WHERE Parent=";
	set_son_query += to_string(parent);
	set_son_query += " AND Direction=";
	set_son_query += to_string(direction);

	if (!mysql_query(db_connection, set_son_query.c_str()))
	{
		//cout << "Set Parent and Direction fields query: OK"<<endl;
	}
	else
		error_and_exit();
}



/**
* Update le champ Mu de la racine trouvée
**/
void Bof_db_Region::set_mu_value(int index_root, double median)
{
	string set_son_query = "UPDATE ";
	set_son_query += table_name;
	set_son_query += " SET Mu=";
	set_son_query += to_string(median);

	set_son_query += " WHERE Bof_Region_ID=";
	set_son_query += to_string(index_root);

	if (!mysql_query(db_connection, set_son_query.c_str()))
	{
		//cout << "Add-bof-query: OK"<<endl;
	}
	else
		error_and_exit();

}



/**
* Obtenir le nombre de noeuds dans chaque sous-arbre
**/
int Bof_db_Region::count_elems(int parent, int direction, unsigned int not_this_one)
{
	string set_son_query = "SELECT COUNT(*) FROM ";
	set_son_query += table_name;

	if (parent != -1)
	{
		set_son_query += " WHERE Parent=";
		set_son_query += to_string(parent);

		set_son_query += " AND Direction=";
		set_son_query += to_string(direction);
	}


	if (not_this_one != 0)
	{
		set_son_query += " AND BOF_Region_ID != ";
		set_son_query += to_string(not_this_one);
	}

	if (!mysql_query(db_connection, set_son_query.c_str()))
	{
		//cout << "Count elements query: OK"<<endl;
	}
	else
		error_and_exit();


	//RECUPERATION DU CONTENU
	//Declaration des pointeurs de structure
	MYSQL_RES *result = NULL;
	MYSQL_ROW row = NULL;

	//On met le jeu de resultat dans le pointeur result
	result = mysql_use_result(db_connection);

	row = mysql_fetch_row(result);
	int nb = strtodouble(row[0]);

	//Liberation du jeu de resultat
	mysql_free_result(result);

	return nb;


}




/**
* Change le champ parent à la ligne index
**/
void Bof_db_Region::set_parent_direction(int index, int index_parent, int direction)
{
	string set_son_query = "UPDATE ";
	set_son_query += table_name;
	set_son_query += " SET Parent=";
	set_son_query += to_string(index_parent);
	set_son_query += " ,Direction=";
	set_son_query += to_string(direction);

	set_son_query += " WHERE Bof_Region_ID=";
	set_son_query += to_string(index);

	if (!mysql_query(db_connection, set_son_query.c_str()))
	{
		//cout << "Set Son Value Query: OK"<<endl;
	}
	else
		error_and_exit();

}




void Bof_db_Region::get_bof_number(int index, Bof_Region &res, double &mu, double &son1, double &son2)
{
	//RECUPERATION DU CONTENU
	//Declaration des pointeurs de structure
	MYSQL_RES *result = NULL;
	MYSQL_ROW row = NULL;

	string random_query = "SELECT Mu, Son1, Son2, ";

	for (unsigned int k=1; k<=this->nb_k_centers;k++)
	{
		random_query+=" Coeff";
		random_query+=to_string(k);
		if (k!= this->nb_k_centers)
			random_query+=" ,";
	}

	random_query += " FROM ";
	random_query += table_name;
	random_query+=" WHERE Bof_Region_ID = ";
	random_query+=to_string(index);

	if (!mysql_query(db_connection, random_query.c_str()))
	{
		//cout << "Random query (Random) : OK"<<endl;
	}
	else
		error_and_exit();

	result = mysql_use_result(db_connection);

	Vector histo_centers;
	histo_centers.resize(this->nb_k_centers);

	row = mysql_fetch_row(result);
	if (!row)
	{
		cout << "Pas de bof ayant le numero " << index << endl;
		error_and_exit();
	}

	mu = strtodouble(row[0]);
	son1 = strtodouble(row[1]);
	son2 = strtodouble(row[2]);

	for (int j=0; j<this->nb_k_centers;j++)
		histo_centers[j] = strtodouble(row[j+3]);

	res = Bof_Region(histo_centers, this->fdb);

	//Liberation du jeu de resultat
	mysql_free_result(result);

}



unsigned int Bof_db_Region::get_root_node()
{
	//RECUPERATION DU CONTENU
	//Declaration des pointeurs de structure
	MYSQL_RES *result = NULL;
	MYSQL_ROW row = NULL;

	string random_query = "SELECT Bof_Region_ID FROM ";
	random_query += table_name;
	random_query+=" WHERE Parent = 0";

	if (mysql_query(db_connection, random_query.c_str()))
		error_and_exit();

	result = mysql_use_result(db_connection);
	row = mysql_fetch_row(result);

	unsigned int root_index = strtodouble(row[0]);

	//Liberation du jeu de resultat
	mysql_free_result(result);

	return root_index;
}




unsigned int Bof_db_Region::find_nearest_leaf(Bof_Region &bof)
{
	cout << endl << "Recherche dans le VP-Tree..." << endl;

	//Déclaration des variables de la fonction
	unsigned int root_index = this->get_root_node();
	cout << "Le parent est le noeud " << root_index << endl << endl;

	std::vector<unsigned int> nodes_to_search;
	nodes_to_search.push_back(root_index);

	bool first = true;
	double distance_max = INT_MAX;
	unsigned int nearest = 0;
	int noeuds_parcourus = 0;

	//Tant qu'il y a des noeuds dans lesquels rechercher...
	while (!nodes_to_search.empty())
	{
		noeuds_parcourus++;

		unsigned int search_node = nodes_to_search.back();
		nodes_to_search.pop_back();
		cout << "Recherche dans le sous-arbre " << search_node << endl;

		Bof_Region root_bof;
		double mu, son1, son2;
		this->get_bof_number(search_node, root_bof, mu, son1, son2);
		double dist_to_node = root_bof - bof;

		if (dist_to_node < distance_max)
		{
			nearest = search_node;
			distance_max = dist_to_node;
		}

		//Si on est au tout en haut de l'arbre, on recherche dans les deux sous-arbres
		if (first)
		{
			nodes_to_search.push_back(son1);
			nodes_to_search.push_back(son2);
			distance_max = dist_to_node;
			first = false;
			cout << endl;
			continue;
		}

		//Si la distance est inférieure au seuil + distance_max, on recherche à l'intérieur
		if ((dist_to_node < mu + distance_max) && (son1 !=0 ))
		{
			nodes_to_search.push_back(son1);
			cout << "Recherche dans le sous-arbre gauche" << endl;
		}
		//Si la distance est supérieure au seuil - distance_max, on recherche à l'extérieur
		if ((dist_to_node > mu - distance_max) && (son2 != 0))
		{
			nodes_to_search.push_back(son2);
			cout << "Recherche dans le sous-arbre droit" << endl;
		}
		cout << endl;
	}

	cout << noeuds_parcourus << " / " << this->count_elems(-1, 0, 0) << " noeuds parcourus!" << endl;
	cout << "Le BOF le plus proche est le " << nearest << endl;
	cout << "La distance minimale est: " << distance_max << endl;

	return nearest;
}




