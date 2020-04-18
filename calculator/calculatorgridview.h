#ifndef CALCULATORGRIDVIEW_H
#define CALCULATORGRIDVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QScrollBar>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QGraphicsSvgItem>
#include <QTimer>
#include "logic/grid.h"

class CalculatorGridView : public QGraphicsView
{
    Q_OBJECT

private:
    QGraphicsScene* scene;
    int selectedX, selectedY, gridWidth, gridHeight;
    QGraphicsRectItem *selection;
    bool dragging;
    virtual void wheelEvent(QWheelEvent* );
    virtual void mousePressEvent(QMouseEvent *);
    virtual void mouseReleaseEvent(QMouseEvent *);

private slots:
    void trueDragging();

public:
    CalculatorGridView(QWidget* parent = 0);
    void render(CISpointer<Base>);
    QString selected() const;
};
#endif // CALCULATORGRIDVIEW_H
