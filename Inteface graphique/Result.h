#ifndef RESULT
#define RESULT
 
#include <iostream>
#include <QApplication>
#include <QWidget>
#include <QGraphicsScene>
#include <QEvent>

 
class Result 
{
	public :
		Result();
		Result(QPixmap *nImage,float nScore,std::string nLink);
		QPixmap *Image;
		float Score;
		std::string Link;

};
 
#endif
