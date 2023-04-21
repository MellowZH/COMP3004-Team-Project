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
    void on_backButton_clicked();
    void on_downArrowButton_clicked();
    void on_upArrowButton_clicked();
    void on_startStopSessionButton_clicked();
    void on_hrContact_stateChanged();
    void loadSessionHistory();
    void loadSessionSummary();
    void updateTime(int);
    void updateGraphData(QCPDataContainer<QCPGraphData>);
    void updateCoherence(float, float);
    void on_resetHistory_clicked();
    QString formatTime(int);
    void batteryDrain();

private:
    Ui::MainWindow *ui;
    list<Session*> sessionLog;
    int selectedOption;

};
#endif // MAINWINDOW_H
