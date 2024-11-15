#ifndef DRAGGABLEITEM_H
#define DRAGGABLEITEM_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>

class DraggableItem : public QGraphicsRectItem
{
public:
    explicit DraggableItem(const QRectF &rect, QGraphicsItem *parent = nullptr);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // DRAGGABLEITEM_H
