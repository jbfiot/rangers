#include <QApplication>
#include <QtGui>
#include "MyScene.h"
#include <iostream>
 

/*J'ai rajout� un bout de code pour visualiser la petite r�gion s�lectionn�e,
il ne marche pas tr�s bien (fen�tres qui ne se ferment pas automatiquement)
mais c'�tait juste pour tester si le r�sultat �tait bon*/

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);


	MyScene* scene = new MyScene;
	QGraphicsView* view = new QGraphicsView(scene);
	view->show();

 
    return app.exec();
}
