// MovingObject.cpp
#include "MovingObject.h"
#include <QGraphicsScene>

MovingObject::MovingObject(QGraphicsScene *scene, const QPixmap &pixmap, int speedX, int speedY)
    : dx(speedX), dy(speedY), scene(scene) {
    setPixmap(pixmap);  // Устанавливаем картинку для объекта
}

void MovingObject::move() {
    // Перемещение объекта
    moveBy(dx, dy);

    // Проверяем столкновение с краями сцены (стенами)
    if (x() <= 5 || x() + boundingRect().width() >= scene->width() - 5) {
        dx = -dx;  // Отражаем объект по оси X
    }
    if (y() <= 5 || y() + boundingRect().height() >= scene->height() - 5) {
        dy = -dy;  // Отражаем объект по оси Y
    }

    // Проверяем столкновение с другими объектами на сцене
    for (auto *item : scene->collidingItems(this)) {
        if (item != this) {  // Проверяем, что это не сам объект
            dx = -dx;  // Отражаем объект по оси X
            dy = -dy;  // Отражаем объект по оси Y
        }
    }
}
