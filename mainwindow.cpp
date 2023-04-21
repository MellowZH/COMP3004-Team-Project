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
    QTimer *batteryTimer = new QTimer;
    connect(batteryTimer, &QTimer::timeout, this, [this]{batteryDrain();});
    batteryTimer->start(10000); //drain 1% every 10 sec

    //initialize graphs
    ui->hrvGraph->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    ui->hrvGraph->xAxis->setLabel("Time");
    ui->hrvGraph->yAxis->setLabel("HeartRate");

    ui->hrvGraph->addGraph();
    ui->hrvGraph->graph(0)->setPen(QPen(Qt::blue));
    ui->hrvGraph->graph(0)->setBrush(QBrush(QColor(0,0,255,20)));
    ui->hrvGraph->xAxis2->setVisible(true);
    ui->hrvGraph->xAxis2->setTickLabels(false);
    ui->hrvGraph->yAxis2->setVisible(true);
    ui->hrvGraph->yAxis2->setTickLabels(false);
    connect(ui->hrvGraph->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->hrvGraph->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->hrvGraph->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->hrvGraph->yAxis2, SLOT(setRange(QCPRange)));
    ui->hrvGraph->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    ui->summaryHrvGraph->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    ui->summaryHrvGraph->xAxis->setLabel("Time");
    ui->summaryHrvGraph->yAxis->setLabel("HeartRate");
    ui->summaryHrvGraph->addGraph();
    ui->summaryHrvGraph->graph(0)->setPen(QPen(Qt::blue));
    ui->summaryHrvGraph->graph(0)->setBrush(QBrush(QColor(0,0,255,20)));
    ui->summaryHrvGraph->xAxis2->setVisible(true);
    ui->summaryHrvGraph->xAxis2->setTickLabels(false);
    ui->summaryHrvGraph->yAxis2->setVisible(true);
    ui->summaryHrvGraph->yAxis2->setTickLabels(false);
    connect(ui->summaryHrvGraph->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->summaryHrvGraph->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->summaryHrvGraph->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->summaryHrvGraph->yAxis2, SLOT(setRange(QCPRange)));
    ui->summaryHrvGraph->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    srand(time(0)); //seed random number generator
}

MainWindow::~MainWindow()
{
    delete ui;
}

//Starts or stops a session
void MainWindow::on_startStopSessionButton_clicked()
{
    switch (ui->stackedWidget->currentIndex()){
        case 0: //Active session screen
            if(sessionLog.empty() || !sessionLog.front()->isActive()){
                cout<<"Starting new Session"<<endl;
                Session *newSession = new Session(ui->challengeLevelValue->value());
                sessionLog.push_front(newSession); //List will be sorted with most recent session at the front of the list
                connect(newSession, SIGNAL(timeUpdated(int)),this, SLOT(updateTime(int)));
                connect(newSession, SIGNAL(graphUpdated(QCPDataContainer<QCPGraphData>)), this, SLOT(updateGraphData(QCPDataContainer<QCPGraphData>)));
                connect(newSession, SIGNAL(coherenceUpdated(float,float)), this, SLOT(updateCoherence(float,float)));
                newSession->startSession();
            }
            else{
                sessionLog.front()->stopSession();
                selectedOption=0;
                ui->stackedWidget->setCurrentIndex(1);
                loadSessionSummary();
            }
            break;
        case 1: //Session summary
            break;
        case 2: //Menu page
            switch (selectedOption){
                case 0:
                    ui->stackedWidget->setCurrentIndex(3); //go to session history page
                    loadSessionHistory();
                    break;
                case 1:
                    ui->stackedWidget->setCurrentIndex(4); //go to settings page
                    break;
            }
            break;
        case 3: //Select session
            ui->stackedWidget->setCurrentIndex(1);
            loadSessionSummary();

            //make top item in session history selected again
            qobject_cast<QPushButton*>(ui->sessionHistoryDisplay->itemAt(selectedOption)->widget())->setStyleSheet("border:0.5px solid;color: rgb(0, 0, 0); background-color: rgb(255, 255, 255)"); //only top option should be selected
            qobject_cast<QPushButton*>(ui->sessionHistoryDisplay->itemAt(0)->widget())->setStyleSheet("background: qradialgradient(cx: 0.4, cy: -0.1, fx: 0.4, fy: -0.1,radius: 1.35, stop: 0 #0055ff, stop: 1 #00aaff); border: 2px solid #0055ff; color: rgb(0, 0, 0);");

            break;
        case 4:
            break; //Settings
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

//move between pages/screens button commands
void MainWindow::on_Menubuttonsession_clicked()
{
    //makes it so when the menu button in the session page is clicked it moves to the menu page
    ui->stackedWidget->setCurrentIndex(2);
    selectedOption = 0;
}

void MainWindow::on_backButton_clicked()
{
    //go back to previous page
    switch (ui->stackedWidget->currentIndex()){
        case 0: //Active session screen
            break;
        case 1: //Session summary
            ui->stackedWidget->setCurrentIndex(0);
        case 2: //Menu page
            ui->stackedWidget->setCurrentIndex(0);
            break;
        case 3: //Session history
            ui->stackedWidget->setCurrentIndex(2); //return to menu page
            selectedOption = 0;
            break;
        case 4: //Settings page
            ui->stackedWidget->setCurrentIndex(2); //return to menu page
            selectedOption = 0;
            break;
    }
}

//sets up the buttons for menu
void MainWindow::on_downArrowButton_clicked(){
    switch (ui->stackedWidget->currentIndex()){
        case 2:
            ui->settingsButton->setStyleSheet("background: qradialgradient(cx: 0.4, cy: -0.1, fx: 0.4, fy: -0.1,radius: 1.35, stop: 0 #0055ff, stop: 1 #00aaff); border: 2px solid #0055ff; color: rgb(0, 0, 0);");
            ui->sessionHistoryButton->setStyleSheet("border:0.5px solid;color: rgb(0, 0, 0); background-color: rgb(255, 255, 255)");
            this->selectedOption = 1;
            break;
        case 3:
            cout<<selectedOption<<endl;
            cout<<ui->sessionHistoryDisplay->count()<<endl;
            if(selectedOption != int(sessionLog.size()) -1){
                if(ui->sessionHistoryDisplay->itemAt(selectedOption)){
                    cout<<"found"<<endl;
                }
                QPushButton *oldOption= qobject_cast<QPushButton*>(ui->sessionHistoryDisplay->itemAt(selectedOption)->widget());
                selectedOption ++;
                QPushButton *newOption= qobject_cast<QPushButton*>(ui->sessionHistoryDisplay->itemAt(selectedOption)->widget());
                if(oldOption){
                    oldOption->setStyleSheet("border:0.5px solid;color: rgb(0, 0, 0); background-color: rgb(255, 255, 255)");
                }
                if(newOption){
                    newOption->setStyleSheet("background: qradialgradient(cx: 0.4, cy: -0.1, fx: 0.4, fy: -0.1,radius: 1.35, stop: 0 #0055ff, stop: 1 #00aaff); border: 2px solid #0055ff; color: rgb(0, 0, 0);");
                }
            }
            break;
    }

}

void MainWindow::on_upArrowButton_clicked(){
    switch (ui->stackedWidget->currentIndex()){
        case 2:
            ui->sessionHistoryButton->setStyleSheet("background: qradialgradient(cx: 0.4, cy: -0.1, fx: 0.4, fy: -0.1,radius: 1.35, stop: 0 #0055ff, stop: 1 #00aaff); border: 2px solid #0055ff; color: rgb(0, 0, 0);");
            ui->settingsButton->setStyleSheet("border:0.5px solid;color: rgb(0, 0, 0); background-color: rgb(255, 255, 255)");
            this->selectedOption=0;
            break;
        case 3:
            cout<<selectedOption<<endl;
            cout<<ui->sessionHistoryDisplay->count()<<endl;
            if(selectedOption >0){
                QPushButton *oldOption= qobject_cast<QPushButton*>(ui->sessionHistoryDisplay->itemAt(selectedOption)->widget());
                selectedOption --;
                QPushButton *newOption= qobject_cast<QPushButton*>(ui->sessionHistoryDisplay->itemAt(selectedOption)->widget());
                if(oldOption){
                    oldOption->setStyleSheet("border:0.5px solid;color: rgb(0, 0, 0); background-color: rgb(255, 255, 255)");
                }
                if(newOption){
                    newOption->setStyleSheet("background: qradialgradient(cx: 0.4, cy: -0.1, fx: 0.4, fy: -0.1,radius: 1.35, stop: 0 #0055ff, stop: 1 #00aaff); border: 2px solid #0055ff; color: rgb(0, 0, 0);");
                }
            }
            break;
    }

}

void MainWindow::on_hrContact_stateChanged() {
    sessionLog.front()->setHrvContact();
}

//Create Ui with previous sessions
void MainWindow::loadSessionHistory(){
    selectedOption =0;
    static int counter = 0;
    list<Session*>::iterator it =sessionLog.begin();
    advance(it, counter);

    //generate entry for each session
    while(counter<int(sessionLog.size())){ //dont generate if a button has already been created for the session
        auto newSession = new QPushButton();
        newSession->setText(QString::fromStdString((*it)->getSessionData().getDate()));
        newSession->setDisabled(true);
        newSession->setStyleSheet("background: qradialgradient(cx: 0.4, cy: -0.1, fx: 0.4, fy: -0.1,radius: 1.35, stop: 0 #0055ff, stop: 1 #00aaff); border: 2px solid #0055ff; color: rgb(0, 0, 0);");
        if(counter>0){
            qobject_cast<QPushButton*>(ui->sessionHistoryDisplay->itemAt(0)->widget())->setStyleSheet("border:0.5px solid;color: rgb(0, 0, 0); background-color: rgb(255, 255, 255)"); //only top option should be selected
        }
        ui->sessionHistoryDisplay->insertWidget(0, newSession);
        advance(it, 1);
        counter++;
    }
}

void MainWindow::loadSessionSummary(){
    list<Session*>::iterator it =sessionLog.begin();
    advance(it, selectedOption);
    ui->summaryAvgCoherenceValue->setText(QString::number((*it)->getSessionData().getAvgCoherence()));
    ui->summaryChallengeLevelValue->setText(QString::number((*it)->getSessionData().getChallengeLevel()));
    ui->summaryLengthValue->setText(formatTime((*it)->getSessionData().getSessionLength()));
    ui->summaryAchievementValue->setText(QString::number((*it)->getSessionData().getAchievementScore()));
    ui->summaryTimeInLowCoherenceValue->setText(formatTime((*it)->getSessionData().getTimeInLowCoherence()));
    ui->summaryTimeInMedCoherenceValue->setText(formatTime((*it)->getSessionData().getTimeInMedCoherence()));
    ui->summaryTimeInHighCoherenceValue->setText(formatTime((*it)->getSessionData().getTimeInHighCoherence()));
    ui->summaryHrvGraph->graph(0)->data()->set((*it)->getSessionData().getHrvData());
    ui->summaryHrvGraph->replot();
    ui->summaryHrvGraph->graph(0)->rescaleAxes();

}

//updates the time
void MainWindow::updateTime(int elapsedSeconds){
    ui->lengthValue->setText(formatTime(elapsedSeconds));
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

void MainWindow::on_resetHistory_clicked(){
   //sessionLog.clear();
   //@TODO CLEAR BUTTONS FROM SESSION HISTORY
}

QString MainWindow::formatTime(int elapsedSeconds){
    int hours = elapsedSeconds/3600;
    int mins = (elapsedSeconds/60)%60;
    int sec = elapsedSeconds % 60;
    QString stopWatch = QString("%1:%2:%3")
            .arg(hours, 2, 10, QLatin1Char('0'))
            .arg(mins, 2, 10, QLatin1Char('0'))
            .arg(sec, 2, 10, QLatin1Char('0'));
    return stopWatch;
}

void MainWindow::batteryDrain(){
    ui->batteryValue->display(ui->batteryValue->intValue()-1);
}

