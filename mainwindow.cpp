#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
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
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Text Files (*.txt);;All Files (*)"));
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
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "", tr("Text Files (*.txt);;All Files (*)"));
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
        QMessageBox::warning(this, tr("Error"), tr("Unable to open the temporary file."));
    }
}

void MainWindow::findText()
{
    bool ok;
    QString searchText = QInputDialog::getText(this, tr("Find"), tr("Find text:"), QLineEdit::Normal, "", &ok);

    if (ok && !searchText.isEmpty()) {
        if (!ui->textEdit->find(searchText)) {
            QMessageBox::information(this, tr("Find"), tr("Text not found"));
        }
    }
}

void MainWindow::replaceText()
{
    bool ok;
    QString searchText = QInputDialog::getText(this, tr("Find"), tr("Find text:"), QLineEdit::Normal, "", &ok);

    if (ok && !searchText.isEmpty()) {
        QString replaceText = QInputDialog::getText(this, tr("Replace"), tr("Replace with:"), QLineEdit::Normal, "", &ok);

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
    QMessageBox::information(this, "Authors", "This application was created by Arkendar.");
}

void MainWindow::showHelp()
{
    QMessageBox::information(this, "Help", "This is a basic text and table editor.\n\nUse File menu to create, open, save files.\nUse Tool menu for additional actions.");
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    // Проверяем, были ли изменения в тексте
    if (ui->textEdit->document()->isModified()) {
        QMessageBox::StandardButton resBtn = QMessageBox::question(this, tr("Close"),
                                                                    tr("The document has been modified.\n"
                                                                       "Do you want to save your changes?"),
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
