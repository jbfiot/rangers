#include "FenPrincipale.h"
#include "MyScene.h"

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
	
	QObject::connect(actionLoadImage, SIGNAL(triggered()), this, SLOT(LoadImage()));
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

	QTextEdit *adressServer1 = new QTextEdit;
	adressServer1->setFixedSize(s);

	QHBoxLayout *adressLayout = new QHBoxLayout;
	adressLayout->addWidget(adressServer1);

	QWidget *adressWidget = new QWidget;
	adressWidget->setLayout(adressLayout);

	QTextEdit *portAdressServer = new QTextEdit;
	portAdressServer->setFixedSize(s);

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
	dockServeur->setFixedSize(250,200);

	// dock RESULTATS

	dockResults = new QDockWidget("Resultats",this);
	addDockWidget(Qt::RightDockWidgetArea, dockResults);
	dockResults->setMinimumWidth(250);

	WidgetResults = new QWidget;
	dockResults->setWidget(WidgetResults);
	

	QPixmap *mini = new QPixmap(QString("test.jpg"));
	Result R(mini,98,"t");
	
	T.push_back(R);
}

void FenPrincipale::LoadImage() {
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
	//QLabel *image=new QLabel;
	MyScene *scene = new MyScene(fileName);
	QGraphicsView *view = new QGraphicsView(scene);

	view->setFixedSize(scene->size+QSize(10,10));
	//view->show();

	//image->setPixmap(QPixmap(fileName));
	QVBoxLayout *dockLayout = new QVBoxLayout;
	dockLayout->addWidget(view);
	ImageWidget->setLayout(dockLayout);
	
	dockImage->show();
	
}
void FenPrincipale::SendServer() {
	QMessageBox::information(this,"Envoi des données au serveur","Les données sont envoyées");

}
void FenPrincipale::ShowResults() {
	QHBoxLayout *layoutScores = new QHBoxLayout;
	for (unsigned int i=0;i<T.size();i++) {
		layoutScores->addWidget(showResult(T[i]));
	}

	WidgetResults->setLayout(layoutScores);
	dockResults->setFixedSize(250,T.size()*150);
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
	
	return res;


}