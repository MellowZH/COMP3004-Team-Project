#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "session.h"
#include <QMainWindow>
#include <QTimer>
#include <QLabel>
#include <QVector>
#include <QtMultimedia>
#include <QSystemTrayIcon>
#include <QWidget>
#include <QMediaPlayer>


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
    void on_startStopSessionButton_clicked();
    void updateTime(int);
    void updateGraphData(QCPDataContainer<QCPGraphData>);
    void updateCoherence(float, float);

private:
    Ui::MainWindow *ui;
    list<Session*> sessionLog;

};
#endif // MAINWINDOW_H
