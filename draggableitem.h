#ifndef DRAGGABLEITEM_H
#define DRAGGABLEITEM_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QString>


class DraggableItem
{
public:
    DraggableItem(QGraphicsItem *item, QString shapeType);
    ~DraggableItem();

    QGraphicsItem *dragItem;
};

class DraggableRectItem : public QGraphicsRectItem
{
public:
    explicit DraggableRectItem(QGraphicsRectItem *rectItem);
    QGraphicsRectItem *rectItem;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
};

class DraggableEllipseItem : public QGraphicsEllipseItem
{
public:
    explicit DraggableEllipseItem(QGraphicsEllipseItem *Item);
    QGraphicsRectItem *Item;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
};

class DraggableTriangleItem : public QGraphicsPolygonItem
{
public:
    explicit DraggableTriangleItem(QGraphicsPolygonItem *Item);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // DRAGGABLEITEM_H
