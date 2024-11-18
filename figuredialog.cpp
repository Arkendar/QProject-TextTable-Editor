#include "figuredialog.h"
#include "ui_figuredialog.h"

//static const std::unordered_map<QString, int> figureMap = {
//    {"Rectangle", 1},
//    {"Circle", 2},
//    {"Triangle", 3}
//};

FigureDialog::FigureDialog(QGraphicsScene *scene, QWidget *parent) :
    QDialog(parent), editorScene(scene),
    ui(new Ui::FigureDialog)
{
    ui->setupUi(this);
    setWindowTitle("Add Figure");

    // Создание сцены
    previewScene = new QGraphicsScene(this);

    // Привязка сцены к previewView
    ui->graphicsView->setScene(previewScene);

    // Создание FigureTools
    FigureTools = new FigureTool(previewScene);

    // Кнопка для выбора цвета заливки
    connect(ui->FillButton, &QPushButton::clicked, this, [this]() {
        FigureTools->fillColor();
    });

    connect(ui->okButton, &QPushButton::clicked, this, &FigureDialog::acceptFigure);
    connect(ui->resetButton, &QPushButton::clicked, this, &FigureDialog::resetSettings);

    // Обновление превью при смене фигуры
    connect(ui->FigureSelector, QOverload<const QString &>::of(&QComboBox::currentIndexChanged), this,
            &FigureDialog::updatePreview);

    // Инициализируем превью
    updatePreview();
}

FigureDialog::~FigureDialog()
{
    delete ui;
}

void FigureDialog::acceptFigure()
{
    if (!currentPreviewItem) return;
    QGraphicsItem *newItem = currentPreviewItem;
    if (newItem) {
        newItem->setPos(100, 100);
        editorScene->addItem(newItem);
    }
    close();
}

void FigureDialog::resetSettings()
{
    fillColor = Qt::white;
    ui->FigureSelector->setCurrentIndex(0);
    updatePreview();
}

void FigureDialog::updatePreview()
{
    previewScene->clear();
    currentPreviewItem = nullptr;

    QString figureType = ui->FigureSelector->currentText();

    if (figureType == "Квадрат") {
        currentPreviewItem = previewScene->addRect(25, 25, 100, 100, QPen(Qt::black), QBrush(fillColor));
    } else if (figureType == "Круг") {
        currentPreviewItem = previewScene->addEllipse(25, 25, 100, 50, QPen(Qt::black), QBrush(fillColor));
    } else if (figureType == "Треугольник") {
        QPolygonF triangle;
        triangle << QPointF(75, 25) << QPointF(125, 75) << QPointF(25, 75);
        currentPreviewItem = previewScene->addPolygon(triangle, QPen(Qt::black), QBrush(fillColor));
    }
}
