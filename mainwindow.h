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
    void on_Selectbuttonsession_clicked();
    void updateTime(int);
    void startNewSession();
    void updateGraphData();

    void on_choice1_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;
    list<Session*> sessionLog;

    QVector<double> getHRVData(){
        QVector<double> hrvData;
        for (int i=0; i<100; ++i){
            hrvData.append(rand()%50+50);
        }
        return hrvData;
    }
    QVector<double> getTimeData(const QVector<double>& data, int sampleRate){
        QVector<double> timeData;
        for (int i = 0; i<data.size(); ++i){
            timeData.append(static_cast<double>(i)/sampleRate);
        }
        return timeData;
    }

};
#endif // MAINWINDOW_H
