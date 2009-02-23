#include <algorithm>
#include "feature_db.h"

#include <sstream>



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
	table_creation_query+=" (Feature_ID int NOT NULL auto_increment,X INT DEFAULT 0, Y INT DEFAULT 0, Img_ID INT DEFAULT 0,";


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

void Feature_db::fill_with_random(int nb_images, int nb_features){

	for (int i=0; i<nb_images; ++i)
	{
		for (int j=0; j<nb_features; ++j)
		{
			std::vector<int> random_coeff;
			get_random_set_indexes(NB_COEFF_FEATURES+2,1000, random_coeff); // 1000 : max du coeff. (totalement arbitraire)
			Feature feature;
			feature.position.push_back(random_coeff[0]);
			feature.position.push_back(random_coeff[1]);
			feature.index_image = i+1;

			for (int j=0; j<NB_COEFF_FEATURES; ++j)
				feature.coeffs.push_back(random_coeff[j+2]);

			this->insert_feature(feature);
		}
	}
}


/**
*   Fill the table with random
**/
void Feature_db::insert_feature(Feature &feature) {// Est-ce que feature ne serait pas const ?

	string fill_with_random_query = "INSERT INTO ";
	fill_with_random_query+=table_name;
	fill_with_random_query+=" (";
	fill_with_random_query+="X,Y,Img_ID,";

	for (unsigned int i=1; i<=NB_COEFF_FEATURES; i++){
		fill_with_random_query+="Coeff";
		fill_with_random_query+=to_string(i);
		if (i!=NB_COEFF_FEATURES) {
			fill_with_random_query+=",";
		}
	}

	fill_with_random_query+=") VALUES (";
	fill_with_random_query+=to_string(feature.position[0]);
	fill_with_random_query+=",";
	fill_with_random_query+=to_string(feature.position[1]);
	fill_with_random_query+=",";
	fill_with_random_query+=to_string(feature.index_image);
	fill_with_random_query+=",";

	for (unsigned int i=1; i<=NB_COEFF_FEATURES; i++){
		fill_with_random_query+=to_string(feature.coeffs[i-1]);
		if (i!=NB_COEFF_FEATURES) {
			fill_with_random_query+=",";
		}
	}
	fill_with_random_query+=")";

	if (!mysql_query(db_connection, fill_with_random_query.c_str())) {
		//cout << "Fill-with-random-query: OK"<<endl;
	}
	else {
		error_and_exit();
	}

}


void Feature_db::get_feature_number(int index, Vector &vec)
{
	//// REQUETE SQL
	std::string get_feature_query = "SELECT ";
	for (unsigned int i=1; i<=NB_COEFF_FEATURES;i++)
	{
		get_feature_query+="Coeff";
		get_feature_query+=to_string(i);
		if (i!= NB_COEFF_FEATURES)
			get_feature_query+=" ,";
	}
	get_feature_query += " FROM ";
	get_feature_query += table_name;
	get_feature_query+=" WHERE Feature_ID=";
	get_feature_query+= to_string(index);


	if (!mysql_query(db_connection, get_feature_query.c_str()))
	{
		//cout << "Get feature query: OK"<<endl;
	}
	else
		error_and_exit();


	//RECUPERATION DU CONTENU

	//Declaration des pointeurs de structure
	MYSQL_RES *result = NULL;
	MYSQL_ROW row = NULL;

	//On met le jeu de resultat dans le pointeur result
	result = mysql_use_result(db_connection);

	//On recupere le nombre de champs
	unsigned int num_champs = mysql_num_fields(result);

	row = mysql_fetch_row(result);

	//On fait une boucle pour avoir la valeur de chaque champs (on zappe l'ID, le X, le Y et l'index_image)
	for (int i = 0; i < num_champs; i++)
	{
		vec.push_back(strtodouble(row[i]));
	}

	//Liberation du jeu de resultat
	mysql_free_result(result);
}




/**
*	Applique l'algorithme des K-Means sur le SiftSet
**/
void Feature_db::do_k_means(int k, std::vector<Vector> &centers, bool try_load, bool save)
{

    unsigned int nb_sifts = get_nbfeatures();
    assert(k<SAMPLE_LENGTH_FOR_K_MEANS && SAMPLE_LENGTH_FOR_K_MEANS<nb_sifts);
    centers.resize(k);


    bool load_successfull=false;
    string k_center_table_name = "k_centers";

    if (try_load) {
        /**
        *   LOADING K-MEANS
        */

        cout << endl<< "Trying to load k-centers..." <<endl;

        string get_k_centers_query = "SELECT * FROM ";
        get_k_centers_query += k_center_table_name;

        if (!mysql_query(db_connection, get_k_centers_query.c_str()))
        {
            MYSQL_RES *result = NULL;
            MYSQL_ROW row = NULL;
            result = mysql_use_result(db_connection);

            unsigned int num_rows = mysql_num_rows(result);

            if (num_rows == k && false){
                row = mysql_fetch_row(result);

                for (int i = 0; i < num_rows; i++)
                {
                    centers.push_back(strtodouble(row[i]));
                }
                load_successfull=true;
                cout << "-> K-centers Loading successfull. No computation." <<endl;
                mysql_free_result(result);

            }
            else {
                mysql_free_result(result);
                cout << "-> Wrong number of the centers in the database: "<<num_rows << " instead of " << k <<endl;
                string drop_query= "DROP TABLE ";
                drop_query+=k_center_table_name;

                if (!mysql_query(db_connection, drop_query.c_str())) {
                    cout << "-> Table " <<k_center_table_name<< " dropped."<<endl;
                }
                else {
                    error_and_exit();
                }


            }



        }
        else {
            cout << "-> Impossible to load k-centers." << endl;
        }
    }



    if (try_load == false || load_successfull==false) {
        /**
        *   COMPUTING K-MEANS
        */
        cout << endl<< "Computing the k-centers..." << endl;

        //Initialisation des centres au pif
        for (int i=0; i<k; ++i)
        {
            for (int j=0; j<128; ++j)
            {
                //Coords des SIFTs entre 0 et 1000?
                centers[i].push_back( rand()*1000./RAND_MAX );
            }
        }

        //Selection des indexes des points SIFTs au pif
        int indexes[SAMPLE_LENGTH_FOR_K_MEANS];
        for (int i=0; i<SAMPLE_LENGTH_FOR_K_MEANS; ++i)
        {
            int index;
            while (1)
            {
                index = rand()%nb_sifts;

                int *p = find(indexes,indexes+i,index);
                if (p == indexes+i)
                    break;
            }

            indexes[i] = index;
        }

        // On met les tous les SIFTs selectionnes dans une liste
        Vector sifts_list[SAMPLE_LENGTH_FOR_K_MEANS];
        for (int i=0; i<SAMPLE_LENGTH_FOR_K_MEANS; ++i)
        {
            this->get_feature_number(indexes[i]+1, sifts_list[i]);
        }

        //K-MEANS...
        int nb_iters = 1;
        int appartenances[SAMPLE_LENGTH_FOR_K_MEANS];
        std::vector<int> numbers(k);
        while (1)
        {
            cout << "-> Iteration #" << nb_iters << endl;

            bool has_changed = false;
            // Assigner chaque point e une classe
            for (int i=0; i<SAMPLE_LENGTH_FOR_K_MEANS; ++i)
            {
                Vector sift = sifts_list[i];
                int index_classe=0;
                double best_dist = INT_MAX;
                for (int j=0; j<k; ++j)
                {
                    double dist = centers[j] - sift;
                    if (dist<best_dist)
                    {
                        best_dist = dist;
                        index_classe = j;
                    }
                }
                if ((!has_changed) && (appartenances[i] != index_classe))
                    has_changed = true;
                appartenances[i] = index_classe;
            }

            if (!has_changed)
                break;

            // Calculer le barycentre de chaque classe
            for (int j=0; j<k; ++j)
                centers[j].reset();

            for (int j=0; j<k; ++j)
                numbers[j] = 0;

            for (int i=0; i<SAMPLE_LENGTH_FOR_K_MEANS; ++i)
            {
                int classe = appartenances[i];
                centers[classe] += sifts_list[i];
                numbers[classe]++;
            }

            for (int j=0; j<k; ++j)
            {
                if (numbers[j] == 0)
                    centers[j].reset();
                else
                    centers[j] *= 1./numbers[j];
            }

            nb_iters++;

        }
    }



    /**
	*   SAVING K-MEANS
	*/

	if (save) {
        cout << endl<< "Saving the k-centers..." << endl;

	    // Table creation
        string table_creation_query = "CREATE TABLE IF NOT EXISTS ";
        table_creation_query+=k_center_table_name;
        table_creation_query+=" (Center_ID int auto_increment,";


        for (unsigned int i=1; i<=NB_COEFF_FEATURES;i++){
            table_creation_query+="Coeff";
            table_creation_query+=to_string(i);
            table_creation_query+=" DOUBLE NOT NULL,";
        }

        table_creation_query+=" PRIMARY KEY(Center_ID))";

        if (!mysql_query(db_connection, table_creation_query.c_str())) {
            cout << "-> K-centers table creation query: OK."<<endl;
        }
        else {
            error_and_exit();
        }


        // Data insertion
        for (int j=1;j<=k;j++) { // Boucle sur les k-centres, on fait 1 requete par centre à sauver.
            string insert_k_centers_query = "INSERT INTO ";
            insert_k_centers_query+=k_center_table_name;
            insert_k_centers_query+=" (";

            for (unsigned int i=1; i<=NB_COEFF_FEATURES; i++){
                insert_k_centers_query+="Coeff";
                insert_k_centers_query+=to_string(i);
                if (i!=NB_COEFF_FEATURES)
                    insert_k_centers_query+=",";
            }

            insert_k_centers_query+=") VALUES (";


            for (unsigned int i=1; i<=NB_COEFF_FEATURES; i++){
                insert_k_centers_query+=to_string(centers[j-1][i-1]);
                if (i!=NB_COEFF_FEATURES)
                    insert_k_centers_query+=",";
            }
            insert_k_centers_query+=")";

            if (!mysql_query(db_connection, insert_k_centers_query.c_str())) {
                //cout << "Save-kcenters-query: OK"<<endl;
            }
            else {
                error_and_exit();
            }
        }

        cout << "-> K-centers successfully saved." << endl;
	}







}



unsigned int Feature_db::get_nbfeatures()
{
	// REQUETE SQL
	string get_feature_query = "SELECT COUNT(*) FROM features";

	if (!mysql_query(db_connection, get_feature_query.c_str())) {
		cout << "Get feature query: OK"<<endl;
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
	int nb = strtodouble(row[0]);

	//Liberation du jeu de resultat
	mysql_free_result(result);

	return nb;

}



void Feature_db::get_all_features_in_image(int index, std::vector<Feature> &features)
{
	// REQUETE SQL
	std::string get_feature_query = "SELECT X, Y, ";
	for (unsigned int i=1; i<=NB_COEFF_FEATURES;i++)
	{
		get_feature_query+="Coeff";
		get_feature_query+=to_string(i);
		if (i!= NB_COEFF_FEATURES)
			get_feature_query+=" ,";
	}
	get_feature_query += " FROM ";
	get_feature_query += table_name;
	get_feature_query+=" WHERE Img_ID=";
	get_feature_query+= to_string(index);


	if (!mysql_query(db_connection, get_feature_query.c_str())) {
		cout << "Get feature query: OK"<<endl;
	}
	else {
		error_and_exit();
	}

	//Declaration des pointeurs de structure
	MYSQL_RES *result = NULL;
	MYSQL_ROW row = NULL;

	unsigned int num_champs = 0;

	result = mysql_use_result(db_connection);

	//On recupere le nombre de champs
	num_champs = mysql_num_fields(result);

	//on stock les valeurs de la ligne choisie
	while (row = mysql_fetch_row(result))
	{
		Feature feature;

		//On declare un pointeur long non signe pour y stocker la taille des valeurs
		unsigned long *lengths;

		//On stocke cette taille dans le pointeur
		lengths = mysql_fetch_lengths(result);

		//On fait une boucle pour avoir la valeur de chaque champs
		feature.position.push_back(strtodouble(row[0]));
		feature.position.push_back(strtodouble(row[1]));
		feature.index_image = index;

		for (int i = 2; i < num_champs; i++)
			feature.coeffs.push_back(strtodouble(row[i]));

		features.push_back(feature);
	}

	cout << features.size() << " features in image " << index << endl;
	//Liberation du jeu de resultat
	mysql_free_result(result);

}





unsigned int Feature_db::get_nbimages()
{
	// REQUETE SQL
	string get_feature_query = "SELECT COUNT(DISTINCT Img_ID) FROM features";

	if (!mysql_query(db_connection, get_feature_query.c_str())) {
		cout << "Get feature query: OK"<<endl;
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
	int nb = strtodouble(row[0]);

	//Liberation du jeu de resultat
	mysql_free_result(result);

	return nb;

}



