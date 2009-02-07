#include "bof.h"


Vector Bof::get_kmeans_proba(std::vector<Feature> k_centers){
    Vector proba,proba_j;
    // Initialisation
    for (unsigned int i=0; i<k_centers.size();i++){
        proba[i]=0;
    }
    // Ajout des proba pour chaque feature du bag of feature. Le tout est divisé par le nombre de features.
    for (unsigned int j=0; j<features.size(); j++){
        proba_j = features[j].get_kmeans_proba(k_centers);
        for (unsigned int i=0; i<k_centers.size();i++){
            proba[i] += proba_j[i]/features.size();
        }

    }

    return proba;


}
