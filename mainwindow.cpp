#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QInputDialog>
#include <QCloseEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Привязываем действия из меню к слотам
    connect(ui->actionNew, &QAction::triggered, this, &MainWindow::onNewFile);
    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::onOpenFile);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::onSaveFile);
    connect(ui->actionClear, &QAction::triggered, this, &MainWindow::onClearText);
    connect(ui->actionReturn, &QAction::triggered, this, &MainWindow::onRestoreText);
    connect(ui->actionAuthors, &QAction::triggered, this, &MainWindow::showAuthors);
    connect(ui->actionHelp, &QAction::triggered, this, &MainWindow::showHelp);
    connect(ui->actionFind, &QAction::triggered, this, &MainWindow::findText);
    connect(ui->actionReplace, &QAction::triggered, this, &MainWindow::replaceText);
    connect(ui->actionCopy, &QAction::triggered, this, &MainWindow::copyText);
    connect(ui->actionPaste, &QAction::triggered, this, &MainWindow::pasteText);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Функция для создания нового файла
void MainWindow::onNewFile()
{
    ui->textEdit->clear();
}

// Функция для открытия файла
void MainWindow::onOpenFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Открыть файл"), "", tr("Текстовые файлы (*.txt);;Все файлы (*)"));
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QFile::ReadOnly | QFile::Text)) {
            QTextStream in(&file);
            ui->textEdit->setPlainText(in.readAll());
            file.close();
        }
    }
}

// Функция для сохранения файла
void MainWindow::onSaveFile()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Сохранить файл"), "", tr("Текстовые файлы (*.txt);;Все файлы (*)"));
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QFile::WriteOnly | QFile::Text)) {
            QTextStream out(&file);
            out << ui->textEdit->toPlainText();
            file.close();
        }
    }
}

void MainWindow::onClearText()
{
    // Сохранить текущее содержимое в временный файл
    QFile file(tempFilePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << ui->textEdit->toPlainText(); // Сохраняем текст в файл
        file.close();
    }

    ui->textEdit->clear(); // Очищаем текстовый редактор
}

void MainWindow::onRestoreText()
{
    QFile file(tempFilePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QString text = in.readAll(); // Читаем содержимое временного файла
        ui->textEdit->setPlainText(text); // Восстанавливаем текст в редакторе
        file.close();
    } else {
        QMessageBox::warning(this, tr("Ошибка"), tr("Невозможно открыть временный файл."));
    }
}

void MainWindow::findText()
{
    bool ok;
    QString searchText = QInputDialog::getText(this, tr("Найти"), tr("Введите текст для поиска:"), QLineEdit::Normal, "", &ok);

    if (ok && !searchText.isEmpty()) {
        if (!ui->textEdit->find(searchText)) {
            QMessageBox::information(this, tr("Поиск"), tr("Текст не найден"));
        }
    }
}

void MainWindow::replaceText()
{
    bool ok;
    QString searchText = QInputDialog::getText(this, tr("Найти"), tr("Введите текст для поиска:"), QLineEdit::Normal, "", &ok);

    if (ok && !searchText.isEmpty()) {
        QString replaceText = QInputDialog::getText(this, tr("Заменить"), tr("Заменить на:"), QLineEdit::Normal, "", &ok);

        if (ok && !replaceText.isEmpty()) {
            ui->textEdit->moveCursor(QTextCursor::Start);
            while (ui->textEdit->find(searchText)) {
                ui->textEdit->textCursor().insertText(replaceText);
            }
        }
    }
}

void MainWindow::copyText()
{
    ui->textEdit->copy();
}

void MainWindow::pasteText()
{
    ui->textEdit->paste();
}

void MainWindow::showAuthors()
{
    QMessageBox::information(this, "Авторы", "Сивов Семен\n"
                                             "Швецов Павел\n"
                                             "ИП-215");
}

void MainWindow::showHelp()
{
    QMessageBox::information(this, "Помощь", "Это базовый текстовый и табличный редактор.\n\nИспользуйте меню 'Файл' для создания, открытия, сохранения файлов.\nИспользуйте меню 'Инструменты' для дополнительных действий.");
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    // Проверяем, были ли изменения в тексте
    if (ui->textEdit->document()->isModified()) {
        QMessageBox::StandardButton resBtn = QMessageBox::question(this, tr("Закрыть"),
            tr("Документ был изменен.\n"
               "Хотите сохранить изменения?"),
            QMessageBox::No | QMessageBox::Yes,
            QMessageBox::Yes);
        if (resBtn == QMessageBox::Yes) {
            // Вызов функции сохранения
            onSaveFile();
        }
    }
    event->accept(); // Закрываем окно
}

void MainWindow::on_addRowButton_clicked()
{
    int currentRowCount = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(currentRowCount);
}


void MainWindow::on_removeRowButton_clicked()
{
    // Получаем текущий индекс выбранной строки
    int currentRow = ui->tableWidget->currentRow();

    // Если строка выбрана (т.е. индекс не равен -1), удаляем её
    if (currentRow != -1) {
        ui->tableWidget->removeRow(currentRow);
    } else {
        // Если строка не выбрана, можно показать сообщение пользователю
        QMessageBox::information(this, tr("Удаление строки"), tr("Пожалуйста, выберите строку для удаления."));
    }
}
