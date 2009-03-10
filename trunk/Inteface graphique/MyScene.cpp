#include "protocol.h"
#include "MyScene.h"
#include <QtGui>
#include <QWidget>
#include <QFileDialog>

MyScene::MyScene() : QGraphicsScene()
{
	QString fichier = QFileDialog::getOpenFileName(0, "Ouvrir un fichier", QString(), "Images (*.png *.gif *.jpg *.jpeg)");
	QPixmap image = QPixmap(fichier);
	size = image.size();
	
	impix=addPixmap(image);

	point1 = QPointF();
	point2 = QPointF();
	numero=true;
	MyRectItem=new QGraphicsRectItem;
	rect = QRectF();

}

MyScene::MyScene(QString fileName) : QGraphicsScene()
{
	
	QPixmap image = QPixmap(fileName);
	size=image.size();
	impix=addPixmap(image);

	point1 = QPointF();
	point2 = QPointF();
	numero=true;
	MyRectItem=new QGraphicsRectItem;
	rect = QRectF();
	SceneSelection = new QGraphicsScene;
	Selection = SceneSelection->addPixmap(image);
}

 void MyScene::mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent)
 {
	 if (mouseEvent->button() == Qt::LeftButton) {
		 if	(numero) {
			removeItem(MyRectItem);
			numero=false;
			point1 = mouseEvent->scenePos();
			MyRectItem = addRect(point1.x(), point1.y(), 0, 0);

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

			qreal minx = (point1.x()<point2.x())?point1.x():point2.x();
			qreal miny = (point1.y()<point2.y())?point1.y():point2.y();
			qreal maxx = (point1.x()>point2.x())?point1.x():point2.x();
			qreal maxy = (point1.y()>point2.y())?point1.y():point2.y();
			QPointF TopLeft=QPointF(minx,miny);
			QPointF BottomRight=QPointF(maxx,maxy);
			rect = QRectF(TopLeft,BottomRight);
			
			//SceneSelection->removeItem(Selection);
			SceneSelection = new QGraphicsScene;
			Selection = SceneSelection->addPixmap(this->getPixResult());

			/*QGraphicsView* ViewSelection = new QGraphicsView(SceneSelection);
			ViewSelection->show();*/
		 }
	 }
 }

QPixmap MyScene::getPixResult()
{
	return (impix->pixmap()).copy(rect.toRect());
}

Image MyScene::getRawImage()
{	
	QImage res = (this->getPixResult()).toImage();

	int width = res.width();
	int height = res.height();
	int** IntArray = new int*[height];
	
	for(int i=0;i<height;i++){
		IntArray[i] = new int[width];
	}

	for(int i=0;i<height;i++){
		for(int j=0;j<width;j++){
			IntArray[i][j] = qGray(res.pixel(j,i));
		}
	}

	Image im;
	im.data=IntArray;
	im.x_size=height;
	im.y_size=width;


	
	/*for (int i=0;i<im.x_size;i++) {
		for (int j=0;j<im.y_size;j++) {
			fprintf_s(f,"%d\t",im.data[i][j]);
		}
		fprintf_s(f,"\n");
	}*/

	return im;
}