#include "calculator/calculatorgridview.h"


CalculatorGridView::CalculatorGridView(QWidget* parent) :
    QGraphicsView(parent), selectedX(0), selectedY(0), gridWidth(0), gridHeight(0)
{

    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    scene = new QGraphicsScene(this);
    setScene(scene);

    setDragMode(QGraphicsView::ScrollHandDrag);
}

void CalculatorGridView::wheelEvent(QWheelEvent* event)
{
    double scaleFactor = 1.15;
    if(event->delta() > 0) {
        scale(scaleFactor, scaleFactor);
    } else {
        scale(1.0 / scaleFactor, 1.0 / scaleFactor);
    }
}

void CalculatorGridView::mousePressEvent(QMouseEvent * event)
{
    dragging = false;
    QTimer::singleShot(150, this, SLOT(trueDragging()));
    QGraphicsView::mousePressEvent(event);
}

void CalculatorGridView::mouseReleaseEvent(QMouseEvent * event)
{
    if (dragging==false) {
        QPointF point = mapToScene(event->pos()).toPoint();
        int newX = point.x()/20,
            newY = point.y()/20;
        if (newX>=0 && newY>=0 &&
                gridWidth>newX && gridHeight>newY) {
            scene->removeItem(scene->itemAt(selectedX*20, selectedY*20));
            scene->addRect(newX*20, newY*20, 20, 20, QPen("red"))->setZValue(2);
            selectedX = newX;
            selectedY = newY;
        }
    }
    QGraphicsView::mouseReleaseEvent(event);
}

void CalculatorGridView::trueDragging()
{
    dragging = true;
}

void CalculatorGridView::render(CISpointer<Base> obj)
{
    if (obj->getType()=="Grid") {
        scene->clear();
        Grid * grid = static_cast<Grid *>(&*obj);

        bool sizeChanged = false;
        if (gridWidth!=grid->width) {
            gridWidth = grid->width;
            sizeChanged = true;
        }
        if (gridHeight!=grid->height) {
            gridHeight = grid->height;
            sizeChanged = true;
        }

        for (int x=0; x<gridWidth; x++) {
            for (int y=0; y<gridHeight; y++) {
                CISpointer<Cell> cell = grid->cells[y*gridWidth+x];
                scene->addRect(x*20, y*20, 20, 20);
                if (x==selectedX && y==selectedY) {
                    scene->addRect(x*20, y*20, 20, 20, QPen("red"))->setZValue(2);
                }
                if (cell!=0) {
                    QString path = QString::fromStdString(cell->toPath());
                    QGraphicsSvgItem *item = new QGraphicsSvgItem(":/resources/" + path + ".svg");
                    item->setPos(x*20, y*20);
                    item->setZValue(1);
                    scene->addItem(item);
                }
            }
        }
        if (sizeChanged)
            setSceneRect(scene->itemsBoundingRect());
    }
}

QString CalculatorGridView::selected() const
{
    return QString::number(selectedX) + "," + QString::number(selectedY);
}
