#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QStackedWidget>
#include <QCheckBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
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


