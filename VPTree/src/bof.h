#ifndef BOF
#define BOF

#include "feature.h"

#include <string>
#include <vector>
#include <assert.h>



/**
*
* Classe Bof = Bag-of-features
*
**/
class Bof
{
    public:

		Bof(){}

		Bof(const std::vector<Feature> &feats) {init_Bof(feats);}

		// méthode permettant d'initialiser le contenu du Bof
		void init_Bof(const std::vector<Feature> &feats) {features = feats;}

        // Méthode pour obtenir la repartition dans les k classes du k-means.
        void get_kmeans_proba(std::vector<Vector> &k_centers, Vector &sigmas, Vector &proba /* Conteneur resultat */) ;

		double get_distance_region(Bof &other);


		

        // Méthode pour trouver la feuille la plus proche dans l'arbre.
        // A Faire ! :p
        // Typiquement qch comme : Leaf get_closest_leaf(VPTree tree);
        // A faire par le groupe serveur pour la recherche dans l'arbre quand la construction de l'arbre sera faite.


    //private:
       std::vector<Feature> features;









};




#endif
