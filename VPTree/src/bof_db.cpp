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


Bof_db::Bof_db (std::vector<Vector> centers, string db_host, string db_username,
				string db_password, string db_name, string table_name)
{
    this->db_name = db_name;
    this->db_username = db_username;
    this->db_password = db_password;
    this->db_host = db_host;
    this->table_name = table_name;
    this->centers = centers;
	this->nb_k_centers = centers.size();

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
	    table_creation_query+=" DOUBLE NOT NULL,";
	}
	table_creation_query+=" Parent int(10) NOT NULL DEFAULT 0, Direction int(2) NOT NULL DEFAULT 0,";

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
	system("pause");
    exit(4);


}

/**
*   Add-feature function (add a line to the table).
*/

void Bof_db::add_bof(Bof bag) {
    string add_bof_query = "INSERT INTO ";
    add_bof_query+=table_name;
    add_bof_query+=" (";
    Vector proba;
    bag.get_kmeans_proba(centers, proba);

    for (unsigned int i=0; i<proba.size(); i++){
        add_bof_query+="Coeff";
        add_bof_query+=to_string(i+1);
        if (i!=proba.size() - 1) {
            add_bof_query+=",";
        }
    }

    add_bof_query+=") VALUES (";

    for (unsigned int i=0; i<proba.size(); i++){
        add_bof_query+=to_string(proba[i]);
        if (i!=proba.size() - 1) {
            add_bof_query+=",";
        }
    }
    add_bof_query+=")";

    if (!mysql_query(db_connection, add_bof_query.c_str())) {
	    cout << "Add-bof-query: OK"<<endl;
	}
	else {
        error_and_exit();
	}

}








// PARTIE CONSTRUCTION DE L'ARBRE
//
///**
// * Sélectionne une liste aléatoire de k nombres entre 1 et n (n>=k)
// **/
//int *get_random_set_indexes(k, n)
//{
//	int *indexes = new int[k];
//	for (int i=0; i<k; ++i)
//	{
//		int index;
//		while (1)
//		{
//			index = rand()%n;
//
//			int *p = find(indexes,indexes+i,index);
//			if (p == indexes+i)
//				break;
//		}
//
//		indexes[i] = index;
//	}
//	return indexes;
//}
//
//
///**
// * Sélectionne un random set aléatoire de résultats parmi les résultats de la requete:
// * PARENT = parent et DIRECTION = direction
// **/
//std::vector<std::vector<double>> select_random_set_indexes(int index_parent, int direction)
//{
//	//1- Compter le nombre de résultats de la requete
//	unsigned int nb = "SELECT count(*) LIMIT INDEX WHERE parent = index_parent and direction = direction";
//
//	//2- Sélectionner un random set sur la liste des indexes
//	std::vector<std::vector<double>> sample_set;
//	if (nb<1000)
//	{
//		int *random_indexes = get_random_set_indexes(1000, nb);
//		sample_set.resize(1000);
//		for (int i=0; i<1000; ++i)
//		{
//			//Le random_indexes[i]-ième résultat
//			sample_set[i] =
//				"SELECT d0,...,d1000 OFFSET random_indexes[i] LIMIT 1 WHERE parent = index_parent and direction = direction"
//		}
//		delete [] random_indexes;
//	}
//	else
//	{
//		sample_set= "SELECT d0,...,d1000 WHERE parent = index_parent and direction = direction";
//	}
//
//	return sample_set;
//
//}
//
//
//int Bof_db::select_vp(int index_parent, int direction)
//{
//	std::vector<std::vector<double>> sample_set = select_random_set_indexes(int index_parent, int direction);
//	double best_spread= 0;
//	unsigned int best_candidate = 0;
//
//	for (int i=0; i<sample_set.size(); ++i)
//	{
//		//Sélection d'un set aléatoire de l'espace qui nous intéresse
//		std::vector<double> candidate = sample_set[i];
//		std::vector<std::vector<double>> rand_set_for_med_test = select_random_set_indexes(int index_parent, int direction);
//
//		//Précalcul des distances entre le candidat et les régions du sample_set
//		std::vector<double> distances_p_rand_set(rand_set_for_med_test.size());
//		for (int j=0; j<distances_p_rand_set.size(); ++j)
//		{
//			distances_p_rand_set[j] = candidate - rand_set_for_med_test[j];
//		}
//
//		//Calcul de la variance de cet ensemble de distances (calculée avec la médiane)
//		double median = distances_p_rand_set.compute_median();
//		double spread = distances_p_rand_set.compute_second_moment(median);
//
//		if (spread > best_spread)
//		{
//			best_spread = spread;
//			best_candidate = i;
//		}
//
//	}
//
//	return best_candidate;
//}
//
//
//void Bof_db::build_tree()
//{
//	//0- Initialisation des deux champs temporaires:
//	// Parent: INT_MAX, direction: quelconque
//
//	//Fonction récursive construisant l'arbre
//	make_one_step(INT_MAX,0, &indexes_to_construct);
//}
//
//
//
//
//void Bof_db::make_one_step(int index_parent, int direction, *std::vector<std::vector<unsigned int>>)
//{
//	//1- Sélectionner la racine parmi un random set
//	unsigned int root = select_vp(parent, direction);
//
//	//2- Choisir la distance critique:
//	// C'est la médiane des distances du noeud à tous les éléments de l'ensemble
//
//	//3- Set parent and direction to nodes of the set
//	//Pour toutes les lignes de la tables ayant index_parent et direction comme champs temporaires,
//	//	INSERT parent = median
//	//	Si la distance avec la médiane est supérieur à mu
//	//		INSERT direction = 1 (sous-arbre de droite)
//	//	Sinon
//	//		INSERT direction = 0 (sous-arbre de gauche)
//	//
//	//Pour les arbres de gauche et de droite
//	//	Si il y a un seul élement
//	//		Mettre dans la base de données que cette ligne est une feuille (mettre les deux sous-arbres à INT_MAX)
//	//	Si il n'y en a aucun
//	//		Mettre le sous-arbre de la médiane égal à INT_MAX
//	//
//	//Mettre à la ligne index_parent de la base de données que le sous-arbre dans la direction direction est median
//
//	//4- Si il y a au moins un élément dans le sous-arbre de gauche
//	//		make_one_step(median, 0)
//	//	 Si il y a au moins un élément dans le sous-arbre de droite
//	//		make_one_step(median, 1)
//
//}
