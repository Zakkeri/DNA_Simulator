#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QTableWidget>
#include <QComboBox>
#include <QMap>
namespace Ui {
class MainWindow;
}

struct tablePair
{
    tablePair(QTableWidgetItem * f, QComboBox * s)
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
    QComboBox * second;
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

       /* for(QList<QListWidgetItem *>::iterator iter = activeLabelsX.begin(); iter != activeLabelsX.end(); iter++)
        {
            delete (*iter);
        }

        for(QList<QListWidgetItem *>::iterator iter = activeLabels_X.begin(); iter != activeLabels_X.end(); iter++)
        {
            delete (*iter);
        }

        for(QList<QListWidgetItem *>::iterator iter = activeLabelsY.begin(); iter != activeLabelsY.end(); iter++)
        {
            delete (*iter);
        }

        for(QList<QListWidgetItem *>::iterator iter = activeLabels_Y.begin(); iter != activeLabels_Y.end(); iter++)
        {
            delete (*iter);
        }

        for(QList<QListWidgetItem *>::iterator iter = inactiveLabelsX.begin(); iter != inactiveLabelsX.end(); iter++)
        {
            delete (*iter);
        }

        for(QList<QListWidgetItem *>::iterator iter = inactiveLabels_X.begin(); iter != inactiveLabels_X.end(); iter++)
        {
            delete (*iter);
        }

        for(QList<QListWidgetItem *>::iterator iter = inactiveLabelsY.begin(); iter != inactiveLabelsY.end(); iter++)
        {
            delete (*iter);
        }

        for(QList<QListWidgetItem *>::iterator iter = inactiveLabels_Y.begin(); iter != inactiveLabels_Y.end(); iter++)
        {
            delete (*iter);
        }

        for(QList<QPair<QTableWidgetItem  *, QTableWidgetItem  *> >::iterator iter = activationSignalsX.begin(); iter != activationSignalsX.end(); iter++)
        {
            delete (*iter).first;
            delete (*iter).second;
        }

        for(QList<QPair<QTableWidgetItem  *, QTableWidgetItem  *> >::iterator iter = activationSignals_X.begin(); iter != activationSignals_X.end(); iter++)
        {
            delete (*iter).first;
            delete (*iter).second;
        }

        for(QList<QPair<QTableWidgetItem  *, QTableWidgetItem  *> >::iterator iter = activationSignalsY.begin(); iter != activationSignalsY.end(); iter++)
        {
            delete (*iter).first;
            delete (*iter).second;
        }

        for(QList<QPair<QTableWidgetItem  *, QTableWidgetItem  *> >::iterator iter = activationSignals_Y.begin(); iter != activationSignals_Y.end(); iter++)
        {
            delete (*iter).first;
            delete (*iter).second;
        }

        for(QList<QPair<QTableWidgetItem  *, QTableWidgetItem  *> >::iterator iter = transmissionSignalsX.begin(); iter != transmissionSignalsX.end(); iter++)
        {
            delete (*iter).first;
            delete (*iter).second;
        }

        for(QList<QPair<QTableWidgetItem  *, QTableWidgetItem  *> >::iterator iter = transmissionSignals_X.begin(); iter != transmissionSignals_X.end(); iter++)
        {
            delete (*iter).first;
            delete (*iter).second;
        }

        for(QList<QPair<QTableWidgetItem  *, QTableWidgetItem  *> >::iterator iter = transmissionSignalsY.begin(); iter != transmissionSignalsY.end(); iter++)
        {
            delete (*iter).first;
            delete (*iter).second;
        }

        for(QList<QPair<QTableWidgetItem  *, QTableWidgetItem  *> >::iterator iter = transmissionSignals_Y.begin(); iter != transmissionSignals_Y.end(); iter++)
        {
            delete (*iter).first;
            delete (*iter).second;
        }

        for(QList<QPair<QTableWidgetItem  *, QTableWidgetItem  *> >::iterator iter = initiationSignals.begin(); iter != initiationSignals.end(); iter++)
        {
            delete (*iter).first;
            delete (*iter).second;
        }*/
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

            for(QList<QPair<QTableWidgetItem  *, QTableWidgetItem  *> >::iterator iter = transmissionSignals[i].begin();
                iter != transmissionSignals[i].end(); iter++)
            {
                delete (*iter).first;
                delete (*iter).second;
            }
        }

        for(QList<QPair<QTableWidgetItem  *, QTableWidgetItem  *> >::iterator iter = initiationSignals.begin();
            iter != initiationSignals.end(); iter++)
        {
            delete (*iter).first;
            delete (*iter).second;
        }
    }

    //Tile entry in the main lists of tiles
    QListWidgetItem * Tile;

    //Active labels
    QList<QListWidgetItem *> activeLabels[4];
    /*QList<QListWidgetItem *> activeLabelsX;
    QList<QListWidgetItem *> activeLabels_X;
    QList<QListWidgetItem *> activeLabelsY;
    QList<QListWidgetItem *> activeLabels_Y;
*/
    //Inactive labels
    QList<QListWidgetItem *> inactiveLabels[4];
    /*QList<QListWidgetItem *> inactiveLabelsX;
    QList<QListWidgetItem *> inactiveLabels_X;
    QList<QListWidgetItem *> inactiveLabelsY;
    QList<QListWidgetItem *> inactiveLabels_Y;
*/
    //Activation Signals
    QList<tablePair *> activationSignals[4];
    /*
    QList<QPair<QTableWidgetItem  *, QTableWidgetItem  *> > activationSignalsX;
    QList<QPair<QTableWidgetItem  *, QTableWidgetItem  *> > activationSignals_X;
    QList<QPair<QTableWidgetItem  *, QTableWidgetItem  *> > activationSignalsY;
    QList<QPair<QTableWidgetItem  *, QTableWidgetItem  *> > activationSignals_Y;
*/
    //Transmission Signals
    QList<QPair<QTableWidgetItem  *, QTableWidgetItem  *> > transmissionSignals[4];
    /*
    QList<QPair<QTableWidgetItem  *, QTableWidgetItem  *> > transmissionSignalsX;
    QList<QPair<QTableWidgetItem  *, QTableWidgetItem  *> > transmissionSignals_X;
    QList<QPair<QTableWidgetItem  *, QTableWidgetItem  *> > transmissionSignalsY;
    QList<QPair<QTableWidgetItem  *, QTableWidgetItem  *> > transmissionSignals_Y;
*/
    //Initiation Signals
    QList<QPair<QTableWidgetItem  *, QTableWidgetItem  *> > initiationSignals;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void updateEntries(short side);   //update all entries with current tile value
    
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

private:
    Ui::MainWindow *ui;
    int currentTile;    //will keep a count of the tiles that were created
    QList<a_tile *> tiles;
    a_tile * selectedTile;
    short currentSide;
    QMap<int, int> strengthFunction;
};

#endif // MAINWINDOW_H
