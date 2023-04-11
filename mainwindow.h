#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Menubuttonsession_clicked();
    void on_Backbuttonmenu_clicked();
    void on_Downarrowmenu_clicked();
    void on_Uparrowmenu_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
