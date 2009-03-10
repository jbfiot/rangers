#include <iostream>
#include <string>
#include "protocol.h"
#include "MyScene.h"
#include "FenPrincipale.h"


#include <QApplication>

#pragma comment(lib, "ws2_32.lib")

FenPrincipale::FenPrincipale()
{	
	showMaximized();
	//showNormal();

	QMenu *menuFichier = menuBar()->addMenu("&Fichier");

	QAction *actionLoadImage = menuFichier->addAction("&Load Image");	
	actionLoadImage->setIcon(QIcon("Icons/fileopen.png"));
	menuFichier->addAction(actionLoadImage);

	QAction *actionExit = menuFichier->addAction("&Quitter");
	actionExit->setIcon(QIcon("Icons/fileclose.png"));
	menuFichier->addAction(actionExit);

	//QMenu *menuTools = menuBar()->addMenu("&Tools");

	QMenu *menuComm = menuBar()->addMenu("&Communication");

	QAction *actionSend = menuComm->addAction("&Send to server");	
	actionSend->setIcon(QIcon("Icons/ok.png"));

	// Création de la barre d'outils

    QToolBar *toolBarFichier = addToolBar("Fichier");
    toolBarFichier->addAction(actionLoadImage);
	toolBarFichier->addAction(actionExit);
	toolBarFichier->addSeparator();
	toolBarFichier->addAction(actionSend);
	
	QObject::connect(actionLoadImage, SIGNAL(triggered()), this, SLOT(LoadImageW()));
    QObject::connect(actionExit, SIGNAL(triggered()), this, SLOT(close()));
    QObject::connect(actionSend, SIGNAL(triggered()), this, SLOT(SendServer()));
	QObject::connect(actionSend, SIGNAL(triggered()), this, SLOT(ShowResults()));
    
	//
	// Création des docks
	//

	// dock IMAGE

	dockImage = new QDockWidget("Image", this);
	setCentralWidget(dockImage);

	ImageWidget = new QWidget;
	dockImage->setWidget(ImageWidget);

	// dock SERVEUR

	dockServeur = new QDockWidget("Serveur", this);
	addDockWidget(Qt::LeftDockWidgetArea, dockServeur);


	QWidget *paramDock = new QWidget;
	dockServeur->setWidget(paramDock);

	QSize s(220,20);

	adressServer1 = new QLineEdit(QString("138.195.102.25"));
	adressServer1->setMaximumSize(s);

	QHBoxLayout *adressLayout = new QHBoxLayout;
	adressLayout->addWidget(adressServer1);

	QWidget *adressWidget = new QWidget;
	adressWidget->setLayout(adressLayout);

	portAdressServer = new QLineEdit(QString("6006"));
	portAdressServer->setMaximumSize(s);

	QHBoxLayout *portLayout = new QHBoxLayout;
	portLayout->addWidget(portAdressServer);

	QWidget *portAdressWidget = new QWidget;
	portAdressWidget->setLayout(portLayout);

	QLabel *adressLabel = new QLabel("Adresse IP",paramDock);
	QLabel *portLabel = new QLabel("Port",paramDock);

	QPushButton *okServer = new QPushButton("Send");
	QObject::connect(okServer, SIGNAL(clicked()),this,SLOT(SendServer()));
	QObject::connect(okServer, SIGNAL(clicked()),this,SLOT(ShowResults()));

	QVBoxLayout *paramLayout = new QVBoxLayout(paramDock);
	paramLayout->addWidget(adressLabel);
	paramLayout->addWidget(adressWidget);
	paramLayout->addWidget(portLabel);
	paramLayout->addWidget(portAdressWidget);
	paramLayout->addWidget(okServer);
	paramLayout->setAlignment(Qt::AlignLeft);
	paramDock->setLayout(paramLayout);
	//dockServeur->setGeometry(QRect(100,200,200,250));
	dockServeur->setMaximumSize(250,200);

	// dock RESULTATS

	dockResults = new QDockWidget("Resultats",this);
	addDockWidget(Qt::RightDockWidgetArea, dockResults);
	dockResults->setMaximumWidth(250);

	WidgetResults = new QWidget;
	scrollArea = new QScrollArea;

	dockResults->setWidget(scrollArea);


	

	QPixmap *mini = new QPixmap(QString("test.jpg"));
	Result R(mini,98,"t");
	QPixmap *mini2 = new QPixmap(QString("9143.gif.jpg"));
	Result R2(mini2,95,"v");
	QPixmap *mini3 = new QPixmap(QString("test.jpg"));
	Result R3(mini3,92,"t");
	QPixmap *mini4 = new QPixmap(QString("test.jpg"));
	Result R4(mini4,90,"t");
	QPixmap *mini5 = new QPixmap(QString("test.jpg"));
	Result R5(mini5,88,"t");
	QPixmap *mini6 = new QPixmap(QString("test.jpg"));
	Result R6(mini6,86,"t");
	QPixmap *mini7 = new QPixmap(QString("test.jpg"));
	Result R7(mini7,84,"t");
	QPixmap *mini8 = new QPixmap(QString("test.jpg"));
	Result R8(mini8,82,"t");
	QPixmap *mini9 = new QPixmap(QString("test.jpg"));
	Result R9(mini9,81,"t");
	QPixmap *mini10 = new QPixmap(QString("test.jpg"));
	Result R10(mini10,79,"t");
	QPixmap *mini11 = new QPixmap(QString("test.jpg"));
	Result R11(mini11,78,"t");
	QPixmap *mini12 = new QPixmap(QString("test.jpg"));
	Result R12(mini12,77,"t");
	QPixmap *mini13 = new QPixmap(QString("test.jpg"));
	Result R13(mini13,76,"t");
	QPixmap *mini14 = new QPixmap(QString("test.jpg"));
	Result R14(mini14,75,"t");

	T.push_back(R);
	T.push_back(R2);
	T.push_back(R3);
	T.push_back(R4);
	T.push_back(R5);
	T.push_back(R6);
	T.push_back(R7);
	T.push_back(R8);
	T.push_back(R9);
	T.push_back(R10);
	T.push_back(R11);
	T.push_back(R12);
	T.push_back(R13);
	T.push_back(R14);

}



void FenPrincipale::LoadImageW() {
	delete ImageWidget;
	ImageWidget = new QWidget;
	dockImage->setWidget(ImageWidget);
	
	QString fileName
        = QFileDialog::getOpenFileName(this, tr("Load Image"),QString(), "Images (*.png *.gif *.jpeg *.jpg)");
    if (fileName.isEmpty())
        return;
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly)) {
        QString msg = tr("Failed to open %1\n%2")
                        .arg(fileName)
                        .arg(file.errorString());
        QMessageBox::warning(this, tr("Error"), msg);
        return;
    }

	scene = new MyScene(fileName);
	QGraphicsView *view = new QGraphicsView(scene);

	view->setMaximumSize(scene->size+QSize(10,10));
	//view->show();

	//image->setPixmap(QPixmap(fileName));
	QVBoxLayout *dockLayout = new QVBoxLayout;
	dockLayout->addWidget(view);
	ImageWidget->setLayout(dockLayout);
	
	dockImage->show();
	
}
void FenPrincipale::SendServer() {

	// Lecture de l'adresse et du port
	
	int port;
	sscanf(portAdressServer->text().toStdString().c_str(),"%d",&port);


	// Config du serveur

	WSADATA WSAData;
	WSAStartup(MAKEWORD(2,0), &WSAData);
	SOCKET sock;
	SOCKADDR_IN sin;
	sock = socket(AF_INET, SOCK_STREAM,0);

	sin.sin_addr.s_addr	= inet_addr(adressServer1->text().toStdString().c_str());
	sin.sin_family		= AF_INET;
	sin.sin_port		= htons(port);
	sock = socket(AF_INET,SOCK_STREAM,0);

	::connect(sock, (SOCKADDR *)&sin, sizeof(sin));
	
	Protocol P(sock);

	Image im=scene->getRawImage();
	
	int err=P.SendImage(im);

	if (err==0) 
		QMessageBox::information(this,"Envoi des données au serveur","Les données sont envoyées");
	else if(err==-1)
		QMessageBox::information(this,"Envoi des données au serveur","Erreur, les données n'ont pu être envoyées");
}
void FenPrincipale::ShowResults() {
	QVBoxLayout *layoutScores = new QVBoxLayout;
	for (unsigned int i=0;i<T.size();i++) {
		layoutScores->addWidget(showResult(T[i]));
	}

	
	WidgetResults->setLayout(layoutScores);

	scrollArea->setWidget(WidgetResults);

	dockResults->show();


}
QWidget* showResult(const Result T) {
	QWidget *res = new QWidget;
	
	QFont font;
    font.setPointSize(18);
    font.setBold(true);
    font.setWeight(75);
   

	QLabel *labelImage = new QLabel;
	labelImage->setPixmap(*(T.Image));
	char c[20];
	sprintf_s(c,20,"%d",int(T.Score));	
	QLabel *labelScore = new QLabel(QString(c));
	labelScore->setFont(font);
	QHBoxLayout *layoutResult = new QHBoxLayout;
	layoutResult->addWidget(labelImage);
	layoutResult->addSpacing(15);
	layoutResult->addWidget(labelScore);
	res->setLayout(layoutResult);
	res->setFixedHeight(100);

	return res;


}

void FenPrincipale::LoadImageResult(char* str) {

	scene = new MyScene(QString(str));
	QGraphicsView *view = new QGraphicsView(scene);

	view->setFixedSize(scene->size+QSize(10,10));
	//view->show();

	//image->setPixmap(QPixmap(fileName));
	QVBoxLayout *dockLayout = new QVBoxLayout;
	dockLayout->addWidget(view);
	ImageWidget->setLayout(dockLayout);
	
	dockImage->show();
}


