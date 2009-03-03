#ifndef DEF_MYSCENE
#define DEF_MYSCENE
 
#include <QApplication>
#include <QWidget>
#include <QGraphicsScene>
#include <QEvent>

 
class MyScene : public QGraphicsScene
{
	Q_OBJECT

    public:
    MyScene();
	MyScene(QString fileName);
	QSize size;
	QPixmap getPixResult();

	public slots:

	protected:
	void mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent * mouseEvent);
	void mouseMoveEvent( QGraphicsSceneMouseEvent * mouseEvent);

    private:
	bool numero;
	QPointF point1;
	QPointF point2;
	QRectF rect;
	QGraphicsRectItem * MyRectItem;
	QGraphicsPixmapItem *impix;
	QGraphicsScene * SceneSelection;
	QGraphicsPixmapItem* Selection;

};
 
#endif
