#summary Conventions pour le preprocessing.

# Preprocessing #

L'étape de préprocessing consiste en un algo qui prend en entrée des images et stocke sur disque les descripteurs des points d'interet de ces images :

Image -> Points d'interet (Harris) -> Descripteurs (SIFT p ex) de ces points d'interets -> Fichier sur disque.

**1 image <=> 1 fichier de descripteurs**

On peut garder le meme nom et changer l'extension en .features :
**Nom\_de\_l'image.jpg <=> Nom\_de\_l'image.features**

# Conventions pour les fichiers de descripteurs #

  * **Ligne 1 :** chemin et dimensions de l'image et tags : **path/to/image,dim\_x,dim\_y,tags**
  * **Liges suivantes :** coordonnées du point puis descripteur : si on utilise SIFT : **x,y,x1,...,x128**

# Fichier bibliothèque de descripeurs #

ID d'un descripteur = Numero de ligne dans le fichier bibliothèque

1 Ligne : /chemin/de/l/image, numero dans le fichier de descripteur correspondant.