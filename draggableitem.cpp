#include "DraggableItem.h"
#include <QBrush>


DraggableItem::DraggableItem(QGraphicsItem *item, QString shapeType)
{
    if (shapeType == "Квадрат") {
        QGraphicsRectItem *rectItem = dynamic_cast<QGraphicsRectItem *>(item);
        if (rectItem) {
            dragItem = new DraggableRectItem(rectItem);
        } else {
            throw std::logic_error("bad cast");
        }
    } else if (shapeType == "Круг") {
        QGraphicsEllipseItem *ellipseItem = dynamic_cast<QGraphicsEllipseItem *>(item);
        if (ellipseItem) {
            dragItem = new DraggableEllipseItem(ellipseItem);
        } else {
            throw std::logic_error("bad cast");
        }
    } else if (shapeType == "Треугольник") {
        QGraphicsPolygonItem *triangleItem = dynamic_cast<QGraphicsPolygonItem *>(item);
        if (triangleItem) {
            dragItem = new DraggableTriangleItem(triangleItem);
        } else {
            throw std::logic_error("bad cast");
        }
    }
}

DraggableItem::~DraggableItem(){
    delete dragItem;
}

DraggableRectItem::DraggableRectItem(QGraphicsRectItem *rectItem)
    : QGraphicsRectItem(rectItem->rect())
{
    setBrush(QBrush(Qt::white));
    setFlag(QGraphicsRectItem::ItemIsMovable); // Устанавливаем флаг перемещения
    setFlag(QGraphicsRectItem::ItemIsSelectable); // Флаг выделения
}

void DraggableRectItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    setBrush(QBrush(Qt::yellow)); // Изменяем цвет при захвате
    QGraphicsRectItem::mousePressEvent(event); // Вызываем базовый обработчик
}

void DraggableRectItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsRectItem::mouseMoveEvent(event); // Перемещение объекта
}

void DraggableRectItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    setBrush(QBrush(Qt::white)); // Возвращаем цвет при отпускании
    QGraphicsRectItem::mouseReleaseEvent(event); // Вызываем базовый обработчик
}

// ELLIPSE

DraggableEllipseItem::DraggableEllipseItem(QGraphicsEllipseItem *Item)
    : QGraphicsEllipseItem(Item->rect())
{
    setBrush(QBrush(Qt::white));
    setFlag(QGraphicsEllipseItem::ItemIsMovable); // Устанавливаем флаг перемещения
    setFlag(QGraphicsEllipseItem::ItemIsSelectable); // Флаг выделения
}

void DraggableEllipseItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    setBrush(QBrush(Qt::yellow)); // Изменяем цвет при захвате
    QGraphicsEllipseItem::mousePressEvent(event); // Вызываем базовый обработчик
}

void DraggableEllipseItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsEllipseItem::mouseMoveEvent(event); // Перемещение объекта
}

void DraggableEllipseItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    setBrush(QBrush(Qt::white)); // Возвращаем цвет при отпускании
    QGraphicsEllipseItem::mouseReleaseEvent(event); // Вызываем базовый обработчик
}

// TRIANGLE

DraggableTriangleItem::DraggableTriangleItem(QGraphicsPolygonItem *item)
    : QGraphicsPolygonItem(item->polygon())
{
    setBrush(QBrush(Qt::white));
    setFlag(QGraphicsItem::ItemIsMovable);   // Устанавливаем флаг перемещения
    setFlag(QGraphicsItem::ItemIsSelectable); // Устанавливаем флаг выделения
}

void DraggableTriangleItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    setBrush(QBrush(Qt::yellow)); // Изменяем цвет при захвате
    QGraphicsPolygonItem::mousePressEvent(event); // Вызываем базовый обработчик
}

void DraggableTriangleItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsPolygonItem::mouseMoveEvent(event); // Перемещение объекта
}

void DraggableTriangleItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    setBrush(QBrush(Qt::white)); // Возвращаем цвет при отпускании
    QGraphicsPolygonItem::mouseReleaseEvent(event); // Вызываем базовый обработчик
}
