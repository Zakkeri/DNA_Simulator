#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QImage>
#include <QGraphicsPixmapItem>
#include <QColorDialog>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QXmlStreamWriter>
#include <QFileDialog>
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
    ui->graphicsView_TileView->setVisible(false);
    ui->checkBox_seedTile->setVisible(false);

    ui->radioButton_SideX->setChecked(true);
    currentSide = 0;
    selectedTile = 0;

    //scalling added!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    ui->graphicsView->scale(2, 2); //scalling added!!!!


    filePath = "";
    modified = false;

    ui->splitter->setStretchFactor(0, 1);
    ui->splitter->setStretchFactor(1, 1);
    this->sim = 0;

    //Set up for 2HAM
    seedTile = 0;
    ui->action2HAM_simulation->trigger();
    ui->listWidget->setSelectionMode(QAbstractItemView::SingleSelection); //single selection
}

MainWindow::~MainWindow()
{
    for(QList<a_tile *>::iterator iter = tiles.begin(); iter != tiles.end(); ++iter)
    {
        delete (*iter);
    }

    if(this->sim != 0)
        delete this->sim;
    delete ui;
}

void MainWindow::paintCurrentTile()
{
    qDebug()<<"Going to paint current tile";
    if(selectedTile == 0) return;
    //DisplayTile tilePainting(10, 10, 200); //new DisplayTile object to draw
    DisplayTile * tilePainting = new DisplayTile(100); // object to draw
    for(int i = 0; i < 4; i++) //for all 4 sides
    {
        for(QList<QListWidgetItem *>::const_iterator iter = selectedTile->activeLabels[i].begin();
            iter != selectedTile->activeLabels[i].end(); iter++)
        { //add active labels
            tilePainting->addLabel(DisplayLabel(i, this->colorFunction[(*iter)->text().toInt()], true));
        }

        for(QList<QListWidgetItem *>::const_iterator iter = selectedTile->inactiveLabels[i].begin();
            iter != selectedTile->inactiveLabels[i].end(); iter++)
        { //add inactive labels
            tilePainting->addLabel(DisplayLabel(i, this->colorFunction[(*iter)->text().toInt()], false));
        }

        for(QList<tablePair *>::const_iterator iter = selectedTile->activationSignals[i].begin();
            iter != selectedTile->activationSignals[i].end(); iter++)
        { //add activation signals
            QString tstr = (*iter)->second->text();
            int t;
            if(tstr == "X" || tstr == "x") t = 0;
            else if(tstr == "Y" || tstr == "y") t = 1;
            else if(tstr == "_X" || tstr == "_x") t = 2;
            else if(tstr == "_Y" || tstr == "_y") t = 3;
            tilePainting->addSignal(DisplaySignal(i, t, this->colorFunction[(*iter)->first->text().toInt()], true));
        }

        for(QList<tablePair *>::const_iterator iter = selectedTile->transmissionSignals[i].begin();
            iter != selectedTile->transmissionSignals[i].end(); iter++)
        { //add transmission signals
            QString tstr = (*iter)->second->text();
            int t;
            if(tstr == "X" || tstr == "x") t = 0;
            else if(tstr == "Y" || tstr == "y") t = 1;
            else if(tstr == "_X" || tstr == "_x") t = 2;
            else if(tstr == "_Y" || tstr == "_y") t = 3;
            tilePainting->addSignal(DisplaySignal(i, t, this->colorFunction[(*iter)->first->text().toInt()], false));
        }
    }

    for(QList<tablePair *>::const_iterator iter = selectedTile->initiationSignals.begin();
        iter != selectedTile->initiationSignals.end(); iter++)
    { //add initiation signals
        QString tstr = (*iter)->second->text();
        int t;
        if(tstr == "X" || tstr == "x") t = 0;
        else if(tstr == "Y" || tstr == "y") t = 1;
        else if(tstr == "_X" || tstr == "_x") t = 2;
        else if(tstr == "_Y" || tstr == "_y") t = 3;
        tilePainting->addSignal(DisplaySignal(-1, t, this->colorFunction[(*iter)->first->text().toInt()]));
    }

    //QImage image(140, 140, QImage::Format_ARGB32);
   // QImage image(300, 300, QImage::Format_ARGB32); //create Q image object
   // QPainter painter(&image); //paint tile on QImage object first
    /*if(painter.begin(ui->graphicsView) == false)
    {
        qDebug()<<"Painter can't paint on the current device";
        return;
    }*/
  //  tilePainting.drawTile(painter); //perform painting operation

    QGraphicsScene* scene = new QGraphicsScene(); //new scene for QGraphicsView
   // scene->addPixmap(QPixmap::fromImage(image)); //add QImage to the scene
   // scene->setSceneRect(0,0,image.width(),image.height()); //set scene dimensions

    scene->addItem(tilePainting);
    QGraphicsScene* currentScene = ui->graphicsView_TileView->scene(); //get current scene of QGraphics view
    if(currentScene != 0) //if it exist, then delete it to be able to replace it with a new scene
        delete currentScene;
    ui->graphicsView_TileView->setScene(scene); //add scene with tile image to the QGraphics view
    //ui->graphicsView->scene()->addItem(tilePainting);


}

void MainWindow::on_actionNew_Simulation_triggered()
{
    qDebug()<<"New button was pressed";
    //Need to clear old data first if there is one
    filePath = ""; //clear the file path
    if(!tiles.isEmpty())
    {
        for(int i = ui->listWidget->count() - 1; i>=0; i--)
        {
            a_tile * toRemove = tiles.at(i); //get pointer to the item to remove
            tiles.removeOne(toRemove);  //remove item from the list of tiles
            ui->tile_comboBox->removeItem(i);    //remove item from the combo box
            ui->listWidget->takeItem(i);   //delete it from the list widget
            delete toRemove;  //remove item
        }

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
    }
    //clear strength function table as well
    for(int i = ui->strength_func_tableWidget->rowCount() - 1; i >= 0; i--)
    {
        ui->strength_func_tableWidget->takeItem(i, 0);
        ui->strength_func_tableWidget->takeItem(i, 1);
        ui->strength_func_tableWidget->takeItem(i, 2);
        ui->strength_func_tableWidget->removeRow(i);
    }
    strengthFunction.clear();
    colorFunction.clear();
    this->currentTile = 0;
    this->seedTile = 0;

    //delete previous simulator
    if(this->sim != 0)
    {
        delete this->sim;
        this->sim = 0;
    }

    //reset selected tile
    this->selectedTile = 0;

    //Remove painting from the small window
    QGraphicsScene* currentScene = ui->graphicsView_TileView->scene(); //get current scene of QGraphics view
    if(currentScene != 0) //if it exist, then delete it to be able to replace it with a new scene
        delete currentScene;
    //And the big window
    currentScene = ui->graphicsView->scene(); //get current scene of QGraphics view
    if(currentScene != 0) //if it exist, then delete it to be able to replace it with a new scene
        delete currentScene;

    //Delete previous results
    ui->treeWidget->clear();

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
    ui->graphicsView_TileView->setVisible(true);
    ui->checkBox_seedTile->setVisible(true);
    ui->stackedWidget->setCurrentIndex(0);
    ui->tabWidget->setCurrentIndex(0);
    modified = true;

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
        ui->activationSignals_table->setItem(ui->activationSignals_table->rowCount() - 1, 1, (*iter)->second);
    }

    for(QList<tablePair *>::const_iterator iter = selectedTile->transmissionSignals[side].begin();
        iter != selectedTile->transmissionSignals[side].end(); iter++)
    {
        ui->transmissionSignals_table->insertRow(ui->transmissionSignals_table->rowCount());//insert row
        //set items
        ui->transmissionSignals_table->setItem(ui->transmissionSignals_table->rowCount() - 1, 0, (*iter)->first);
        ui->transmissionSignals_table->setItem(ui->transmissionSignals_table->rowCount() - 1, 1, (*iter)->second);
    }

    for(QList<tablePair *>::const_iterator iter = selectedTile->initiationSignals.begin();
        iter != selectedTile->initiationSignals.end(); iter++)
    {
        ui->initiation_signals_tableWidget->insertRow(ui->initiation_signals_tableWidget->rowCount());//insert row
        //set items
        ui->initiation_signals_tableWidget->setItem(ui->initiation_signals_tableWidget->rowCount() - 1, 0, (*iter)->first);
        ui->initiation_signals_tableWidget->setItem(ui->initiation_signals_tableWidget->rowCount() - 1, 1, (*iter)->second);
    }

    if(ui->actionATAM_simulation->isChecked()) //if doing aTAM check or uncheck seed tile checkbox
    {
        if(seedTile == selectedTile)
            ui->checkBox_seedTile->setChecked(true);
        else
            ui->checkBox_seedTile->setChecked(false);
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
    modified = true;

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
    modified = true;
}

void MainWindow::on_BeginSim_Button_clicked()
{
    if(ui->actionATAM_simulation->isChecked() && seedTile == 0)
    {
        QMessageBox::warning(this, "Seed tile not selected", "Please select a seed tile");
        ui->tabWidget->setCurrentIndex(0);
        return;
    }
    //Need to add validation of input
    SetOfAssemblyTiles * Set = new SetOfAssemblyTiles();
    //for each store tile, create Assembly tile and add it to the set
    AssemblyTile * seed = 0; //in case I have a seed tile
    int ID = 0;
    for(QList<a_tile *>::const_iterator it = this->tiles.begin(); it != this->tiles.end(); ++it)
    {
        //list to construct
        QList<QList<int> > * activeLabels = new QList<QList<int> >();
        QList<QList<int> > * inactiveLabels = new QList<QList<int> >();
        QList<QList<Signal> > * activationSigs = new QList<QList<Signal> >();
        QList<QList<Signal> >* transmissionSigs = new QList<QList<Signal> >();
        QList<Signal> *initSigs = new QList<Signal>();
        //empty lists
        QList<int> empty;
        QList<Signal> em;
        for(int i = 0; i < 4; i++) //create sub lists
        {
            activeLabels->append(empty);
            inactiveLabels->append(empty);
            activationSigs->append(em);
            transmissionSigs->append(em);
        }

        for(int i = 0; i < 4; i++)
        {
            //add active labels
            for(QList<QListWidgetItem *>::const_iterator actIter = (*it)->activeLabels[i].begin();
                actIter != (*it)->activeLabels[i].end(); actIter++)
            {
                (*activeLabels)[i].append((*actIter)->text().toInt());
            }
            //add inactive labels
            for(QList<QListWidgetItem *>::const_iterator inactIter = (*it)->inactiveLabels[i].begin();
                inactIter != (*it)->inactiveLabels[i].end(); inactIter++)
            {
                (*inactiveLabels)[i].append((*inactIter)->text().toInt());
            }
            //add activation signals
            for(QList<tablePair *>::const_iterator asigIter = (*it)->activationSignals[i].begin();
                asigIter != (*it)->activationSignals[i].end(); asigIter++)
            {
                QString dir = (*asigIter)->second->text();
                direction d;
                if(dir == "X" || dir == "x") d = direction(0);
                else if(dir == "Y" || dir == "y") d = direction(1);
                else if(dir == "_X" || dir == "x") d = direction(2);
                else if(dir == "_Y" || dir == "_y") d = direction(3);
                else
                {
                    qDebug()<<"Wrong direction in the table";
                    return;
                }
                Signal sig((*asigIter)->first->text().toInt(),d);
                (*activationSigs)[i].append(sig);
            }
            //add transmission signals
            for(QList<tablePair *>::const_iterator tsigIter = (*it)->transmissionSignals[i].begin();
                tsigIter != (*it)->transmissionSignals[i].end(); tsigIter++)
            {
                QString dir = (*tsigIter)->second->text();
                direction d;
                if(dir == "X" || dir == "x") d = direction(0);
                else if(dir == "Y" || dir == "y") d = direction(1);
                else if(dir == "_X" || dir == "x") d = direction(2);
                else if(dir == "_Y" || dir == "_y") d = direction(3);
                else
                {
                    qDebug()<<"Wrong direction in the table";
                    return;
                }
                Signal sig((*tsigIter)->first->text().toInt(),d);
                (*transmissionSigs)[i].append(sig);
            }
        }

        //add Initiation signals
        for(QList<tablePair *>::const_iterator isigIter = (*it)->initiationSignals.begin();
            isigIter != (*it)->initiationSignals.end(); isigIter++)
        {
            QString dir = (*isigIter)->second->text();
            direction d;
            if(dir == "X" || dir == "x") d = direction(0);
            else if(dir == "Y" || dir == "y") d = direction(1);
            else if(dir == "_X" || dir == "x") d = direction(2);
            else if(dir == "_Y" || dir == "_y") d = direction(3);
            else
            {
                qDebug()<<"Wrong direction in the table";
                return;
            }
            Signal sig((*isigIter)->first->text().toInt(),d);
            initSigs->append(sig);
        }

        ActiveTile * T = new ActiveTile(*activeLabels, *inactiveLabels, *activationSigs, *transmissionSigs,
                                        *initSigs, ID++);
        AssemblyTile * AT = new AssemblyTile(T, this->strengthFunction);
        //If doing aTAM check for seed tile
        if(ui->actionATAM_simulation->isChecked() && seedTile == (*it))
        {
            seed = AT;
        }
        else
        {
            Set->addAssemblyTile(AT);
        }
    }

    //Instantiate the correct simulator
    if(ui->action2HAM_simulation->isChecked())
    {
        this->sim = new Simulator_2HAM(Set, this->strengthFunction, ui->ThetaParam_SpinBox->value(),
                                  ui->NumberOfSteps_SpinBox->value(), this->colorFunction);
    }
    else
    {
        this->sim = new Simulator_aTAM(seed, Set, this->strengthFunction, ui->ThetaParam_SpinBox->value(),
                                       ui->NumberOfSteps_SpinBox->value(), this->colorFunction);
    }
    this->sim->initialize();
    this->sim->startSimulation();
    qDebug()<<"Simulation is over";
    //Add result retrival and tile drawing!!!
   // QTreeWidget *tree = new QTreeWidget(ui->tab_5); //tree widget to store results
    //tree->setColumnCount(1);
    ui->treeWidget->clear();
    QList<SetOfAssemblyTiles *> resultSet = this->sim->getAssemblies(); //result set
    int i = 0; //loop index
    if(ui->actionATAM_simulation->isChecked()) //if doing aTAM simulation, then for i=0 put building blocks
    {
        QTreeWidgetItem *item = new QTreeWidgetItem(); //get an item for the set
        item->setText(0, "Building tiles");  //set text to the set
        SetOfAssemblyTiles* set = resultSet.at(i);
        for(int j = 0; j < set->getListOfAssemblyTiles().length(); j++)
        {
            QTreeWidgetItem * child = new QTreeWidgetItem(); //get an item for the tile
            child->setText(0,"Tile " + QString::number(j));
            item->addChild(child); //add tile to the set item
        }
        ui->treeWidget->addTopLevelItem(item); //add all tiles to the total tree
        i++;
    }
    for(; i < resultSet.length(); i++)
    //for(QList<SetOfAssemblyTiles *>::const_iterator it = resultSet.begin(); it != resultSet.end(); it++)
    {
        QTreeWidgetItem *item = new QTreeWidgetItem(); //get an item for the set
        item->setText(0, "Step " + QString::number(i));  //set text to the set
        SetOfAssemblyTiles* set = resultSet.at(i);
        for(int j = 0; j < set->getListOfAssemblyTiles().length(); j++)
        {
            QTreeWidgetItem * child = new QTreeWidgetItem(); //get an item for the tile
            child->setText(0,"Tile " + QString::number(j));
            item->addChild(child); //add tile to the set item
        }
        ui->treeWidget->addTopLevelItem(item); //add all tiles to the total tree

    }


}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    switch(index)
    {
    case 0:
        qDebug()<<"Index = 0\n";
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
        ui->graphicsView_TileView->setVisible(true);
        ui->checkBox_seedTile->setVisible(true);

        ui->stackedWidget->setCurrentIndex(0);

        ui->graphicsView->setVisible(false);
        break;
    case 1:
        qDebug()<<"Index = 1\n";
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
        ui->graphicsView_TileView->setVisible(true);
        ui->checkBox_seedTile->setVisible(true);

        ui->stackedWidget->setCurrentIndex(0);

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
        ui->graphicsView_TileView->setVisible(true);
        ui->checkBox_seedTile->setVisible(true);

        ui->stackedWidget->setCurrentIndex(0);

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
        ui->graphicsView_TileView->setVisible(false);
        ui->checkBox_seedTile->setVisible(false);

        ui->stackedWidget->setCurrentIndex(1);

        ui->graphicsView->setVisible(true); //show graphics
        //Paint tile
        this->paintCurrentTile();
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
        ui->graphicsView_TileView->setVisible(false);
        ui->checkBox_seedTile->setVisible(false);

        ui->stackedWidget->setCurrentIndex(1);

        ui->graphicsView->setVisible(true); //show graphics
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
    modified = true;
    this->paintCurrentTile();
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
    modified = true;
    this->paintCurrentTile();
}

void MainWindow::on_inactiveLabel_Add_pushButton_clicked()
{
    qDebug()<<"Add inactive label button pressed";

    if(selectedTile == 0) return;   //if no tile is selected return

    selectedTile->inactiveLabels[currentSide].append(new QListWidgetItem("0"));

    //make entries editable
    selectedTile->inactiveLabels[currentSide].last()->setFlags(selectedTile->inactiveLabels[currentSide].last()->flags() | Qt::ItemIsEditable);
    ui->inactiveLabels_listWidget->addItem(selectedTile->inactiveLabels[currentSide].last()); //add item to the list widget
    modified = true;
    this->paintCurrentTile();
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
    modified = true;
    this->paintCurrentTile();
}

void MainWindow::on_activationSig_Add_pushButton_clicked()
{
    qDebug()<<"Add activation signal button pressed";
    if(selectedTile == 0) return;
    ui->activationSignals_table->insertRow(ui->activationSignals_table->rowCount());
    QTableWidgetItem * item1 = new QTableWidgetItem("0");
    QTableWidgetItem * item2 = new QTableWidgetItem("X");
    tablePair *pair = new tablePair(item1, item2);
    selectedTile->activationSignals[currentSide].insert(ui->activationSignals_table->rowCount() - 1,pair);
    ui->activationSignals_table->setItem(ui->activationSignals_table->rowCount() - 1, 0, selectedTile->activationSignals[currentSide].last()->first);
    ui->activationSignals_table->setItem(ui->activationSignals_table->rowCount() - 1, 1, selectedTile->activationSignals[currentSide].last()->second);
    modified = true;
    this->paintCurrentTile();
}

void MainWindow::on_activationSig_Remove_pushButton_clicked()
{
    qDebug()<<"Remove activation signal button pressed";
    if(selectedTile == 0 || ui->activationSignals_table->currentItem() == 0) return;
    tablePair * toRemove = selectedTile->activationSignals[currentSide].at(ui->activationSignals_table->currentRow());
    selectedTile->activationSignals[currentSide].removeAt(ui->activationSignals_table->currentRow());
    ui->activationSignals_table->takeItem(ui->activationSignals_table->currentRow(), 0);
    ui->activationSignals_table->takeItem(ui->activationSignals_table->currentRow(), 1);
    ui->activationSignals_table->removeRow(ui->activationSignals_table->currentRow());

    delete toRemove;
    modified = true;
    this->paintCurrentTile();
}

void MainWindow::on_transmissionSig_Add_pushButton_clicked()
{
    qDebug()<<"Add transmission signal button pressed";
    if(selectedTile == 0) return;
    ui->transmissionSignals_table->insertRow(ui->transmissionSignals_table->rowCount());
    QTableWidgetItem * item1 = new QTableWidgetItem("0");
    QTableWidgetItem * item2 = new QTableWidgetItem("X");
    tablePair *pair = new tablePair(item1, item2);
    selectedTile->transmissionSignals[currentSide].insert(ui->transmissionSignals_table->rowCount() - 1,pair);
    ui->transmissionSignals_table->setItem(ui->transmissionSignals_table->rowCount() - 1, 0, selectedTile->transmissionSignals[currentSide].last()->first);
    ui->transmissionSignals_table->setItem(ui->transmissionSignals_table->rowCount() - 1, 1, selectedTile->transmissionSignals[currentSide].last()->second);
    modified = true;
    this->paintCurrentTile();
}

void MainWindow::on_transmissionSig_Remove_pushButton_clicked()
{
    qDebug()<<"Remove transmission signal button pressed";
    if(selectedTile == 0 || ui->transmissionSignals_table->currentItem() == 0) return;
    tablePair * toRemove = selectedTile->transmissionSignals[currentSide].at(ui->transmissionSignals_table->currentRow());
    selectedTile->transmissionSignals[currentSide].removeAt(ui->transmissionSignals_table->currentRow());
    ui->transmissionSignals_table->takeItem(ui->transmissionSignals_table->currentRow(), 0);
    ui->transmissionSignals_table->takeItem(ui->transmissionSignals_table->currentRow(), 1);
    ui->transmissionSignals_table->removeRow(ui->transmissionSignals_table->currentRow());

    delete toRemove;
    modified = true;
    this->paintCurrentTile();
}

void MainWindow::on_initiationSig_Add_button_clicked()
{
    qDebug()<<"Add initiation signal button pressed";
    if(selectedTile == 0) return;
    ui->initiation_signals_tableWidget->insertRow(ui->initiation_signals_tableWidget->rowCount());
    QTableWidgetItem * item1 = new QTableWidgetItem("0");
    QTableWidgetItem * item2 = new QTableWidgetItem("X");
    tablePair *pair = new tablePair(item1, item2);
    selectedTile->initiationSignals.insert(ui->initiation_signals_tableWidget->rowCount() - 1,pair);
    ui->initiation_signals_tableWidget->setItem(ui->initiation_signals_tableWidget->rowCount() - 1, 0, selectedTile->initiationSignals.last()->first);
    ui->initiation_signals_tableWidget->setItem(ui->initiation_signals_tableWidget->rowCount() - 1, 1, selectedTile->initiationSignals.last()->second);
    modified = true;
    this->paintCurrentTile();
}

void MainWindow::on_initiationSig_Remove_button_clicked()
{
    qDebug()<<"Remove initiation signal button pressed";
    if(selectedTile == 0 || ui->initiation_signals_tableWidget->currentItem() == 0) return;
    tablePair * toRemove = selectedTile->initiationSignals.at(ui->initiation_signals_tableWidget->currentRow());
    selectedTile->initiationSignals.removeAt(ui->initiation_signals_tableWidget->currentRow());
    ui->initiation_signals_tableWidget->takeItem(ui->initiation_signals_tableWidget->currentRow(), 0);
    ui->initiation_signals_tableWidget->takeItem(ui->initiation_signals_tableWidget->currentRow(), 1);
    ui->initiation_signals_tableWidget->removeRow(ui->initiation_signals_tableWidget->currentRow());

    delete toRemove;
    modified = true;
    this->paintCurrentTile();
}

void MainWindow::on_tile_comboBox_currentIndexChanged(int index) //when different tile is selected
{
    qDebug()<<"Combobox index changed to: "<<index;
    if(index < 0) return;
    ui->listWidget->setCurrentRow(index);
    selectedTile = tiles.at(index);
    ui->radioButton_SideX->setChecked(true);
    currentSide = 0;
    updateEntries(currentSide);
    this->paintCurrentTile();
}



void MainWindow::on_listWidget_itemChanged(QListWidgetItem *item)
{
    qDebug()<<"Item changed event: "<<item->text();
    ui->tile_comboBox->setItemText(ui->listWidget->currentRow(), item->text());
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
    if(value == 0)
        return;
    qDebug()<<"Active label changed to: "<<value;
    if(this->strengthFunction.contains(value)) //check if current value is present
    {
        this->paintCurrentTile();
        return;
    }
    this->strengthFunction[value] = -1;
    this->strengthFunction[-value] = -1;
    this->colorFunction[value] = QColor(0,0,0); //set color to white by default
    this->colorFunction[-value] = QColor(0,0,0);
    ui->strength_func_tableWidget->insertRow(ui->strength_func_tableWidget->rowCount());
    ui->strength_func_tableWidget->setItem(ui->strength_func_tableWidget->rowCount() - 1,
                                           0, new QTableWidgetItem(QString::number(abs(value))));
    ui->strength_func_tableWidget->setItem(ui->strength_func_tableWidget->rowCount() - 1,
                                           1, new QTableWidgetItem("-1"));
    modified = true;
    this->paintCurrentTile();
}

void MainWindow::on_inactiveLabels_listWidget_itemChanged(QListWidgetItem *item)
{
    int value = item->text().toInt();
    if(value == 0)
        return;
    qDebug()<<"Inactive label changed to: "<<value;
    if(this->strengthFunction.contains(value)) //check if current value is present
    {
        this->paintCurrentTile();
        return;
    }
    this->strengthFunction[value] = -1;
    this->strengthFunction[-value] = -1;
    this->colorFunction[value] = QColor(0,0,0); //set color to white by default
    this->colorFunction[-value] = QColor(0,0,0);
    ui->strength_func_tableWidget->insertRow(ui->strength_func_tableWidget->rowCount());
    ui->strength_func_tableWidget->setItem(ui->strength_func_tableWidget->rowCount() - 1,
                                           0, new QTableWidgetItem(QString::number(abs(value))));
    ui->strength_func_tableWidget->setItem(ui->strength_func_tableWidget->rowCount() - 1,
                                           1, new QTableWidgetItem("-1"));
    modified = true;
    this->paintCurrentTile();
}

void MainWindow::on_strength_func_tableWidget_itemChanged(QTableWidgetItem *item) //check for strength to be changed
{
    qDebug()<<"Strength table item changed";
    if(item->column() == 0)
    {
        qDebug()<<"Item for column 0 is changed to "<<item->text();
        if(item->text().toInt() == 0)
            return;
        if(strengthFunction.contains(item->text().toInt())) //if strength function contains item
        {//check if this item is in the table already
            bool inTable = false; //item is already in the table
            QSet<int> currItems; //set of labels in the table
            for(int i = 0; i < ui->strength_func_tableWidget->rowCount(); i++)
            {//iterate through all labels and put them in the set and check whether new label is already in the table
                if(i == item->row()) //skip current row
                    continue;
                QTableWidgetItem * next = ui->strength_func_tableWidget->item(i, 0);
                if(next->text() == item->text())
                    inTable = true;
                currItems.insert(next->text().toInt()); //insert positive value
                currItems.insert(-(next->text().toInt())); //insert negative value
            }
            if(inTable) //if label is in the table, then restore previous label
            {
                QMessageBox::warning(this, "Label is already present", "Label is already defined in the table");
                QList<int> result = strengthFunction.keys().toSet().subtract(currItems).values();
                if(result.empty())
                    item->setText("0");
                else
                {
                    int res = (result.first() == 0 ? result.last() : result.first());
                    item->setText(QString::number(abs(res)));
                }
            }
        }
        else
        {
            QSet<int> currItems; //set of labels in the table
            for(int i = 0; i < ui->strength_func_tableWidget->rowCount(); i++)
            {//iterate through all labels and put them in the set
                if(i == item->row()) //skip current row
                    continue;
                QTableWidgetItem * next = ui->strength_func_tableWidget->item(i, 0);
                currItems.insert(next->text().toInt()); //insert positive value
                currItems.insert(-(next->text().toInt())); //insert negative value
            }
            //Get label that used to be in the cell
            QList<int> label = strengthFunction.keys().toSet().subtract(currItems).values();
            if(label.empty()) //if there was no previous value, then just insert it
            {
                if(ui->strength_func_tableWidget->item(item->row(), 1)->text() == "-1")
                {//if strength was not defined, set it to default
                    strengthFunction[item->text().toInt()] = -1;
                    strengthFunction[-(item->text().toInt())] = -1;
                }
                else //set strength to the defined value
                {
                    strengthFunction[item->text().toInt()] = ui->strength_func_tableWidget->item(item->row(), 1)->text().toInt();
                    strengthFunction[-(item->text().toInt())] = ui->strength_func_tableWidget->item(item->row(), 1)->text().toInt();
                }

                if(ui->strength_func_tableWidget->item(item->row(), 2)->text() == "")
                {//if color is not defined, then set it to default
                    colorFunction[item->text().toInt()] = QColor(0,0,0);
                    colorFunction[-(item->text().toInt())] = QColor(0,0,0);
                }
                else
                {//else set it to the defined one
                    colorFunction[item->text().toInt()] = QColor(ui->strength_func_tableWidget->item(item->row(), 2)->text());
                    colorFunction[-(item->text().toInt())] = QColor(ui->strength_func_tableWidget->item(item->row(), 2)->text());
                }
            }
            else //remove old value
            {
                int oldLabel = abs((label.first() == 0 ? label.last() : label.first()));
                //Get strength of teh label
                int strength = strengthFunction[oldLabel];
                //Remove old strength value from the map
                strengthFunction.remove(oldLabel);
                strengthFunction.remove(-oldLabel);
                //Insert new label and its strength value
                strengthFunction[item->text().toInt()] = strength;
                strengthFunction[-(item->text().toInt())] = strength;

                //check if color map needs to be updated
                if(colorFunction.contains(oldLabel))
                {
                    QColor color = colorFunction[oldLabel]; //get color value
                    //remove old label
                    colorFunction.remove(oldLabel);
                    colorFunction.remove(-oldLabel);
                    //insert new label
                    colorFunction[item->text().toInt()] = color;
                    colorFunction[-(item->text().toInt())] = color;
                }
            }
        }
    }
    else if(item->column() == 1)
    {
        int key = ui->strength_func_tableWidget->item(item->row(), 0)->text().toInt();
        if(!strengthFunction.contains(key)) //if such key is not present, then return
            return;
        qDebug()<<"Label = "<<key;
        qDebug()<<"Strength changed to = "<<item->text().toInt();
        strengthFunction[key] = item->text().toInt();
        strengthFunction[-key] = item->text().toInt();
        modified = true;
    }
}

void MainWindow::on_strength_func_tableWidget_cellDoubleClicked(int row, int column)
{
    qDebug()<<"Strength function cell row: "<<row<<" column: "<<column<<" was double clicked";
    if(column == 2) //show color dialog to select color
    {
        QColorDialog colorD;
        QColor color = colorD.getColor(); //open color dialog
        if(!color.isValid()) return;    //check if user just canceled

        //Update colors
        this->colorFunction[ui->strength_func_tableWidget->item(row, 0)->text().toInt()] = color;
        this->colorFunction[-(ui->strength_func_tableWidget->item(row, 0)->text().toInt())] = color;
        QTableWidgetItem *forColor = new QTableWidgetItem(color.name());
        ui->strength_func_tableWidget->setItem(row, column, forColor);
        this->paintCurrentTile();

    }
    modified = true;
}

void MainWindow::on_treeWidget_clicked(const QModelIndex &index)
{
    qDebug()<<"Clicked column: "<<index.column()<<"Clicked row: "<<index.row();
    QModelIndex par = index.parent();
    qDebug()<<"Parent is valid? "<<par.isValid();
    if(!par.isValid())
        return;
    int setInd = par.row();
    int tileInd = index.row();

    QList<DisplayTile*> tiles = this->sim->toDisplayTile(
                this->sim->getAssemblies().at(setInd)->getListOfAssemblyTiles().at(tileInd));


    QGraphicsScene* scene = new QGraphicsScene();
    QGraphicsScene* currentScene = ui->graphicsView->scene();
    if(currentScene != 0)
           delete currentScene;
    ui->graphicsView->setScene(scene);

    for(QList<DisplayTile*>::iterator iter = tiles.begin(); iter != tiles.end(); iter++)
    {
        scene->addItem(*iter);
    }

    ui->graphicsView->setVisible(false);
    ui->graphicsView->setVisible(true);
}

//Save as function
void MainWindow::on_actionSave_triggered()
{
    filePath = QFileDialog::getSaveFileName(this, "Save", QString(), "Tiles (*.xml)");
    qDebug()<<"Save as: "<<filePath;
    on_actionSave_2_triggered();
}


//Save function
void MainWindow::on_actionSave_2_triggered()
{
    qDebug()<<"Save trigerred";
    if(filePath == "") //if no pass specified, ask user to put it
    {
        filePath = QFileDialog::getSaveFileName(this, "Save", QString(), "Tiles (*.xml)");
    }
    QFile writeFile(filePath);

    //try to open
    if (!writeFile.open(QIODevice::WriteOnly))
        return;
    QXmlStreamWriter save(&writeFile);
    save.setAutoFormatting(true);
    save.writeStartDocument(); //start writing document
    save.writeStartElement("TileSet");
    for(QList<a_tile *>::const_iterator iter = tiles.begin(); iter != tiles.end(); iter++)
    {
        save.writeStartElement("Tile");
        save.writeAttribute("name", (*iter)->Tile->text());
        if(seedTile != 0 && seedTile == *iter) //if this is a seed tile, mark it so
        {
            save.writeAttribute("seed", "1");
        }
        //save each side
        for(int i = 0; i < 4; i++)
        {
            save.writeStartElement("Side" + QString::number(i));
            //save active labels
            if(!(*iter)->activeLabels[i].isEmpty())
            {
                save.writeStartElement("ActiveLabels");
                for(QList<QListWidgetItem *>::const_iterator actIter = (*iter)->activeLabels[i].begin();
                    actIter != (*iter)->activeLabels[i].end(); actIter++)
                {
                    save.writeStartElement("label");
                    save.writeCharacters((*actIter)->text());
                    save.writeEndElement(); //end of label
                }
                save.writeEndElement(); //end of ActiveLabels
            }

            //save inactive labels
            if(!(*iter)->inactiveLabels[i].isEmpty())
            {
                save.writeStartElement("InactiveLabels");
                for(QList<QListWidgetItem *>::const_iterator inactIter = (*iter)->inactiveLabels[i].begin();
                    inactIter != (*iter)->inactiveLabels[i].end(); inactIter++)
                {
                    save.writeStartElement("label");
                    save.writeCharacters((*inactIter)->text());
                    save.writeEndElement(); //end of label
                }
                save.writeEndElement(); //end of InactiveLabels
            }

            //save activation signals
            if(!(*iter)->activationSignals[i].isEmpty())
            {
                save.writeStartElement("ActivationSignals");
                for(QList<tablePair *>::const_iterator asigIter = (*iter)->activationSignals[i].begin();
                    asigIter != (*iter)->activationSignals[i].end(); asigIter++)
                {
                    save.writeStartElement("signal");
                    save.writeAttribute("label", (*asigIter)->first->text());
                    save.writeAttribute("target", (*asigIter)->second->text());
                    save.writeEndElement(); //end of signal
                }
                save.writeEndElement(); //end of ActivationSignals
            }

            //save transmission signals
            if(!(*iter)->transmissionSignals[i].isEmpty())
            {
                save.writeStartElement("TransmissionSignals");
                for(QList<tablePair *>::const_iterator tsigIter = (*iter)->transmissionSignals[i].begin();
                    tsigIter != (*iter)->transmissionSignals[i].end(); tsigIter++)
                {
                    save.writeStartElement("signal");
                    save.writeAttribute("label", (*tsigIter)->first->text());
                    save.writeAttribute("target", (*tsigIter)->second->text());
                    save.writeEndElement(); //end of signal
                }
                save.writeEndElement(); //end of TransmissionSignals
            }
            save.writeEndElement(); //write end for side
        }

        //save Initiation signals
        if(!(*iter)->initiationSignals.isEmpty())
        {
            save.writeStartElement("InitiationSignals");
            for(QList<tablePair *>::const_iterator isigIter = (*iter)->initiationSignals.begin();
                isigIter != (*iter)->initiationSignals.end(); isigIter++)
            {
                save.writeStartElement("signal");
                save.writeAttribute("label", (*isigIter)->first->text());
                save.writeAttribute("target", (*isigIter)->second->text());
                save.writeEndElement(); //end of signal
            }
            save.writeEndElement(); //write end for InitiationSignals
        }
        save.writeEndElement();//end tile element
    }
    //write strength function block
    save.writeStartElement("StrengthFunction");
    for(QMap<int, int>::iterator it = strengthFunction.begin(); it != strengthFunction.end(); it++)
    {
        save.writeStartElement("stren");
        save.writeAttribute("key", QString::number(it.key()));
        save.writeAttribute("strength", QString::number(it.value()));
        save.writeAttribute("color", colorFunction[it.key()].name());
        save.writeEndElement(); //end of strength
    }
    save.writeEndElement(); //end writing of StrengthFunction
    save.writeEndElement(); //end of tileset
    save.writeEndDocument(); //end writing a document
    writeFile.close();
}

//Load Action
void MainWindow::on_actionLoad_triggered()
{
    //Open dialog for user to select file
    filePath = QFileDialog::getOpenFileName(this, "Open File", QString(), "Tile (*.xml)");
    QFile readFile(filePath); //declare and open file
    if (!readFile.open(QIODevice::ReadOnly))
        return;

    //Remove old data
    this->selectedTile = 0;
    this->seedTile = 0;
    ui->treeWidget->clear();
    if(!tiles.isEmpty())
    {
        for(int i = ui->listWidget->count() - 1; i>=0; i--)
        {
            a_tile * toRemove = tiles.at(i); //get pointer to the item to remove
            tiles.removeOne(toRemove);  //remove item from the list of tiles
            ui->tile_comboBox->removeItem(i);    //remove item from the combo box
            ui->listWidget->takeItem(i);   //delete it from the list widget
            delete toRemove;  //remove item
        }

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
    }
    //clear strength function table as well
    for(int i = ui->strength_func_tableWidget->rowCount() - 1; i >= 0; i--)
    {
        ui->strength_func_tableWidget->takeItem(i, 0);
        ui->strength_func_tableWidget->takeItem(i, 1);
        ui->strength_func_tableWidget->takeItem(i, 2);
        ui->strength_func_tableWidget->removeRow(i);
    }
    strengthFunction.clear();
    colorFunction.clear();
    this->currentTile = 0;

    //Remove painting from the small window
    QGraphicsScene* currentScene = ui->graphicsView_TileView->scene(); //get current scene of QGraphics view
    if(currentScene != 0) //if it exist, then delete it to be able to replace it with a new scene
        delete currentScene;
    //And the big window
    currentScene = ui->graphicsView->scene(); //get current scene of QGraphics view
    if(currentScene != 0) //if it exist, then delete it to be able to replace it with a new scene
        delete currentScene;
    ui->tabWidget->setCurrentIndex(0);

    QXmlStreamReader read(&readFile); //declare xml reader
    read.readNextStartElement(); //read TileSet tag
    read.readNextStartElement(); //read next tile
    while(!read.isEndElement() || read.name() != "TileSet") //read untill the end of start element
    {
        if(read.name() == "Tile" && !read.isEndElement()) //if read tile open element, add tile
        {
            QString tileName = read.attributes().value("name").toString(); //get tile name
            tiles.append(selectedTile = new a_tile(tileName)); //set current tile and append it to the list
            if(read.attributes().hasAttribute("seed")) // if this is a seed tile, mark it so
            {
                this->seedTile = tiles.last();
                if(ui->actionATAM_simulation->isChecked()) //if aTAM simulation is trigered, change tile text color
                {
                    this->seedTile->Tile->setForeground(Qt::darkGreen);
                }
            }
            tiles.last()->Tile->setFlags(tiles.last()->Tile->flags() | Qt::ItemIsEditable);
            ui->listWidget->addItem(tiles.last()->Tile); //add tile to the list
            ui->tile_comboBox->addItem(tileName);  //add tile to the combo box
            (this->currentTile)++;  //increase counter
        }
        else if(read.name() == "Side0" && !read.isEndElement())
            currentSide = 0;
        else if(read.name() == "Side1" && !read.isEndElement())
            currentSide = 1;
        else if(read.name() == "Side2" && !read.isEndElement())
            currentSide = 2;
        else if(read.name() == "Side3" && !read.isEndElement())
            currentSide = 3;
        else if(read.name() == "ActiveLabels" && !read.isEndElement())
        {
            read.readNextStartElement(); //get next start element
            while(read.name() != "ActiveLabels") //while haven't got to the end element
            {
                if(read.name() == "label" && !read.isEndElement())
                {
                    selectedTile->activeLabels[currentSide].append(new QListWidgetItem(read.readElementText()));
                    //make entries editable
                    selectedTile->activeLabels[currentSide].last()->setFlags(selectedTile->activeLabels[currentSide].last()->flags() | Qt::ItemIsEditable);
                }
                read.readNextStartElement(); //read next start element
            }
        }
        else if(read.name() == "InactiveLabels" && !read.isEndElement())
        {
            read.readNextStartElement(); //get next start element
            while(read.name() != "InactiveLabels") //while haven't got to the end element
            {
                if(read.name() == "label" && !read.isEndElement())
                {
                    selectedTile->inactiveLabels[currentSide].append(new QListWidgetItem(read.readElementText()));
                    //make entries editable
                    selectedTile->inactiveLabels[currentSide].last()->setFlags(selectedTile->inactiveLabels[currentSide].last()->flags() | Qt::ItemIsEditable);
                }
                read.readNextStartElement(); //read next start element
            }
        }
        else if(read.name() == "ActivationSignals" && !read.isEndElement())
        {
            read.readNextStartElement(); //get next start element
            while(read.name() != "ActivationSignals") //while haven't got to the end element
            {
                if(read.name() == "signal" && !read.isEndElement())
                {
                    QTableWidgetItem * item1 = new QTableWidgetItem(read.attributes().value("label").toString());
                    QTableWidgetItem * item2 = new QTableWidgetItem(read.attributes().value("target").toString());
                    tablePair *pair = new tablePair(item1, item2);
                    selectedTile->activationSignals[currentSide].append(pair);
                }
                read.readNextStartElement(); //get next start element
            }

        }
        else if(read.name() == "TransmissionSignals" && !read.isEndElement())
        {
            read.readNextStartElement(); //get next start element
            while(read.name() != "TransmissionSignals") //while haven't got to the end element
            {
                if(read.name() == "signal" && !read.isEndElement())
                {
                    QTableWidgetItem * item1 = new QTableWidgetItem(read.attributes().value("label").toString());
                    QTableWidgetItem * item2 = new QTableWidgetItem(read.attributes().value("target").toString());
                    tablePair *pair = new tablePair(item1, item2);
                    selectedTile->transmissionSignals[currentSide].append(pair);
                }
                read.readNextStartElement(); //get next start element
            }
        }
        else if(read.name() == "InitiationSignals" && !read.isEndElement())
        {
            read.readNextStartElement(); //get next start element
            while(read.name() != "InitiationSignals") //while haven't got to the end element
            {
                if(read.name() == "signal" && !read.isEndElement())
                {
                    QTableWidgetItem * item1 = new QTableWidgetItem(read.attributes().value("label").toString());
                    QTableWidgetItem * item2 = new QTableWidgetItem(read.attributes().value("target").toString());
                    tablePair *pair = new tablePair(item1, item2);
                    selectedTile->initiationSignals.append(pair);
                }
                read.readNextStartElement(); //get next start element
            }
        }
        else if(read.name() == "StrengthFunction" && !read.isEndElement())
        {
            read.readNextStartElement(); //read stren element
            while(read.name() != "StrengthFunction")
            {
                if(read.name() == "stren" && !read.isEndElement())//while haven't got to the end element
                {
                    int ind = read.attributes().value("key").toString().toInt(); //get index
                    int str = read.attributes().value("strength").toString().toInt(); //get strength
                    strengthFunction[ind] = str;
                    colorFunction[ind] = QColor(read.attributes().value("color").toString());
                    if(ind > 0) //add strength to the list on positive index
                    {
                        //insert row
                        ui->strength_func_tableWidget->insertRow(ui->strength_func_tableWidget->rowCount());
                        //first column
                        ui->strength_func_tableWidget->setItem(ui->strength_func_tableWidget->rowCount() - 1,
                                                               0, new QTableWidgetItem(QString::number(ind)));
                        //second column
                        ui->strength_func_tableWidget->setItem(ui->strength_func_tableWidget->rowCount() - 1,
                                                               1, new QTableWidgetItem(QString::number(str)));
                        //third column
                        ui->strength_func_tableWidget->setItem(ui->strength_func_tableWidget->rowCount() - 1,
                                                               2, new QTableWidgetItem(read.attributes().value("color").toString()));
                    }
                }
                read.readNextStartElement();
            }
        }
        read.readNextStartElement(); //read next
    }

    readFile.close(); //close file

    //Show all hidden frames
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
    ui->graphicsView_TileView->setVisible(true);
    ui->checkBox_seedTile->setVisible(true);

    ui->listWidget->item(0)->setSelected(true);
    this->selectedTile = this->tiles.first();
    this->currentSide = 0;
    updateEntries(0);
    this->paintCurrentTile();
}

void MainWindow::on_activationSignals_table_itemChanged(QTableWidgetItem *item)
{
    qDebug()<<"Activation signal item was changed";
    this->paintCurrentTile();
}

void MainWindow::on_transmissionSignals_table_itemChanged(QTableWidgetItem *item)
{
    qDebug()<<"Transmission signal item was changed";
    this->paintCurrentTile();
}

void MainWindow::on_initiation_signals_tableWidget_itemChanged(QTableWidgetItem *item)
{
    qDebug()<<"Initiation signal item was changed";
    this->paintCurrentTile();
}

void MainWindow::on_strengthFunc_Add_Button_clicked()
{
    int rowCount = ui->strength_func_tableWidget->rowCount(); //get index of the next row
    ui->strength_func_tableWidget->insertRow(rowCount);
    ui->strength_func_tableWidget->setItem(rowCount, 0, new QTableWidgetItem("0"));
    ui->strength_func_tableWidget->setItem(rowCount, 1, new QTableWidgetItem("-1"));
    ui->strength_func_tableWidget->setItem(rowCount, 2, new QTableWidgetItem(""));
}

void MainWindow::on_strengthFunc_Remove_Button_clicked()
{
    int row = ui->strength_func_tableWidget->currentRow(); //get current row
    int key = ui->strength_func_tableWidget->item(row, 0)->text().toInt(); //get key for the map
    //remove items from the strength map, if needed
    if(strengthFunction.contains(key))
    {
        strengthFunction.remove(key);
        strengthFunction.remove(-key);
    }
    //remove items from the color map if needed
    if(colorFunction.contains(key))
    {
        colorFunction.remove(key);
        colorFunction.remove(-key);
    }
    //remove entry from the table
    QTableWidgetItem* toDelete =  ui->strength_func_tableWidget->takeItem(row, 0);
    if(toDelete != 0)
        delete toDelete;
    toDelete =  ui->strength_func_tableWidget->takeItem(row, 1);
        if(toDelete != 0)
            delete toDelete;
    toDelete =  ui->strength_func_tableWidget->takeItem(row, 2);
        if(toDelete != 0)
            delete toDelete;
    ui->strength_func_tableWidget->removeRow(row);
}

void MainWindow::on_action2HAM_simulation_triggered()
{
    qDebug()<<"Doing 2HAM simulation";
    //this->simulationModel = 1;
    ui->actionATAM_simulation->setChecked(false);
    ui->action2HAM_simulation->setChecked(true);
    ui->checkBox_seedTile->setEnabled(false);
    if(seedTile != 0) //set foreground to black
    {
        seedTile->Tile->setForeground(Qt::black);
    }
    ui->checkBox_seedTile->setChecked(false);
}

void MainWindow::on_actionATAM_simulation_triggered()
{
    qDebug()<<"Doing aTAM simulation";
    //this->simulationModel = 2;
    ui->action2HAM_simulation->setChecked(false);
    ui->actionATAM_simulation->setChecked(true);
    ui->checkBox_seedTile->setEnabled(true);
    if(seedTile != 0) //set foreground to dark green
    {
        seedTile->Tile->setForeground(Qt::darkGreen);
        if(seedTile == this->selectedTile)
        {
            ui->checkBox_seedTile->setChecked(true);
        }
    }

}

void MainWindow::on_checkBox_seedTile_clicked(bool checked)
{
    if(selectedTile == 0) return; //if no tile selected, then return
    if(checked) //if checked tile as a seed
    {
        if(seedTile == 0) seedTile = selectedTile; //set new seed tile
        else //make previous seed tile to be non-seed tile
        {
            seedTile->Tile->setForeground(Qt::black); //change text color to black
            seedTile = selectedTile; //update seed tile
        }
        seedTile->Tile->setForeground(Qt::darkGreen); //make tile name color green
    }
    else //if unchecked tile to become non-seed
    {
        seedTile->Tile->setForeground(Qt::black); //change text color to black
        seedTile = 0; //unreference seed tile
    }
}
