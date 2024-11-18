#include "DraggableItem.h"
#include <QBrush>


DraggableItem::DraggableItem(const QRectF &rect, QGraphicsItem *parent)
{
    setFlag(QGraphicsItem::ItemIsMovable); // Устанавливаем флаг перемещения
    setFlag(QGraphicsItem::ItemIsSelectable); // Флаг выделения
}

void DraggableItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    setBrush(QBrush(Qt::yellow)); // Изменяем цвет при захвате
    QGraphicsItem::mousePressEvent(event); // Вызываем базовый обработчик
}

void DraggableItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseMoveEvent(event); // Перемещение объекта
}

void DraggableItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    setBrush(QBrush(Qt::white)); // Возвращаем цвет при отпускании
    QGraphicsItem::mouseReleaseEvent(event); // Вызываем базовый обработчик
}
