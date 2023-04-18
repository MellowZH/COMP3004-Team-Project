#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
//new stuff for graph
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
    void updatetime();
    void startNewSession();
    void updateGraphData();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    int elapsedSeconds;

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
