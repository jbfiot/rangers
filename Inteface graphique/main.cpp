#include <QApplication>
#include <QtGui>
#include "FenPrincipale.h"
#include "MyScene.h"
#include "protocol.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[])
{
	/*	--------------------------------
	Ouverture de la fenêtre
	------------------------------------*/

    QApplication app(argc, argv);

    FenPrincipale fenetre;
	//fenetre.setWindowState(fenetre.windowState()^Qt::WindowFullScreen);
    fenetre.show();

	app.exec();

	/*	--------------------------------
	Création du serveur
	------------------------------------*/		

	
    return 0;
}