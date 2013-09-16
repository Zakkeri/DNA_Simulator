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
    ui->graphicsView->setVisible(false);

    //ui->graphicsView->setScene(new QGraphicsScene());

    ui->radioButton_SideX->setChecked(true);
    currentSide = 0;
    selectedTile = 0;
    /*QPainter paint(ui->graphicsView);

    paint.setPen(QPen(Qt::black, 4, Qt::SolidLine));
    paint.drawLine(0,0,10,10);
*/

}

MainWindow::~MainWindow()
{
    QObject::disconnect(ui->listWidget, SIGNAL(currentRowChanged(int )), this, SLOT(on_listWidget_currentRowChanged(int)));

    for(QList<a_tile *>::iterator iter = tiles.begin(); iter != tiles.end(); ++iter)
    {
        delete (*iter);
    }
    delete ui;
}

void MainWindow::paintCurrentTile()
{
    if(selectedTile == 0) return;
    DisplayTile tilePainting(10, 10, 100);
    for(int i = 0; i < 4; i++)
    {
        for(QList<QListWidgetItem *>::const_iterator iter = selectedTile->activeLabels[i].begin();
            iter != selectedTile->activeLabels[i].end(); iter++)
        {
            tilePainting.addLabel(DisplayLabel(i, QColor(255, 0, 0), true));
        }

        for(QList<QListWidgetItem *>::const_iterator iter = selectedTile->inactiveLabels[i].begin();
            iter != selectedTile->inactiveLabels[i].end(); iter++)
        {
            tilePainting.addLabel(DisplayLabel(i, QColor(0, 0, 255), false));
        }
    }

    QPainter painter(ui->graphicsView);
    /*if(painter.begin(ui->graphicsView) == false)
    {
        qDebug()<<"Painter can't paint on the current device";
        return;
    }*/
    tilePainting.drawTile(painter);


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

void MainWindow::updateEntries(short side)
{
    if(selectedTile == 0) return;
    //Clear all lists/tables

    for(int i = ui->activeLabels_listWidget->count() - 1; i >=0; i--)
    {
        ui->activeLabels_listWidget->takeItem(i);
    }

    for(int i = ui->inactiveLabels_listWidget->count() - 1; i >=0; i--)
    {
        ui->inactiveLabels_listWidget->takeItem(i);
    }

    for(int i = ui->activationSignals_table->rowCount() - 1; i >=0; i--)
    {
        ui->activationSignals_table->takeItem(i, 0);
        ui->activationSignals_table->takeItem(i, 1);

        ui->activationSignals_table->removeRow(i);
    }

    for(int i = ui->transmissionSignals_table->rowCount() - 1; i >=0; i--)
    {
        ui->transmissionSignals_table->takeItem(i, 0);
        ui->transmissionSignals_table->takeItem(i, 1);
        ui->transmissionSignals_table->removeRow(i);
    }

    for(int i = ui->initiation_signals_tableWidget->rowCount() - 1; i >=0; i--)
    {
        ui->initiation_signals_tableWidget->takeItem(i, 0);
        ui->initiation_signals_tableWidget->takeItem(i, 1);
        ui->initiation_signals_tableWidget->removeRow(i);
    }

    //Insert values from current tile
    for(QList<QListWidgetItem *>::const_iterator iter = selectedTile->activeLabels[side].begin();
        iter != selectedTile->activeLabels[side].end(); iter++)
    {
        ui->activeLabels_listWidget->addItem(*iter);
    }

    for(QList<QListWidgetItem *>::const_iterator iter = selectedTile->inactiveLabels[side].begin();
        iter != selectedTile->inactiveLabels[side].end(); iter++)
    {
        ui->inactiveLabels_listWidget->addItem(*iter);
    }

    for(QList<tablePair *>::const_iterator iter = selectedTile->activationSignals[side].begin();
        iter != selectedTile->activationSignals[side].end(); iter++)
    {
        ui->activationSignals_table->insertRow(ui->activationSignals_table->rowCount());//insert row
        //set items
        ui->activationSignals_table->setItem(ui->activationSignals_table->rowCount() - 1, 0, (*iter)->first);
        ui->activationSignals_table->setCellWidget(ui->activationSignals_table->rowCount() - 1, 1, (*iter)->second);
    }

    for(QList<QPair<QTableWidgetItem  *, QTableWidgetItem  *> >::const_iterator iter = selectedTile->transmissionSignals[side].begin();
        iter != selectedTile->transmissionSignals[side].end(); iter++)
    {
        ui->transmissionSignals_table->insertRow(ui->transmissionSignals_table->rowCount());//insert row
        //set items
        ui->transmissionSignals_table->setItem(ui->transmissionSignals_table->rowCount() - 1, 0, (*iter).first);
        ui->transmissionSignals_table->setItem(ui->transmissionSignals_table->rowCount() - 1, 1, (*iter).second);
    }

    for(QList<QPair<QTableWidgetItem  *, QTableWidgetItem  *> >::const_iterator iter = selectedTile->initiationSignals.begin();
        iter != selectedTile->initiationSignals.end(); iter++)
    {
        ui->initiation_signals_tableWidget->insertRow(ui->initiation_signals_tableWidget->rowCount());//insert row
        //set items
        ui->initiation_signals_tableWidget->setItem(ui->initiation_signals_tableWidget->rowCount() - 1, 0, (*iter).first);
        ui->initiation_signals_tableWidget->setItem(ui->initiation_signals_tableWidget->rowCount() - 1, 1, (*iter).second);
    }
}

void MainWindow::on_NewTileButton_clicked()
{
    qDebug()<<"New Tile Button pressed";

    /*QListWidgetItem item("Tile " + QString::number(this->currentTile));
    item.setFlags(item.flags() | Qt::ItemIsEditable);*/
    tiles.append(new a_tile(QString("Tile ") + QString::number(this->currentTile)));
    tiles.last()->Tile->setFlags(tiles.last()->Tile->flags() | Qt::ItemIsEditable);
    ui->listWidget->addItem(tiles.last()->Tile); //add tile to the list

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
        int row = ui->listWidget->currentRow();
        a_tile * toRemove = tiles.at(row); //get pointer to the item to remove
        tiles.removeOne(toRemove);  //remove item from the list of tiles
        ui->tile_comboBox->removeItem(row);    //remove item from the combo box
        ui->listWidget->takeItem(row);   //delete it from the list widget
        delete toRemove;  //remove item

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

        ui->graphicsView->setVisible(false);
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

        ui->graphicsView->setVisible(false);
        break;
    case 2:
        qDebug()<<"Index = 2\n";
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


        ui->graphicsView->setVisible(false);
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

        ui->graphicsView->setVisible(true); //show graphics
        //Paint tile
        this->paintCurrentTile();
        break;

    default:
        qDebug()<<"default: Index = "<<index<<"\n";
        break;
    }
}

void MainWindow::on_listWidget_clicked(const QModelIndex &index)
{
    qDebug()<<"Row clicked: "<<index.row();
    if(index.row() < 0) return;
    int currentRow = index.row();
    ui->tile_comboBox->setCurrentIndex(currentRow); //update combobox
    selectedTile = tiles.at(currentRow);    //update selectedTile value
    ui->radioButton_SideX->setChecked(true);    //select side X by default
    currentSide = 0;
    updateEntries(currentSide);    //update all lists and tables
}

void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::on_activeLabel_Add_pushButton_clicked()
{
    qDebug()<<"Add active label button pressed";

    if(selectedTile == false) return;   //if no tile is selected return

    selectedTile->activeLabels[currentSide].append(new QListWidgetItem("0"));

    //make entries editable
    selectedTile->activeLabels[currentSide].last()->setFlags(selectedTile->activeLabels[currentSide].last()->flags() | Qt::ItemIsEditable);
    ui->activeLabels_listWidget->addItem(selectedTile->activeLabels[currentSide].last());


}


void MainWindow::on_activeLabel_Remove_pushButton_clicked()
{
    qDebug()<<"Remove active label button pressed";
    if(selectedTile == 0) return;   //if no tile is selected return

    if(ui->activeLabels_listWidget->currentItem() == 0)  //check if label exist
    {
        qDebug()<<"No item was selected\n";
    }
    else    //if it does
    {
        qDebug()<<"Selected item: "<<ui->activeLabels_listWidget->currentItem()->text()<<"\n";

        QListWidgetItem * toRemove = selectedTile->activeLabels[currentSide].at(ui->activeLabels_listWidget->currentRow());
        selectedTile->activeLabels[currentSide].removeAt(ui->activeLabels_listWidget->currentRow()); //delete it from the tile list

        ui->activeLabels_listWidget->takeItem(ui->activeLabels_listWidget->currentRow());   //delete it from the widget list
        delete toRemove;
    }
}

void MainWindow::on_inactiveLabel_Add_pushButton_clicked()
{
    qDebug()<<"Add inactive label button pressed";

    if(selectedTile == 0) return;   //if no tile is selected return

    selectedTile->inactiveLabels[currentSide].append(new QListWidgetItem("0"));

    //make entries editable
    selectedTile->inactiveLabels[currentSide].last()->setFlags(selectedTile->inactiveLabels[currentSide].last()->flags() | Qt::ItemIsEditable);
    ui->inactiveLabels_listWidget->addItem(selectedTile->inactiveLabels[currentSide].last()); //add item to the list widget
}

void MainWindow::on_inactiveLabel_Remove_pushButton_clicked()
{
    qDebug()<<"Remove inactive label button pressed";
    if(ui->inactiveLabels_listWidget->currentItem() == 0)  //check if label exist
    {
        qDebug()<<"No item was selected\n";
    }
    else    //if it does
    {
        qDebug()<<"Selected item: "<<ui->inactiveLabels_listWidget->currentItem()->text()<<"\n";

        QListWidgetItem * toRemove = selectedTile->inactiveLabels[currentSide].at(ui->inactiveLabels_listWidget->currentRow());
        selectedTile->inactiveLabels[currentSide].removeAt(ui->inactiveLabels_listWidget->currentRow()); //delete it from the tile list

        ui->inactiveLabels_listWidget->takeItem(ui->inactiveLabels_listWidget->currentRow());   //delete it from the widget list
        delete toRemove;

    }
}

void MainWindow::on_activationSig_Add_pushButton_clicked()
{
    qDebug()<<"Add activation signal button pressed";
    /*if(selectedTile == 0) return;
    ui->activationSignals_table->insertRow(ui->activationSignals_table->rowCount());
    QTableWidgetItem * item1 = new QTableWidgetItem("0");
    QComboBox * item2 = new QComboBox();
    item2->addItem("X");
    item2->addItem("Y");
    item2->addItem("-X");
    item2->addItem("-Y");
    tablePair *pair = new tablePair(item1, item2);
    selectedTile->activationSignals[currentSide].append(pair);
    ui->activationSignals_table->setItem(ui->activationSignals_table->rowCount() - 1, 0, selectedTile->activationSignals[currentSide].last()->first);
    ui->activationSignals_table->setCellWidget(ui->activationSignals_table->rowCount() - 1, 1, selectedTile->activationSignals[currentSide].last()->second);
*/

}

void MainWindow::on_activationSig_Remove_pushButton_clicked()
{
    qDebug()<<"Remove activation signal button pressed";
  /*  if(selectedTile == 0 || ui->activationSignals_table->rowCount() == 0) return;
    tablePair * toRemove = selectedTile->activationSignals[currentSide].at(ui->activationSignals_table->currentRow());
    selectedTile->activationSignals[currentSide].removeAt(ui->activationSignals_table->currentRow());
    ui->activationSignals_table->takeItem(ui->activationSignals_table->currentRow(), 0);
    ui->activationSignals_table->takeItem(ui->activationSignals_table->currentRow(), 1);
    ui->activationSignals_table->removeRow(ui->activationSignals_table->currentRow());

    delete toRemove;*/
}

void MainWindow::on_transmissionSig_Add_pushButton_clicked()
{
    qDebug()<<"Add transmission signal button pressed";
    //ui->transmissionSignals_table->insertRow(ui->transmissionSignals_table->rowCount());
}

void MainWindow::on_transmissionSig_Remove_pushButton_clicked()
{
    qDebug()<<"Remove transmission signal button pressed";
    //ui->transmissionSignals_table->removeRow(ui->transmissionSignals_table->currentRow());
}

void MainWindow::on_tile_comboBox_currentIndexChanged(int index) //when different tile is selected
{
    qDebug()<<"Combobox index changed to: "<<index;
    if(index < 0) return;
    ui->listWidget->setCurrentRow(index);
    selectedTile = tiles.at(index);
}



void MainWindow::on_listWidget_itemChanged(QListWidgetItem *item)
{
    qDebug()<<"Item changed event: "<<item->text();
    ui->tile_comboBox->removeItem(ui->listWidget->currentRow());
    ui->tile_comboBox->insertItem(ui->listWidget->currentRow(), item->text());
}

void MainWindow::on_radioButton_SideX_clicked()
{
    qDebug()<<"Side X checked";
    currentSide = 0;
    updateEntries(0);
}

void MainWindow::on_radioButton_SideY_clicked()
{
    qDebug()<<"Side Y checked";
    currentSide = 1;
    updateEntries(1);
}

void MainWindow::on_radioButton_Side_X_clicked()
{
    qDebug()<<"Side -X checked";
    currentSide = 2;
    updateEntries(2);
}

void MainWindow::on_radioButton_Side_Y_clicked()
{
    qDebug()<<"Side -Y checked";
    currentSide = 3;
    updateEntries(3);
}



void MainWindow::on_activeLabels_listWidget_itemChanged(QListWidgetItem *item)
{
    int value = item->text().toInt();
    qDebug()<<"Active label changed to: "<<value;
    if(this->strengthFunction.contains(value)) return; //check if current value is present
    this->strengthFunction[value] = -1;
    this->strengthFunction[-value] = -1;
    ui->strength_func_tableWidget->insertRow(ui->strength_func_tableWidget->rowCount());
    ui->strength_func_tableWidget->setItem(ui->strength_func_tableWidget->rowCount() - 1,
                                           0, new QTableWidgetItem(QString::number(abs(value))));
    ui->strength_func_tableWidget->setItem(ui->strength_func_tableWidget->rowCount() - 1,
                                           1, new QTableWidgetItem("-1"));
}

void MainWindow::on_inactiveLabels_listWidget_itemChanged(QListWidgetItem *item)
{
    int value = item->text().toInt();
    qDebug()<<"Inactive label changed to: "<<value;
    if(this->strengthFunction.contains(value)) return; //check if current value is present
    this->strengthFunction[value] = -1;
    this->strengthFunction[-value] = -1;
    ui->strength_func_tableWidget->insertRow(ui->strength_func_tableWidget->rowCount());
    ui->strength_func_tableWidget->setItem(ui->strength_func_tableWidget->rowCount() - 1,
                                           0, new QTableWidgetItem(QString::number(abs(value))));
    ui->strength_func_tableWidget->setItem(ui->strength_func_tableWidget->rowCount() - 1,
                                           1, new QTableWidgetItem("-1"));
}
