#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QStackedWidget>
#include <QCheckBox>
#include <QTimer>
#include <QDebug>
#include <QFile>
#include <ctime>
#include <QTextStream>
#include <QLabel>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QtWidgets>
#include <QtCore/QThread>
#include <QtCore/QFuture>
#include <QVector>
#include <QSystemTrayIcon>
#include <QProcess>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QtMultimedia>
#include <QTimer>
#include <iostream>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->hrvGraph->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    ui->hrvGraph->xAxis->setLabel("Time");
    ui->hrvGraph->yAxis->setLabel("HeartRate");

    //adds a new graph
    ui->hrvGraph->addGraph();
    ui->hrvGraph->graph(0)->setPen(QPen(Qt::blue));
    ui->hrvGraph->graph(0)->setBrush(QBrush(QColor(0,0,255,20)));
    ui->hrvGraph->addGraph();
    ui->hrvGraph->xAxis2->setVisible(true);
    ui->hrvGraph->xAxis2->setTickLabels(false);
    ui->hrvGraph->yAxis2->setVisible(true);
    ui->hrvGraph->yAxis2->setTickLabels(false);
    connect(ui->hrvGraph->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->hrvGraph->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->hrvGraph->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->hrvGraph->yAxis2, SLOT(setRange(QCPRange)));
    ui->hrvGraph->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    srand(time(0)); //seed random number generator
}

MainWindow::~MainWindow()
{
    delete ui;
}

//Starts or stops a session
void MainWindow::on_startStopSessionButton_clicked()
{
    if(sessionLog.empty() || !sessionLog.front()->isActive()){
        cout<<"Starting new Session"<<endl;
        Session *newSession = new Session();
        sessionLog.push_front(newSession); //List will be sorted with most recent session at the front of the list
        connect(newSession, SIGNAL(timeUpdated(int)),this, SLOT(updateTime(int)));
        connect(newSession, SIGNAL(graphUpdated(QCPDataContainer<QCPGraphData>)), this, SLOT(updateGraphData(QCPDataContainer<QCPGraphData>)));
        connect(newSession, SIGNAL(coherenceUpdated(float,float)), this, SLOT(updateCoherence(float,float)));
        newSession->startSession();
    }
    else{
        sessionLog.front()->stopSession();
    }
//    if(ui->activesession->isChecked()==false){
    //        if (timer->isActive()){
    //            timer->stop();
    //        }
    //        QString filename= "logsoflatestsession.txt" ;
    //        QFile file(filename);
    //        file.open(QIODevice::WriteOnly | QIODevice::Text);
    //        QTextStream out(&file);
    //        out << "here is the data: \nCoherence values: " << ui->coherenceValue->text() << "\nLength of Session: " << ui->lengthValue->text() << "\nAchivement Value: " << ui->achievementValue->text() << endl;
    //        file.close();
    //    }
   }

//updates the time
void MainWindow::updateTime(int elapsedSeconds){
    int hours = elapsedSeconds/3600;
    int mins = (elapsedSeconds/60)%60;
    int sec = elapsedSeconds % 60;
    QString stopWatch = QString("%1:%2:%3")
            .arg(hours, 2, 10, QLatin1Char('0'))
            .arg(mins, 2, 10, QLatin1Char('0'))
            .arg(sec, 2, 10, QLatin1Char('0'));
    ui->lengthValue->setText(stopWatch);
}

//updates the graph data
void MainWindow::updateGraphData(QCPDataContainer<QCPGraphData> hrvData){
    ui->hrvGraph->graph(0)->data()->set(hrvData);
    ui->hrvGraph->replot();
    ui->hrvGraph->graph(0)->rescaleAxes();
}

//updates coherenceScore and achievementScore
void MainWindow::updateCoherence(float coherenceScore, float achievementScore){
    ui->coherenceValue->setText(QString::number(coherenceScore));
    ui->achievementValue->setText(QString::number(achievementScore));
}

//move between pages/screens button commands
void MainWindow::on_Menubuttonsession_clicked()
{
    //makes it so when the menu button in the session page is clicked it moves to the menu page
    ui->stackedWidget->setCurrentIndex(1);
    ui->choice1->toggle();
    ui->choice2->toggle();
    ui->choice3->toggle();
}

void MainWindow::on_Backbuttonmenu_clicked()
{
    //makes it so when the back button in menu page is clicked it moves back to the session page
    ui->stackedWidget->setCurrentIndex(0);
}

//sets up the buttons for menu
void MainWindow::on_Downarrowmenu_clicked()
{
    if (ui->choice1->isChecked()==true && ui->choice2->isChecked()==true && ui->choice3->isChecked()==true){
        ui->choice1->toggle();
    }
    else if (ui->choice1->isChecked()==false && ui->choice3->isChecked()==true){
        ui->choice2->toggle();
        ui->choice1->toggle();
    }
    else if (ui->choice2->isChecked()==false && ui->choice1->isChecked()==true){
        ui->choice2->toggle();
        ui->choice3->toggle();
    }
}

void MainWindow :: on_Uparrowmenu_clicked(){
    if (ui->choice2->isChecked()==true && ui->choice1->isChecked()==true){
        ui->choice3->toggle();
        ui->choice2->toggle();
    }
    else if (ui->choice3->isChecked()==true && ui->choice2->isChecked()==false){
        ui->choice2->toggle();
        ui->choice1->toggle();
    }
}


