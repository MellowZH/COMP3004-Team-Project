#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QStackedWidget>
#include <QCheckBox>
#include <QTimer>
#include <QDebug>
#include <QFile>
#include <ctime>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer(this);
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

//makes it so that when the select button is started the timer activates and numbers start changing
void MainWindow::on_Selectbuttonsession_clicked()
{

    ui->activesession->toggle();
//    HrvGraph = ui->hrvGraph
    if(ui->activesession->isChecked()==false){
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


