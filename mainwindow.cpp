#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWidget->setVisible(false);
    ui->radioButton_SideX->setVisible(false);
    ui->radioButton_SideY->setVisible(false);
    ui->radioButton_Side_X->setVisible(false);
    ui->radioButton_Side_Y->setVisible(false);
    ui->label_4->setVisible(false);
    ui->label_5->setVisible(false);
    ui->label_6->setVisible(false);
    ui->label_7->setVisible(false);
    ui->activationSignals_table->setVisible(false);
    ui->activeLabels_list->setVisible(false);
    ui->transmissionSignals_table->setVisible(false);
    ui->inactiveLabels_list->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_Simulation_triggered()
{
    qDebug()<<"New button was pressed";
    this->currentTile = 0;
    ui->tabWidget->setVisible(true);
    ui->radioButton_SideX->setChecked(true);
    ui->radioButton_SideX->setVisible(true);
    ui->radioButton_SideY->setVisible(true);
    ui->radioButton_Side_X->setVisible(true);
    ui->radioButton_Side_Y->setVisible(true);
    ui->label_4->setVisible(true);
    ui->label_5->setVisible(true);
    ui->label_6->setVisible(true);
    ui->label_7->setVisible(true);
    ui->activationSignals_table->setVisible(true);
    ui->activeLabels_list->setVisible(true);
    ui->transmissionSignals_table->setVisible(true);
    ui->inactiveLabels_list->setVisible(true);
}



void MainWindow::on_NewTileButton_clicked()
{
    qDebug()<<"New Tile Button pressed";
    ui->listWidget->addItem(QString("Tile ") + QString::number(this->currentTile));
    (this->currentTile)++;
}

void MainWindow::on_DeleteTileButton_clicked()
{
    qDebug()<<"Delete Tile Button Pressed";

}

void MainWindow::on_BeginSim_Button_clicked()
{

}
