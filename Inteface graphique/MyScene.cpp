#include "MyScene.h"
#include <QtGui>
#include <QWidget>
#include <QFileDialog>
#include <iostream>
#include <QPen>

using namespace std;

MyScene::MyScene() : QGraphicsScene()
{
	QString fichier = QFileDialog::getOpenFileName(0, "Ouvrir un fichier", QString(), "Images (*.png *.gif *.jpg *.jpeg)");
	QPixmap image = QPixmap(fichier);
	QSize size = image.size();
	
	impix = this->addPixmap(image);

	point1 = QPointF();
	point2 = QPointF();
	MyRectItem = new QGraphicsRectItem;
	rect = QRectF();
	numero=true;
}

 void MyScene::mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent)
 {
	 if (mouseEvent->button() == Qt::LeftButton) {
		 if (numero) {
			this->removeItem(MyRectItem);
			numero=false;
			point1 = mouseEvent->scenePos();
			MyRectItem = this->addRect(point1.x(), point1.y(), 0, 0);

			QPen * pen = new QPen;
			pen->setWidth(3);
			pen->setStyle(Qt::DashLine);
			pen->setBrush(Qt::red);
			MyRectItem->setPen(*pen);

			this->update();
		 }
	 }
 }

void MyScene::mouseMoveEvent( QGraphicsSceneMouseEvent * mouseEvent )
{	
	if (impix->isUnderMouse()) {
		if (!numero) {
		MyRectItem->setRect(QRectF(point1,mouseEvent->scenePos()));
		this->update();
		}
	}
}

void MyScene::mouseReleaseEvent(QGraphicsSceneMouseEvent * mouseEvent)
 {
	 if (mouseEvent->button() == Qt::LeftButton) {
		 if (!numero) {
			numero=true;
			point2 = mouseEvent->scenePos();
			rect = QRectF(point1,point2);
			
			SceneRes = new QGraphicsScene;
			SceneRes->addPixmap(this->getPixResult());
			QGraphicsView* ViewRes = new QGraphicsView(SceneRes);
			ViewRes->show();
		 }
	 }
 }


QPixmap MyScene::getPixResult()
{
	return (impix->pixmap()).copy(rect.toRect());
}