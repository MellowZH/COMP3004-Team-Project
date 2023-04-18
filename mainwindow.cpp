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


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updatetime);
    elapsedSeconds = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

//updates the time
void MainWindow::updatetime(){
    elapsedSeconds++;
    int hours = elapsedSeconds/3600;
    int mins = (elapsedSeconds/60)%60;
    int sec = elapsedSeconds % 60;
    QString stopWatch = QString("%1:%2:%3")
            .arg(hours, 2, 10, QLatin1Char('0'))
            .arg(mins, 2, 10, QLatin1Char('0'))
            .arg(sec, 2, 10, QLatin1Char('0'));
    ui->lengthValue->setText(stopWatch);
}
//starts new session
void MainWindow::startNewSession()
{
    ui->hrvGraph->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    ui->hrvGraph->xAxis->setLabel("Time");
    ui->hrvGraph->yAxis->setLabel("HeartRate");

    //adds a new graph
    ui->hrvGraph->addGraph();
    ui->hrvGraph->graph(0)->setPen(QPen(Qt::blue));
    ui->hrvGraph->graph(0)->setBrush(QBrush(QColor(0,0,255,20)));
    ui->hrvGraph->addGraph();
    ui->hrvGraph->graph(1)->setPen(QPen(Qt::red));
    //generates points of data
    QVector<double> x(251), y0(251), y1(251);
    for (int i=0; i<251; ++i){
        x[i] = i;
        y0[i] = exp(-i/150.0)*qCos(i/10.0);
        y1[i] = exp(-i/150.0);
    }
    ui->hrvGraph->xAxis2->setVisible(true);
    ui->hrvGraph->xAxis2->setTickLabels(false);
    ui->hrvGraph->yAxis2->setVisible(true);
    ui->hrvGraph->yAxis2->setTickLabels(false);

    //makes it so that the left and bottom axes are always transfering their ranges to the right and top axes
    connect(ui->hrvGraph->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->hrvGraph->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->hrvGraph->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->hrvGraph->yAxis2, SLOT(setRange(QCPRange)));

    ui->hrvGraph->graph(0)->setData(x, y0);
    ui->hrvGraph->graph(1)->setData(x, y1);

    ui->hrvGraph->graph(0)->rescaleAxes();
    ui->hrvGraph->graph(1)->rescaleAxes();

    ui->hrvGraph->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
}
//updates the graph data
void MainWindow::updateGraphData(){
    //gens some new HR values
    int graphoffset=0;
    QVector<double> x(251), y(251);
    for (int i=0; i<251; ++i){
        x[i]= i;
        y[i]= exp(-i/150.0)*qCos((i+graphoffset)/10);
        y[i] += exp(-(i+10)/150.0);
    }
    ui->hrvGraph->graph(0)->setData(x, y);
    graphoffset += 1;
    ui->hrvGraph->rescaleAxes();
}
//makes it so that when the select button is started the timer activates and numbers start changing
void MainWindow::on_Selectbuttonsession_clicked()
{

    ui->activesession->toggle();

    if(ui->activesession->isChecked()==true){
        updatetime();
        startNewSession();
        timer->start(1000);
        QCPGraph *graph = ui->hrvGraph->graph(0);
//        QSharedPointer<QCPGraphDataContainer> dataContainter= graph->data();
//        QCPGraphDataContainer *data = dataContainer.data();
//        QVector<QCPGraphData> graphData;
//        for (int i=0; i <data->size(); i++){
//            graphData.append(*(data->at(i)));
//        }
    }
    if(ui->activesession->isChecked()==false){
        if (timer->isActive()){
            timer->stop();
        }
        QString filename= "logsoflatestsession.txt" ;
        QFile file(filename);
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream out(&file);
        out << "here is the data: \nCoherence values: " << ui->coherenceValue->text() << "\nLength of Session: " << ui->lengthValue->text() << "\nAchivement Value: " << ui->achievementValue->text() << endl;
        file.close();
    }
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


