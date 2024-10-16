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
    connect(ui->actionSaveTable, &QAction::triggered, this, &MainWindow::onSaveTable);
    connect(ui->actionOpenTable, &QAction::triggered, this, &MainWindow::onOpenTable);
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
            onSaveFile();
        }
    }
    event->accept(); // Закрываем окно
}

// Функция для сохранения таблицы
void MainWindow::onSaveTable()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Сохранить таблицу"), "", tr("CSV файлы (*.csv);;Все файлы (*)"));
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QFile::WriteOnly | QFile::Text)) {
            QTextStream out(&file);
            int rowCount = ui->tableWidget->rowCount();
            int columnCount = ui->tableWidget->columnCount();

            // Записываем данные в формате CSV
            for (int row = 0; row < rowCount; ++row) {
                QStringList rowData;
                for (int column = 0; column < columnCount; ++column) {
                    QTableWidgetItem* item = ui->tableWidget->item(row, column);
                    if (item) {
                        rowData << item->text();
                    } else {
                        rowData << "";
                    }
                }
                out << rowData.join(",") << "\n";
            }
            file.close();
        } else {
            QMessageBox::warning(this, tr("Ошибка"), tr("Не удалось открыть файл для записи."));
        }
    }
}

// Функция для открытия8 таблицы
void MainWindow::onOpenTable()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Открыть таблицу"), "", tr("CSV файлы (*.csv);;Все файлы (*)"));
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QFile::ReadOnly | QFile::Text)) {
            QTextStream in(&file);
            ui->tableWidget->setRowCount(0); // Очистить текущие данные в таблице
            while (!in.atEnd()) {
                QString line = in.readLine();
                QStringList rowData = line.split(",");
                int currentRowCount = ui->tableWidget->rowCount();
                ui->tableWidget->insertRow(currentRowCount);
                for (int i = 0; i < rowData.size(); ++i) {
                    QTableWidgetItem *newItem = new QTableWidgetItem(rowData[i]);
                    ui->tableWidget->setItem(currentRowCount, i, newItem); // Устанавливаем данные в ячейку
                }
            }
            file.close();
        } else {
            QMessageBox::warning(this, tr("Ошибка"), tr("Не удалось открыть файл для чтения."));
        }
    }
}



//********ФУНКЦИИ СОЗДАННЫЕ ЧЕРЕЗ СЛОТЫ***************


void MainWindow::on_addRowButton_clicked()
{
    int currentRowCount = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(currentRowCount);
}


void MainWindow::on_removeRowButton_clicked()
{
    // Получаем текущий индекс выбранной строки
    int currentRow = ui->tableWidget->currentRow();

    // Если строка выбрана удаляем её
    if (currentRow != -1) {
        ui->tableWidget->removeRow(currentRow);
    } else {
        QMessageBox::information(this, tr("Удаление строки"), tr("Пожалуйста, выберите строку для удаления."));
    }
}

void MainWindow::on_addColButton_clicked()
{
    int currentColumnCount = ui->tableWidget->columnCount();
    ui->tableWidget->insertColumn(currentColumnCount);
}

void MainWindow::on_removeColButton_clicked()
{
    // Получаем текущий индекс выбранной колонки
        int currentColumn = ui->tableWidget->currentColumn();

        // Если колонка выбрана удаляем её
        if (currentColumn != -1) {
            ui->tableWidget->removeColumn(currentColumn);
        } else {
            QMessageBox::information(this, tr("Удаление колонки"), tr("Пожалуйста, выберите колонку для удаления."));
        }
}

void MainWindow::on_boldButton_clicked()
{
    // Изменение жирности текста в textEdit
    QTextCursor cursor = ui->textEdit->textCursor();
    if (cursor.hasSelection()) {
        QTextCharFormat format;
        format.setFontWeight(cursor.charFormat().fontWeight() == QFont::Bold ? QFont::Normal : QFont::Bold);
        cursor.mergeCharFormat(format);
    }

    // Изменение жирности текста в выделенных ячейках tableWidget
    QList<QTableWidgetItem*> selectedItems = ui->tableWidget->selectedItems();
    for (QTableWidgetItem* item : selectedItems) {
        if (item) {
            QFont font = item->font();
            font.setBold(!font.bold());
            item->setFont(font);
        }
    }
}

void MainWindow::on_italicButton_clicked()
{
    // Изменение курсива текста в textEdit
    QTextCursor cursor = ui->textEdit->textCursor();
    if (cursor.hasSelection()) {
        QTextCharFormat format;
        format.setFontItalic(!cursor.charFormat().fontItalic());
        cursor.mergeCharFormat(format);
    }

    // Изменение курсива текста в выделенных ячейках tableWidget
    QList<QTableWidgetItem*> selectedItems = ui->tableWidget->selectedItems();
    for (QTableWidgetItem* item : selectedItems) {
        if (item) {
            QFont font = item->font();
            font.setItalic(!font.italic());
            item->setFont(font);
        }
    }
}

void MainWindow::on_strikeoutButton_clicked()
{
    // Изменение зачеркнутого текста в textEdit
        QTextCursor cursor = ui->textEdit->textCursor();
        if (cursor.hasSelection()) {
            QTextCharFormat format;
            format.setFontStrikeOut(!cursor.charFormat().fontStrikeOut());
            cursor.mergeCharFormat(format);
        }

        // Изменение зачеркнутого текста в выделенных ячейках tableWidget
        QList<QTableWidgetItem*> selectedItems = ui->tableWidget->selectedItems();
        for (QTableWidgetItem* item : selectedItems) {
            if (item) {
                QFont font = item->font();
                font.setStrikeOut(!font.strikeOut());
                item->setFont(font);
            }
        }
}

void MainWindow::on_fontComboBox_currentFontChanged(const QFont &fontName)
{
    // Изменение шрифта в textEdit
       QFont font(fontName);
       ui->textEdit->setCurrentFont(font);

       // Изменение шрифта в выделенных ячейках tableWidget
       QList<QTableWidgetItem*> selectedItems = ui->tableWidget->selectedItems();
       for (QTableWidgetItem* item : selectedItems) {
           if (item) {
               item->setFont(font);
           }
       }
}

// Слот для обновления размера шрифта
void MainWindow::on_spinFontSize_valueChanged(int arg1)
{
        QTextCursor cursor = ui->textEdit->textCursor();
        if (cursor.hasSelection()) {
            QTextCharFormat format;
            format.setFontPointSize(arg1);
            cursor.mergeCharFormat(format);
        }

        QList<QTableWidgetItem*> selectedItems = ui->tableWidget->selectedItems();
        for (QTableWidgetItem* item : selectedItems) {
            if (item) {
                QFont font = item->font();
                font.setPointSize(arg1);
                item->setFont(font);
            }
        }
}
