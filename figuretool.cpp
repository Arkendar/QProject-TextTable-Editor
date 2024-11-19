#include "FigureTool.h"

// Конструктор, принимающий сцену
FigureTool::FigureTool(QGraphicsScene *scene)
    : scene(scene) {}

// Метод для добавления прямоугольника
QGraphicsItem* FigureTool::addRectangle() {
    QRectF rect(0, 0, 100, 100);
    auto *item = new QGraphicsRectItem(rect);
    item->setBrush(Qt::white);
    item->setPen(QPen(Qt::black, 2));
    item->setPos(100, 100);
    scene->addItem(item);
    return item;
}

// Метод для добавления эллипса
QGraphicsItem* FigureTool::addEllipse() {
    QRectF rect(0, 0, 50, 50);
    auto *item = new QGraphicsEllipseItem(rect);
    item->setBrush(Qt::white);
    item->setPen(QPen(Qt::black, 2));
    item->setPos(150, 150);
    scene->addItem(item);
    return item;
}

// Метод для добавления треугольника
QGraphicsItem* FigureTool::addTriangle() {
    QPolygonF triangle;
    triangle << QPointF(0, 50) << QPointF(50, 50) << QPointF(25, 0);

    auto *item = new QGraphicsPolygonItem(triangle);
    item->setBrush(Qt::white);
    item->setPen(QPen(Qt::black, 2));
    item->setPos(200, 200);
    scene->addItem(item);
    return item;
}

// Метод для изменения цвета заливки
void FigureTool::fillColor() {
    QColor fillColor = QColorDialog::getColor(Qt::white, nullptr, "Select Fill Color");
    if (fillColor.isValid()) {
        for (auto *item : scene->selectedItems()) {
            if (auto *shape = dynamic_cast<QAbstractGraphicsShapeItem*>(item)) {
                shape->setBrush(fillColor);
            }
        }
    }
}

// Метод для изменения цвета обводки
void FigureTool::changeStroke() {
    QColor strokeColor = QColorDialog::getColor(Qt::black, nullptr, "Select Stroke Color");
    if (strokeColor.isValid()) {
        for (auto *item : scene->selectedItems()) {
            if (auto *shape = dynamic_cast<QAbstractGraphicsShapeItem*>(item)) {
                QPen pen = shape->pen();
                pen.setColor(strokeColor);
                shape->setPen(pen);
            }
        }
    }
}

// Метод для изменения толщины обводки
void FigureTool::changeStrokeWidth() {
    bool ok;
    int newWidth = QInputDialog::getInt(nullptr, "Stroke Width",
                                        "Enter width (1-20):",
                                        2, 1, 20, 1, &ok);
    if (ok) {
        for (auto *item : scene->selectedItems()) {
            if (auto *shape = dynamic_cast<QAbstractGraphicsShapeItem*>(item)) {
                QPen pen = shape->pen();
                pen.setWidth(newWidth);
                shape->setPen(pen);
            }
        }
    }
}

// Метод для изменения размеров фигур
void FigureTool::resizeShape() {
    for (auto *item : scene->selectedItems()) {
        if (auto *rectItem = dynamic_cast<QGraphicsRectItem*>(item)) {
            QRectF currentRect = rectItem->rect();
            bool ok;
            int newWidth = QInputDialog::getInt(nullptr, "Resize Rectangle",
                                                "Enter new width:",
                                                currentRect.width(), 1, 1000, 1, &ok);
            if (ok) {
                int newHeight = QInputDialog::getInt(nullptr, "Resize Rectangle",
                                                     "Enter new height:",
                                                     currentRect.height(), 1, 1000, 1, &ok);
                if (ok) {
                    rectItem->setRect(0, 0, newWidth, newHeight);
                }
            }
        }
    }
}
