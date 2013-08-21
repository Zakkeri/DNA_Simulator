#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:

    void on_actionNew_Simulation_triggered();

    void on_NewTileButton_clicked();

    void on_DeleteTileButton_clicked();

    void on_BeginSim_Button_clicked();

    void on_tabWidget_currentChanged(int index);

private:
    Ui::MainWindow *ui;
    int currentTile;
};

#endif // MAINWINDOW_H
