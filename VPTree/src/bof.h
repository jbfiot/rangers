#ifndef BOF
#define BOF

#include "Feature.h"

#include <string>
#include <vector>
#include <assert.h>



class Bof
{

    /**
    *
    * Classe Bof = Bag-of-features
    *
    **/

    public:

        // Méthode pour obtenir la repartition dans les k classes du k-means.
        std::vector<double> get_kmeans_proba(std::vector<Feature> k_centers);

        // Méthode pour trouver la feuille la plus proche dans l'arbre.
        // A Faire ! :p
        // Typiquement qch comme : Leaf get_closest_leaf(VPTree tree);
        // A faire par le groupe serveur pour la recherche dans l'arbre quand la construction de l'arbre sera faite.


    private:
       std::vector<Feature> features;









};




#endif
