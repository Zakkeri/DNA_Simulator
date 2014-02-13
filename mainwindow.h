#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QTableWidget>
#include <QComboBox>
#include <QMap>
#include <QString>
#include <QPainter>
#include <QGraphicsScene>
//#include "Headers/displaytile.h"
#include "Headers/displaytile2.h"
#include "Headers/ActiveTile.h"
#include "Headers/AssemblyTile.h"
#include "Headers/SetOfAssemblyTiles.h"
#include "Headers/Simulator.h"
#include "Headers/AdditionalData.h"
#include "Headers/AssemblyTileSetManager.h"
namespace Ui {
class MainWindow;
}

struct tablePair
{
    tablePair(QTableWidgetItem * f, QTableWidgetItem * s)
    {
        first = f;
        second = s;
    }

    ~tablePair()
    {
        delete first;
        delete second;
    }

    QTableWidgetItem * first;
    QTableWidgetItem * second;
};

struct a_tile   //struct that will hold all information about a single tile
{
    a_tile(QString tileName)
    {
        this->Tile = new QListWidgetItem(tileName);
    }

    ~a_tile()
    {
        delete Tile;

        for(int i = 0; i < 4; i++)
        {
            for(QList<QListWidgetItem *>::iterator iter = activeLabels[i].begin(); iter != activeLabels[i].end(); iter++)
            {
                 delete (*iter);
            }

            for(QList<QListWidgetItem *>::iterator iter = inactiveLabels[i].begin(); iter != inactiveLabels[i].end(); iter++)
            {
                 delete (*iter);
            }

            for(QList<tablePair*>::iterator iter = activationSignals[i].begin();
                iter != activationSignals[i].end(); iter++)
            {
                delete (*iter);
            }

            for(QList<tablePair*>::iterator iter = transmissionSignals[i].begin();
                iter != transmissionSignals[i].end(); iter++)
            {
                delete (*iter);
            }
        }

        for(QList<tablePair*>::iterator iter = initiationSignals.begin();
            iter != initiationSignals.end(); iter++)
        {
            delete (*iter);
        }
    }

    //Tile entry in the main lists of tiles
    QListWidgetItem * Tile;

    //Active labels
    QList<QListWidgetItem *> activeLabels[4];

    //Inactive labels
    QList<QListWidgetItem *> inactiveLabels[4];

    //Activation Signals
    QList<tablePair *> activationSignals[4];

    //Transmission Signals
    QList<tablePair *> transmissionSignals[4];

    //Initiation Signals
    QList<tablePair*> initiationSignals;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void updateEntries(short side);   //update all entries with current tile value
    void paintCurrentTile();
    
private slots:

    void on_actionNew_Simulation_triggered();

    void on_NewTileButton_clicked();

    void on_DeleteTileButton_clicked();

    void on_BeginSim_Button_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_actionExit_triggered();

    void on_activeLabel_Add_pushButton_clicked();

    void on_activeLabel_Remove_pushButton_clicked();

    void on_inactiveLabel_Add_pushButton_clicked();

    void on_inactiveLabel_Remove_pushButton_clicked();

    void on_activationSig_Add_pushButton_clicked();

    void on_activationSig_Remove_pushButton_clicked();

    void on_transmissionSig_Add_pushButton_clicked();

    void on_transmissionSig_Remove_pushButton_clicked();

    void on_tile_comboBox_currentIndexChanged(int index);


    void on_listWidget_itemChanged(QListWidgetItem *item);

    void on_radioButton_SideX_clicked();

    void on_radioButton_SideY_clicked();

    void on_radioButton_Side_X_clicked();

    void on_radioButton_Side_Y_clicked();

    void on_listWidget_clicked(const QModelIndex &index);

    void on_activeLabels_listWidget_itemChanged(QListWidgetItem *item);

    void on_inactiveLabels_listWidget_itemChanged(QListWidgetItem *item);

    void on_strength_func_tableWidget_itemChanged(QTableWidgetItem *item);

    void on_strength_func_tableWidget_cellDoubleClicked(int row, int column);

    void on_initiationSig_Add_button_clicked();

    void on_initiationSig_Remove_button_clicked();

    void on_treeWidget_clicked(const QModelIndex &index);

    void on_actionSave_triggered();

    void on_actionSave_2_triggered();

    void on_actionLoad_triggered();

    void on_activationSignals_table_itemChanged(QTableWidgetItem *item);

    void on_transmissionSignals_table_itemChanged(QTableWidgetItem *item);

    void on_initiation_signals_tableWidget_itemChanged(QTableWidgetItem *item);

private:
    Ui::MainWindow *ui;
    int currentTile;    //will keep a count of the tiles that were created
    QList<a_tile *> tiles;
    a_tile * selectedTile;
    short currentSide;
    QMap<int, int> strengthFunction;
    QMap<int, QColor> colorFunction;
    Simulator * sim;

    //For saving and loading
    QString filePath; //path of currently saved/loaded tiles
    bool modified; //if file was modified

};

#endif // MAINWINDOW_H
