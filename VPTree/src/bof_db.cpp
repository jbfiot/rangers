#include "bof_db.h"

#define RANDOM_SET_MAX_LENGTH 1000
#define MAX_BOF_BY_SELECT 100

using namespace std;



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
	table_creation_query+=" (Bof_ID int NOT NULL auto_increment,";

	for (unsigned int i=1; i<=nb_k_centers;i++){
	    table_creation_query+="Coeff";
	    table_creation_query+=to_string(i);
	    table_creation_query+=" DOUBLE NOT NULL,";
	}
	table_creation_query+=" Parent int DEFAULT 0, Direction int DEFAULT 0, Mu double, Son1 int DEFAULT 0, Son2 int DEFAULT 0,";

	table_creation_query+=" PRIMARY KEY(Bof_ID))";

	cout << table_creation_query <<endl;

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





/**
 * PARTIE CONSTRUCTION DE L'ARBRE
 **/



/**
 * Sélectionne un random set aléatoire de résultats parmi les résultats de la requete:
 * PARENT = parent et DIRECTION = direction
 **/
std::vector<Vector> Bof_db::select_random_set_indexes(int index_parent, int direction)
{
	//1- Compter le nombre de résultats de la requete
	string nb_result_query = "SELECT count(*) WHERE parent =";
	nb_result_query+=to_string(index_parent);
	nb_result_query+=" AND direction = ";
	nb_result_query+= to_string(direction);


	if (!mysql_query(db_connection, nb_result_query.c_str())) {
	    cout << "# of results of query: OK"<<endl;
	}
	else {
        error_and_exit();
	}

	//RECUPERATION DU CONTENU
	//Declaration des pointeurs de structure
	MYSQL_RES *result = NULL;
	MYSQL_ROW row = NULL;

	//On met le jeu de resultat dans le pointeur result
	result = mysql_use_result(db_connection);

	//On recupere le nombre de champs
	unsigned int num_champs = mysql_num_fields(result);

	row = mysql_fetch_row(result);
	unsigned int nb = strtodouble(row[0]);

	//Liberation du jeu de resultat
	mysql_free_result(result);

    string random_query;

	//2- Sélectionner un random set sur la liste des indexes
	std::vector<Vector> sample_set;
	if (nb>RANDOM_SET_MAX_LENGTH)
	{
		int *random_indexes = get_random_set_indexes(RANDOM_SET_MAX_LENGTH, nb);
		sample_set.resize(RANDOM_SET_MAX_LENGTH);
		for (int i=0; i<RANDOM_SET_MAX_LENGTH; ++i)
		{
			//Le random_indexes[i]-ième résultat

        random_query = "SELECT (";

        for (unsigned int k=1; k<=nb_k_centers;k++){
            random_query+="Coeff";
            random_query+=to_string(k);
            if (k!= nb_k_centers)
                random_query+=" ,";
            else
                random_query+=") OFFSET ";
        }
        random_query+=to_string(random_indexes[i]);
        random_query+=" LIMIT 1 WHERE parent = ";
        random_query+=index_parent;
        random_query+=" and direction = ";
        random_query+=direction;

        if (!mysql_query(db_connection, random_query.c_str())) {
            cout << "Random query: OK"<<endl;
        }
        else {
            error_and_exit();
        }


        //On met le jeu de resultat dans le pointeur result
        result = mysql_use_result(db_connection);


        row = mysql_fetch_row(result);
        for (int j=0; j<nb_k_centers;j++){
            sample_set[i][j] = strtodouble(row[j]);
        }

        //Liberation du jeu de resultat
        mysql_free_result(result);

		}

		delete [] random_indexes;
	}
	else
	{
	    sample_set.resize(nb);
        random_query = "SELECT (";

        for (unsigned int i=1; i<=nb_k_centers;i++){
            random_query+="Coeff";
            random_query+=to_string(i);
            if (i!= nb_k_centers)
                random_query+=" ,";
        }
        random_query+=")";
        random_query+=" WHERE parent = ";
        random_query+=index_parent;
        random_query+=" and direction = ";
        random_query+=direction;

        if (!mysql_query(db_connection, nb_result_query.c_str())) {
            cout << "# of results of query: OK"<<endl;
        }
        else {
            error_and_exit();
        }

        //On met le jeu de resultat dans le pointeur result
        result = mysql_use_result(db_connection);


        row = mysql_fetch_row(result);
        for (int i=0; i<nb;i++) {
            for (int j=0; j<nb_k_centers;j++){
                sample_set[i][j] = strtodouble(row[j]);
            }
        }

        //Liberation du jeu de resultat
        mysql_free_result(result);



	}

	return sample_set;

}


unsigned int Bof_db::select_vp(int index_parent, int direction)
{
	std::vector<Vector> sample_set = select_random_set_indexes(index_parent, direction);
	double best_spread= 0;
	unsigned int best_candidate = 0;

	for (int i=0; i<sample_set.size(); ++i)
	{
		//Sélection d'un set aléatoire de l'espace qui nous intéresse
		Vector candidate = sample_set[i];
		std::vector<Vector> rand_set_for_med_test = select_random_set_indexes(index_parent, direction);

		//Précalcul des distances entre le candidat et les régions du sample_set
		Vector distances_p_rand_set(rand_set_for_med_test.size());
		for (int j=0; j<distances_p_rand_set.size(); ++j)
		{
			distances_p_rand_set[j] = candidate - rand_set_for_med_test[j];
		}

		//Calcul de la variance de cet ensemble de distances (calculée avec la médiane)
		double median = distances_p_rand_set.compute_median();
		double spread = distances_p_rand_set.compute_second_moment(median);

		if (spread > best_spread)
		{
			best_spread = spread;
			best_candidate = i;
		}

	}

	return best_candidate;
}


void Bof_db::build_tree()
{
	//Fonction récursive construisant l'arbre
	make_one_step(0,0);
}




void Bof_db::make_one_step(int index_parent, int direction)
{
	//1- Sélectionner la racine parmi un random set
	unsigned int root = select_vp(index_parent, direction);

	//2- Choisir la distance critique:
	// C'est la médiane des distances du noeud à tous les éléments de l'ensemble
	double mu; // pour la distance critique
	int median_index; // pour l'index du bof qui devient noeud de division


	//3- Set parent and directions to nodes of the set
	int i=0, nb_son_1=0, nb_son_2=0;

    //Declaration des pointeurs de structure
    MYSQL_RES *result = NULL;
    MYSQL_ROW row = NULL;

    unsigned int num_champs = 0;

    string mos_query,median_query, dir;
    double dist;

	while(1) {
        mos_query = "SELECT (";

        for (unsigned int k=1; k<=nb_k_centers;k++){
            mos_query+="Coeff";
            mos_query+=to_string(k);
            if (k!= nb_k_centers)
                mos_query+=" ,";
            else
                mos_query+=") OFFSET ";
        }
        mos_query+=to_string(i*MAX_BOF_BY_SELECT);
        mos_query+=" LIMIT "; mos_query+=to_string(MAX_BOF_BY_SELECT);
        mos_query+=" WHERE parent = "; mos_query+=index_parent;
        mos_query+=" and direction = "; mos_query+=direction;


        if (!mysql_query(db_connection, mos_query.c_str())) {
            cout << "MakeOneStep query: OK"<<endl;
        }
        else {
            error_and_exit();
        }

        result = mysql_use_result(db_connection);

        //On recupere le nombre de champs
        num_champs = mysql_num_fields(result);

        if (num_champs>0) {
            while (row = mysql_fetch_row(result))
            {
                // TO-DO : recup le bof ID et calculer la distance à partir de row
                string Bof_ID;

                //dist = ...;
                if (dist>mu) {
                    dir = "1";
                    nb_son_1++;
                }
                else {
                    dir = "2";
                    nb_son_2++;
                }

                median_query = "INSERT INTO ";
                median_query+=db_name;
                median_query+=" (Parent,direction) VALUES (";
                median_query+=to_string(median_index);
                median_query+=",";
                median_query+=dir;
                median_query+=") WHERE Bof_ID=";
                median_query+=Bof_ID;

                if (!mysql_query(db_connection, median_query.c_str())) {
                    cout << "Median query: OK"<<endl;
                }
                else {
                    error_and_exit();
                }

            }
        }
        else
            break;

        //Liberation du jeu de resultat
        mysql_free_result(result);

	    i++;

	}


	//Pour toutes les lignes de la tables ayant index_parent et direction comme champs temporaires,
	//	INSERT parent = median
	//	Si la distance avec la médiane est supérieur à mu
	//		INSERT direction = 1 (sous-arbre de droite)
	//	Sinon
	//		INSERT direction = 0 (sous-arbre de gauche)





	//Pour les arbres de gauche et de droite
	//	Si il y a un seul élement
	//		Mettre dans la base de données que cette ligne est une feuille (mettre les deux sous-arbres à INT_MAX)
	//	Si il n'y en a aucun
	//		Mettre le sous-arbre de la médiane égal à INT_MAX
	//
	//Mettre à la ligne index_parent de la base de données que le sous-arbre dans la direction direction est median

	//4- Si il y a au moins un élément dans le sous-arbre de gauche
	if (nb_son_1>0)
        make_one_step(median_index, 1);
	//	 Si il y a au moins un élément dans le sous-arbre de droite
	if (nb_son_2>0)
		make_one_step(median_index, 2);

}
