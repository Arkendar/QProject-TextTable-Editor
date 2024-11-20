// MovingObject.h
#ifndef MOVINGOBJECT_H
#define MOVINGOBJECT_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QObject>

class MovingObject : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
private:
    int dx, dy; // Скорость по X и Y
    QGraphicsScene *scene;

public:
    MovingObject(QGraphicsScene *scene, const QPixmap &pixmap, int speedX, int speedY);

public slots:
    void move();
};

#endif // MOVINGOBJECT_H
