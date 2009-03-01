#ifndef HEADER_FENPRINCIPALE
#define HEADER_FENPRINCIPALE

#include <iostream>
#include "Result.h"
#include <QtGui>


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
		

	public slots :
		void SendServer();
		void LoadImage();
		void ShowResults();
};

QWidget* showResult(const Result T);
#endif