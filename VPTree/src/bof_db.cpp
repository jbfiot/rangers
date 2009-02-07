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


Bof_db::Bof_db (std::vector<Feature> centers, string db_host, string db_username,
				string db_password, string db_name, string table_name)
{
    this->db_name = db_name;
    this->db_username = db_username;
    this->db_password = db_password;
    this->db_host = db_host;
    this->table_name = table_name;
    this->centers = centers;
	this->nb_k_centers = centers[0].coeffs[0];

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
	system("pause");
    exit(4);


}

/**
*   Add-feature function (add a line to the table).
*/

void Bof_db::add_bof(Bof bag) {
    string add_bof_query = "INSERT INTO ";
    add_bof_query+=db_name;
}








// PARTIE CONSTRUCTION DE L'ARBRE
//
///**
// * S�lectionne une liste al�atoire de k nombres entre 1 et n (n>=k)
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
// * S�lectionne un random set al�atoire de r�sultats parmi les r�sultats de la requete:
// * PARENT = parent et DIRECTION = direction
// **/
//std::vector<std::vector<double>> select_random_set_indexes(int index_parent, int direction)
//{
//	//1- Compter le nombre de r�sultats de la requete
//	unsigned int nb = "SELECT count(*) LIMIT INDEX WHERE parent = index_parent and direction = direction";
//
//	//2- S�lectionner un random set sur la liste des indexes
//	std::vector<std::vector<double>> sample_set;
//	if (nb<1000)
//	{
//		int *random_indexes = get_random_set_indexes(1000, nb);
//		sample_set.resize(1000);
//		for (int i=0; i<1000; ++i)
//		{
//			//Le random_indexes[i]-i�me r�sultat
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
//		//S�lection d'un set al�atoire de l'espace qui nous int�resse
//		std::vector<double> candidate = sample_set[i];
//		std::vector<std::vector<double>> rand_set_for_med_test = select_random_set_indexes(int index_parent, int direction);
//		
//		//Pr�calcul des distances entre le candidat et les r�gions du sample_set
//		std::vector<double> distances_p_rand_set(rand_set_for_med_test.size());
//		for (int j=0; j<distances_p_rand_set.size(); ++j)
//		{
//			distances_p_rand_set[j] = candidate - rand_set_for_med_test[j];
//		}
//
//		//Calcul de la variance de cet ensemble de distances (calcul�e avec la m�diane)
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
//	//Fonction r�cursive construisant l'arbre
//	make_one_step(INT_MAX,0, &indexes_to_construct);
//}
//
//
//
//
//void Bof_db::make_one_step(int index_parent, int direction, *std::vector<std::vector<unsigned int>>)
//{
//	//1- S�lectionner la racine parmi un random set
//	unsigned int root = select_vp(parent, direction);
//	
//	//2- Choisir la distance critique:
//	// C'est la m�diane des distances du noeud � tous les �l�ments de l'ensemble
//
//	//3- Set parent and direction to nodes of the set
//	//Pour toutes les lignes de la tables ayant index_parent et direction comme champs temporaires,
//	//	INSERT parent = median
//	//	Si la distance avec la m�diane est sup�rieur � mu
//	//		INSERT direction = 1 (sous-arbre de droite)
//	//	Sinon
//	//		INSERT direction = 0 (sous-arbre de gauche)
//	//
//	//Pour les arbres de gauche et de droite
//	//	Si il y a un seul �lement
//	//		Mettre dans la base de donn�es que cette ligne est une feuille (mettre les deux sous-arbres � INT_MAX)
//	//	Si il n'y en a aucun
//	//		Mettre le sous-arbre de la m�diane �gal � INT_MAX
//	//
//	//Mettre � la ligne index_parent de la base de donn�es que le sous-arbre dans la direction direction est median
//
//	//4- Si il y a au moins un �l�ment dans le sous-arbre de gauche
//	//		make_one_step(median, 0)
//	//	 Si il y a au moins un �l�ment dans le sous-arbre de droite
//	//		make_one_step(median, 1)
//
//}
