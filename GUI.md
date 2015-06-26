# GUI #

## Idées ##
  * On donne à l'utilisateur la possibilité de faire une recherche avec un nombre quelconque de contraintes
  * Une contrainte est : on veut qch qui ressemble à telle zone dans telle partie de l'image

## Point de vue utilisateur final ##
  1. L'utilisateur selectionne une image dans la base ou en parcourant son disque par exemple.
  1. Il choisit une zone dans l'image ([exemple](http://arthur.robots.ox.ac.uk:8080/search/?id=oxc1_hertford_000011)).
  1. Il définit la zone où il veut cette selection.
    * Toute l'image
    * Zone prédéfinie (haut/bas/en haut à droite/ etc)
    * Selection manuelle
  1. Il ajoute la contrainte.
  1. Il rajoute autant de contrainte qu'il veut jusqu'a avoir sa query complete.
  1. Il lance la recherche et admire les resultats ;)



## Visualisation des résultats ##

  * On peut s'inspirer du [moteur d'Oxford](http://arthur.robots.ox.ac.uk:8080/dosearch/?id=oxc1_hertford_000011&x1=73&y1=23&x2=531&y2=361&width_on_page=600&height_on_page=800&use_qe=false)

## Installation Qt 4.4 ##
http://doc.trolltech.com/4.4/install-win.html
http://doc.trolltech.com/4.4/requirements-win.html
Problème fatal error truc machin résolue : http://lists.trolltech.com/qt-interest/2007-01/msg00560.html