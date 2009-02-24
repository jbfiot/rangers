#include <QApplication>
#include <QtGui>
#include "MyScene.h"
#include <iostream>
 

/*J'ai rajouté un bout de code pour visualiser la petite région sélectionnée,
il ne marche pas très bien (fenêtres qui ne se ferment pas automatiquement)
mais c'était juste pour tester si le résultat était bon*/

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);


	MyScene* scene = new MyScene;
	QGraphicsView* view = new QGraphicsView(scene);
	view->show();

 
    return app.exec();
}
