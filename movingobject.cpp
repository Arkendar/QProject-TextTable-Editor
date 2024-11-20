// MovingObject.cpp
#include "MovingObject.h"
#include <QGraphicsScene>
#include <cmath>
#include "Wall.h"


MovingObject::MovingObject(QGraphicsScene *scene, const QPixmap &pixmap, int speedX, int speedY)
    : speedX(speedX), speedY(speedY), scene(scene) {
    setPixmap(pixmap);  // Устанавливаем картинку для объекта

}

void MovingObject::move()
{
    // Двигаем объект
    setPos(x() + speedX, y() + speedY);

    // Проверяем столкновение
    checkCollision();
    // Проверка столкновения с границами сцены
    checkBoundaryCollision();
}

void MovingObject::checkCollision()
{
    // Получаем все элементы на сцене
    QList<QGraphicsItem*> allItems = scene->items();

    for (QGraphicsItem *item : allItems) {
        // Проверяем, если это не сам объект и если объекты пересекаются
        // И исключаем из проверки элементы, которые являются границами сцены
        if (item != this && this->collidesWithItem(item) && !dynamic_cast<Wall*>(item)) {
            // Получаем позицию центра столкнувшегося объекта
            QRectF itemRect = item->boundingRect();
            QPointF itemCenter = item->mapToScene(itemRect.center());
            QPointF collisionVector = itemCenter - mapToScene(boundingRect().center());

            // Нормализуем вектор столкновения
            qreal length = sqrt(collisionVector.x() * collisionVector.x() + collisionVector.y() * collisionVector.y());
            if (length != 0) {
                collisionVector /= length;  // Нормализуем вектор

                // Рассчитываем скалярное произведение для отражения
                qreal dotProduct = speedX * collisionVector.x() + speedY * collisionVector.y();

                // Отражаем скорость от столкновения
                speedX -= 2 * dotProduct * collisionVector.x();
                speedY -= 2 * dotProduct * collisionVector.y();

                // Чтобы избежать уменьшения скорости, сохраняем исходную скорость
                qreal currentSpeed = sqrt(speedX * speedX + speedY * speedY);
                qreal originalSpeed = sqrt(this->speedX * this->speedX + this->speedY * this->speedY);
                if (currentSpeed != 0) {
                    speedX = (speedX / currentSpeed) * originalSpeed;
                    speedY = (speedY / currentSpeed) * originalSpeed;
                }

                // Чтобы объект не прошел сквозь другие объекты, минимально корректируем его позицию
                qreal overlap = 5.0; // Слишком большое значение может привести к резкому движению
                QPointF correction = collisionVector * overlap;

                // Исправляем позицию объекта
                setPos(x() - correction.x(), y() - correction.y());
            }
        }
    }
}

void MovingObject::checkBoundaryCollision()
{
    // Проверка для левой и правой границы
    if (x() <= 0 || x() >= scene->sceneRect().width() - pixmap().width()) {
        speedX = -speedX;  // Инвертируем горизонтальную скорость
    }

    // Проверка для верхней и нижней границы
    if (y() <= 0 || y() >= scene->sceneRect().height() - pixmap().height()) {
        speedY = -speedY;  // Инвертируем вертикальную скорость
    }
}

