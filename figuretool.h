#ifndef FIGURETOOL_H
#define FIGURETOOL_H

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsPolygonItem>
#include <QColorDialog>
#include <QInputDialog>

class FigureTool {
public:
    explicit FigureTool(QGraphicsScene *scene);

    void addRectangle();

    void addEllipse();

    void addTriangle();

    void fillColor();

    void changeStroke();

    void changeStrokeWidth();

    void resizeShape();

private:
    QGraphicsScene *scene;
};

#endif // FIGURETOOL_H
