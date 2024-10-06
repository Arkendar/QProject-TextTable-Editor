#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onNewFile();
    void onOpenFile();
    void onSaveFile();
    void onClearText();
    void onRestoreText();
    void showAuthors();
    void showHelp();
    void findText();
    void replaceText();
    void copyText();
    void pasteText();

private:
    Ui::MainWindow *ui;
    QString tempFilePath = "temp.txt";

protected:
    void closeEvent(QCloseEvent *event) override;
};

#endif // MAINWINDOW_H
