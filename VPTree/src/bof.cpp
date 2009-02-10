#include "bof.h"


void Bof::get_kmeans_proba(std::vector<Feature> &k_centers, Vector &proba)  {
    Vector proba_j;
    proba.resize(k_centers.size());

    // Initialisation
    for (unsigned int i=0; i<k_centers.size();i++){
        proba[i]=0;
    }
    // Ajout des proba pour chaque feature du bag of feature. Le tout est divisé par le nombre de features.
    for (unsigned int j=0; j<features.size(); j++){
        features[j].get_kmeans_proba(k_centers, proba_j);
        cout <<proba_j<<endl;
        for (unsigned int i=0; i<k_centers.size();i++){
            proba[i] += proba_j[i];
        }

    }
    proba*=1./features.size();
    cout <<"proba.size="<<proba.size()<<endl;


}
