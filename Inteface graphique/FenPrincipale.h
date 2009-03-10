#ifndef HEADER_FENPRINCIPALE
#define HEADER_FENPRINCIPALE

#include <iostream>
#include "Result.h"
#include "MyScene.h"
#include <QtGui>
#include <QApplication>

class FenPrincipale : public QMainWindow
{
	Q_OBJECT

	public:
		FenPrincipale();
		

	private:
		QDockWidget *dockImage;
		QWidget *ImageWidget;
		QDockWidget *dockServeur;
		QDockWidget *dockResults;
		QWidget *WidgetResults;
		std::vector<Result> T;
		QLineEdit *adressServer1;
		QLineEdit *portAdressServer;
		MyScene *scene;
		QScrollArea* scrollArea;

	public slots :
		void SendServer();
		void LoadImageW();
		void ShowResults();
		void LoadImageResult(char* str);
};

QWidget* showResult(const Result T);
#endif