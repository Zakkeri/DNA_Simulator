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
    ui->activeLabels_listWidget->setVisible(false);
    ui->transmissionSignals_table->setVisible(false);
    ui->inactiveLabels_listWidget->setVisible(false);
    ui->activeLabel_Add_pushButton->setVisible(false);
    ui->activeLabel_Remove_pushButton->setVisible(false);
    ui->inactiveLabel_Add_pushButton->setVisible(false);
    ui->inactiveLabel_Remove_pushButton->setVisible(false);
    ui->activationSig_Add_pushButton->setVisible(false);
    ui->activationSig_Remove_pushButton->setVisible(false);
    ui->transmissionSig_Add_pushButton->setVisible(false);
    ui->transmissionSig_Remove_pushButton->setVisible(false);

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
    ui->activeLabels_listWidget->setVisible(true);
    ui->transmissionSignals_table->setVisible(true);
    ui->inactiveLabels_listWidget->setVisible(true);
    ui->activeLabel_Add_pushButton->setVisible(true);
    ui->activeLabel_Remove_pushButton->setVisible(true);
    ui->inactiveLabel_Add_pushButton->setVisible(true);
    ui->inactiveLabel_Remove_pushButton->setVisible(true);
    ui->activationSig_Add_pushButton->setVisible(true);
    ui->activationSig_Remove_pushButton->setVisible(true);
    ui->transmissionSig_Add_pushButton->setVisible(true);
    ui->transmissionSig_Remove_pushButton->setVisible(true);


}



void MainWindow::on_NewTileButton_clicked()
{
    qDebug()<<"New Tile Button pressed";

    /*QListWidgetItem item("Tile " + QString::number(this->currentTile));
    item.setFlags(item.flags() | Qt::ItemIsEditable);*/

    ui->listWidget->addItem(QString("Tile ") + QString::number(this->currentTile)); //add tile to the list

    ui->tile_comboBox->addItem(QString("Tile ") + QString::number(this->currentTile));  //add tile to the combo box

    (this->currentTile)++;  //increase counter


}

void MainWindow::on_DeleteTileButton_clicked()
{
    qDebug()<<"Delete Tile Button Pressed";
    if(ui->listWidget->currentItem() == 0)  //check if tile exist
    {
        qDebug()<<"No item was selected\n";
    }
    else    //if it does
    {
        qDebug()<<"Selected item: "<<ui->listWidget->currentItem()->text()<<"\n";

        ui->tile_comboBox->removeItem(ui->listWidget->currentRow());    //remove item from the combo box

        delete ui->listWidget->takeItem(ui->listWidget->currentRow());   //delete it from the list

    }

}

void MainWindow::on_BeginSim_Button_clicked()
{

}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    switch(index)
    {
    case 0:
        qDebug()<<"Index = 0\n";
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
        ui->activeLabels_listWidget->setVisible(true);
        ui->transmissionSignals_table->setVisible(true);
        ui->inactiveLabels_listWidget->setVisible(true);
        ui->activeLabel_Add_pushButton->setVisible(true);
        ui->activeLabel_Remove_pushButton->setVisible(true);
        ui->inactiveLabel_Add_pushButton->setVisible(true);
        ui->inactiveLabel_Remove_pushButton->setVisible(true);
        ui->activationSig_Add_pushButton->setVisible(true);
        ui->activationSig_Remove_pushButton->setVisible(true);
        ui->transmissionSig_Add_pushButton->setVisible(true);
        ui->transmissionSig_Remove_pushButton->setVisible(true);
        break;
    case 1:
        qDebug()<<"Index = 1\n";
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
        ui->activeLabels_listWidget->setVisible(true);
        ui->transmissionSignals_table->setVisible(true);
        ui->inactiveLabels_listWidget->setVisible(true);
        ui->activeLabel_Add_pushButton->setVisible(true);
        ui->activeLabel_Remove_pushButton->setVisible(true);
        ui->inactiveLabel_Add_pushButton->setVisible(true);
        ui->inactiveLabel_Remove_pushButton->setVisible(true);
        ui->activationSig_Add_pushButton->setVisible(true);
        ui->activationSig_Remove_pushButton->setVisible(true);
        ui->transmissionSig_Add_pushButton->setVisible(true);
        ui->transmissionSig_Remove_pushButton->setVisible(true);
        break;
    case 2:
        qDebug()<<"Index = 2\n";
        ui->radioButton_SideX->setVisible(false);
        ui->radioButton_SideY->setVisible(false);
        ui->radioButton_Side_X->setVisible(false);
        ui->radioButton_Side_Y->setVisible(false);
        ui->label_4->setVisible(false);
        ui->label_5->setVisible(false);
        ui->label_6->setVisible(false);
        ui->label_7->setVisible(false);
        ui->activationSignals_table->setVisible(false);
        ui->activeLabels_listWidget->setVisible(false);
        ui->transmissionSignals_table->setVisible(false);
        ui->inactiveLabels_listWidget->setVisible(false);
        ui->activeLabel_Add_pushButton->setVisible(false);
        ui->activeLabel_Remove_pushButton->setVisible(false);
        ui->inactiveLabel_Add_pushButton->setVisible(false);
        ui->inactiveLabel_Remove_pushButton->setVisible(false);
        ui->activationSig_Add_pushButton->setVisible(false);
        ui->activationSig_Remove_pushButton->setVisible(false);
        ui->transmissionSig_Add_pushButton->setVisible(false);
        ui->transmissionSig_Remove_pushButton->setVisible(false);
        break;
    case 3:
        qDebug()<<"Index = 3\n";
        ui->radioButton_SideX->setVisible(false);
        ui->radioButton_SideY->setVisible(false);
        ui->radioButton_Side_X->setVisible(false);
        ui->radioButton_Side_Y->setVisible(false);
        ui->label_4->setVisible(false);
        ui->label_5->setVisible(false);
        ui->label_6->setVisible(false);
        ui->label_7->setVisible(false);
        ui->activationSignals_table->setVisible(false);
        ui->activeLabels_listWidget->setVisible(false);
        ui->transmissionSignals_table->setVisible(false);
        ui->inactiveLabels_listWidget->setVisible(false);
        ui->activeLabel_Add_pushButton->setVisible(false);
        ui->activeLabel_Remove_pushButton->setVisible(false);
        ui->inactiveLabel_Add_pushButton->setVisible(false);
        ui->inactiveLabel_Remove_pushButton->setVisible(false);
        ui->activationSig_Add_pushButton->setVisible(false);
        ui->activationSig_Remove_pushButton->setVisible(false);
        ui->transmissionSig_Add_pushButton->setVisible(false);
        ui->transmissionSig_Remove_pushButton->setVisible(false);
        break;
    case 4:
        qDebug()<<"Index = 4\n";
        ui->radioButton_SideX->setVisible(false);
        ui->radioButton_SideY->setVisible(false);
        ui->radioButton_Side_X->setVisible(false);
        ui->radioButton_Side_Y->setVisible(false);
        ui->label_4->setVisible(false);
        ui->label_5->setVisible(false);
        ui->label_6->setVisible(false);
        ui->label_7->setVisible(false);
        ui->activationSignals_table->setVisible(false);
        ui->activeLabels_listWidget->setVisible(false);
        ui->transmissionSignals_table->setVisible(false);
        ui->inactiveLabels_listWidget->setVisible(false);
        ui->activeLabel_Add_pushButton->setVisible(false);
        ui->activeLabel_Remove_pushButton->setVisible(false);
        ui->inactiveLabel_Add_pushButton->setVisible(false);
        ui->inactiveLabel_Remove_pushButton->setVisible(false);
        ui->activationSig_Add_pushButton->setVisible(false);
        ui->activationSig_Remove_pushButton->setVisible(false);
        ui->transmissionSig_Add_pushButton->setVisible(false);
        ui->transmissionSig_Remove_pushButton->setVisible(false);
        break;
    default:
        qDebug()<<"default: Index = "<<index<<"\n";
        break;
    }
}
