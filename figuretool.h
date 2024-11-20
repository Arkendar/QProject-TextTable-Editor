#ifndef FIGURETOOL_H
#define FIGURETOOL_H

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsPolygonItem>
#include <QColorDialog>
#include <QInputDialog>
#include "draggableitem.h"

class FigureTool {
public:
    explicit FigureTool(QGraphicsScene *scene);

    QGraphicsItem* addRectangle();

    QGraphicsItem* addEllipse();

    QGraphicsItem* addTriangle();

    void fillColor(QGraphicsItem *item);

    void changeStroke();

    void changeStrokeWidth();

    void resizeShape();

private:
    QGraphicsScene *scene;
};

#endif // FIGURETOOL_H
