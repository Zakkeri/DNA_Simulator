#include "mainwindow.h"
#include <QApplication>
#include<QMap>
#include"Headers/SetOfAssemblyTiles.h"
#include"Headers/Simulator_2HAM.h"
#include"Headers/ActiveTile.h"
#include"Headers/AssemblyTile.h"
#include<QDebug>
#define DEBUG
//#define TEST1
//#define TEST2
//#define TEST3
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
#ifdef TEST1
    int theta = 1;
    int steps = 20;
    QMap<int, int> StrengthFunction;
    /*
     1 - black
     2 - green
     3 - purple
     4 - pink
     */
    qDebug()<<"Setting up a strength function";
    StrengthFunction[1] = 0;
    for(int i = 2; i < 5; i++)
    {
        StrengthFunction[i] = 1;
        StrengthFunction[-i] = 1;
    }

    SetOfAssemblyTiles *simulationSet = new SetOfAssemblyTiles;

    QList<int> side0;
    side0.append(4);
    side0.append(1);
    QList<int> side1;
    side1.append(1);
    QList<int> side2;
    side2.append(1);
    QList<int> side3;
    side3.append(1);
    QList<QList<int> > acLabels;
    acLabels.append(side0);
    acLabels.append(side1);
    acLabels.append(side2);
    acLabels.append(side3);

    side0.clear();
    side1.clear();
    side2.clear();
    side3.clear();

    QList<int> empty;
    QList<QList<int> > inLabels;
    inLabels.append(empty);
    inLabels.append(empty);
    inLabels.append(empty);
    inLabels.append(empty);

    QList<Signal> em;
    QList<QList<Signal> > acSignals;
    acSignals.append(em);
    acSignals.append(em);
    acSignals.append(em);
    acSignals.append(em);

    QList<QList<Signal> > trSignals;
    trSignals.append(em);
    trSignals.append(em);
    trSignals.append(em);
    trSignals.append(em);

    QList<Signal> init;
    init.append(Signal(2, x));
    init.append(Signal(3, x));
qDebug()<<"Creating Active tile t0";
    ActiveTile *t0 = new ActiveTile(acLabels, inLabels, acSignals, trSignals, init,0);

    QList<QList<int> > acLabels1;
    QList<int> side01;
    side01.append(1);
    acLabels1.append(side01);
    QList<int> side11;
    side11.append(1);
    acLabels1.append(side11);
    QList<int> side21;
    side21.append(1);
    side21.append(-4);
    acLabels1.append(side21);

    QList<int> side31;
    side31.append(1);
    acLabels1.append(side31);

    QList<QList<int> > inLabels1;
    QList<int> empty1;
    inLabels1.append(empty1);
    inLabels1.append(empty1);
    inLabels1.append(empty1);
    inLabels1.append(empty1);

    inLabels1[0].append(-2);

    QList<QList<Signal> > acSignals1(acSignals);
    acSignals1[2].append(Signal(2, x));

    QList<QList<Signal> > trSignals1(trSignals);
    trSignals1[2].append(Signal(3, x));
    trSignals1[2].append(Signal(2, x));

    QList<Signal> init1;


qDebug()<<"Creating Active tile t1";
    ActiveTile * t1 = new ActiveTile(acLabels1, inLabels1, acSignals1, trSignals1, init1,1);

    QList<QList<int> > acLabels2;
    acLabels2.append(empty);
    acLabels2.append(empty);
    acLabels2.append(empty);
    acLabels2.append(empty);

    acLabels2[0].append(1);
    acLabels2[1].append(1);
    acLabels2[2].append(1);
    acLabels2[2].append(2);
    acLabels2[3].append(1);

    QList<QList<int> > inLabels2;
    inLabels2.append(empty);
    inLabels2.append(empty);
    inLabels2.append(empty);
    inLabels2.append(empty);

    inLabels2[0].append(-3);

    QList<QList<Signal> > acSignals2;
    acSignals2.append(em);
    acSignals2.append(em);
    acSignals2.append(em);
    acSignals2.append(em);

    acSignals2[2].append(Signal(3, x));

    QList<QList<Signal> > trSignals2;
    trSignals2.append(em);
    trSignals2.append(em);
    trSignals2.append(em);
    trSignals2.append(em);

    trSignals2[2].append(Signal(1, x));
    trSignals2[2].append(Signal(1, _y));

    QList<Signal> init2;

    ActiveTile * t2 = new ActiveTile(acLabels2, inLabels2, acSignals2, trSignals2, init2,2);

    QList<QList<int> > acLabels3;
    acLabels3.append(empty);
    acLabels3.append(empty);
    acLabels3.append(empty);
    acLabels3.append(empty);

    acLabels3[0].append(1);
    acLabels3[1].append(1);
    acLabels3[2].append(3);
    acLabels3[3].append(1);

    QList<QList<int> > inLabels3;
    inLabels3.append(empty);
    inLabels3.append(empty);
    inLabels3.append(empty);
    inLabels3.append(empty);

    QList<QList<Signal> > acSignals3;
    acSignals3.append(em);
    acSignals3.append(em);
    acSignals3.append(em);
    acSignals3.append(em);

    QList<QList<Signal> > trSignals3;
    trSignals3.append(em);
    trSignals3.append(em);
    trSignals3.append(em);
    trSignals3.append(em);

    trSignals2[2].append(Signal(4, x));

    QList<Signal> init3;
    init3.append(Signal(4, _x));

    ActiveTile * t3 = new ActiveTile(acLabels3, inLabels3, acSignals3, trSignals3, init3,3);
/*
    acLabels[0].clear();
    acLabels[0].append(3);
    acLabels[1].clear();
    acLabels[1].append(3);
    acLabels[2].clear();
    acLabels[2].append(3);
    acLabels[2].append(-2);
    acLabels[3].clear();
    acLabels[3].append(3);

    inLabels[0].clear();
    inLabels[0].append(3);

    acSignals[2].clear();
    acSignals[2].append(Signal(3, x));

    trSignals[2].clear();
    trSignals[2].append(Signal(4, x));
    trSignals[2].append(Signal(2, _y));

    qDebug()<<"Creating Active tile t2";
    ActiveTile t2(acLabels, inLabels, acSignals, trSignals, init,2);

    acLabels[0].clear();
    acLabels[0].append(3);
    acLabels[1].clear();
    acLabels[1].append(3);
    acLabels[2].clear();
    acLabels[2].append(-3);
    acLabels[3].clear();
    acLabels[3].append(3);

    inLabels[0].clear();


    acSignals[2].clear();

    trSignals[2].clear();
    trSignals[2].append(Signal(4, x));

    init.append(Signal(4, _x));

    qDebug()<<"Creating Active tile t3";
    ActiveTile t3(acLabels, inLabels, acSignals, trSignals, init,3);*/
qDebug()<<"Generating Assembly Tiles";
    AssemblyTile* T0 = new AssemblyTile(t0, StrengthFunction);
    AssemblyTile* T1 = new AssemblyTile(t1, StrengthFunction);
    AssemblyTile* T2 = new AssemblyTile(t2, StrengthFunction);
    AssemblyTile* T3 = new AssemblyTile(t3, StrengthFunction);
    //AssemblyTile T2(&t2);
    //AssemblyTile T3(&t3);
qDebug()<<"Adding Assembly tiles to the set";
    simulationSet->addAssemblyTile(T0);
    simulationSet->addAssemblyTile(T1);
    simulationSet->addAssemblyTile(T2);
    simulationSet->addAssemblyTile(T3);
    //simulationSet->addAssemblyTile(T2);
    //simulationSet->addAssemblyTile(T3);
    qDebug()<<"Creating simulator";

    Simulator sim(simulationSet, StrengthFunction, theta, steps);

    sim.initialize();

    sim.startSimulation();



qDebug()<<"DOOOOONNNNNEEEEEEEE!!!!!!!!!!!!!!!!!!!";
#endif

#ifdef TEST2
    int theta = 1;
    int steps = 20;
    QMap<int, int> StrengthFunction;
    /*
     1 - black
     2 - green
     3 - purple
     4 - pink
     */
    qDebug()<<"Setting up a strength function";
    StrengthFunction[1] = 0;
    for(int i = 2; i < 5; i++)
    {
        StrengthFunction[i] = 1;
        StrengthFunction[-i] = 1;
    }

    SetOfAssemblyTiles *simulationSet = new SetOfAssemblyTiles;

    QList<int> side0;
    side0.append(1);
    QList<int> side1;
    side1.append(1);
    QList<int> side2;
    QList<int> side3;
    side3.append(2);
    QList<QList<int> > acLabels;
    acLabels.append(side0);
    acLabels.append(side1);
    acLabels.append(side2);
    acLabels.append(side3);

    QList<int> empty;
    QList<QList<int> > inLabels;
    inLabels.append(empty);
    inLabels.append(empty);
    inLabels.append(empty);
    inLabels[2].append(4);
    inLabels.append(empty);

    QList<Signal> em;
    QList<QList<Signal> > acSignals;
    acSignals.append(em);
    acSignals.append(em);
    acSignals.append(em);
    acSignals.append(em);
    acSignals[3].append(Signal(4, _x));

    QList<QList<Signal> > trSignals;
    trSignals.append(em);
    trSignals.append(em);
    trSignals.append(em);
    trSignals.append(em);

    QList<Signal> init;
    init.append(Signal(4, _y));

qDebug()<<"Creating Active tile t0";
    ActiveTile *t0 = new ActiveTile(acLabels, inLabels, acSignals, trSignals, init,0);

    QList<QList<int> > acLabels1;
    QList<int> side01;
    side01.append(1);
    acLabels1.append(side01);
    QList<int> side11;
    side11.append(-2);
    acLabels1.append(side11);
    QList<int> side21;
    acLabels1.append(side21);
    QList<int> side31;
    side31.append(1);
    acLabels1.append(side31);

    QList<QList<int> > inLabels1;
    QList<int> empty1;
    inLabels1.append(empty1);
    inLabels1.append(empty1);
    inLabels1.append(empty1);
    inLabels1[2].append(4);
    inLabels1.append(empty1);


    QList<QList<Signal> > acSignals1;
    acSignals1.append(em);
    acSignals1.append(em);
    acSignals1[1].append(Signal(4, _x));
    acSignals1.append(em);
    acSignals1.append(em);

    QList<QList<Signal> > trSignals1;
    trSignals1.append(em);
    trSignals1.append(em);
    trSignals1.append(em);
    trSignals1.append(em);



    QList<Signal> init1;
    init1.append(Signal(4, y));


qDebug()<<"Creating Active tile t1";
    ActiveTile * t1 = new ActiveTile(acLabels1, inLabels1, acSignals1, trSignals1, init1,1);

    QList<QList<int> > acLabels2;
    acLabels2.append(empty);
    acLabels2.append(empty);
    acLabels2.append(empty);
    acLabels2.append(empty);

    acLabels2[1].append(1);
    acLabels2[2].append(1);
    acLabels2[3].append(3);

    QList<QList<int> > inLabels2;
    inLabels2.append(empty);
    inLabels2.append(empty);
    inLabels2.append(empty);
    inLabels2.append(empty);

    inLabels2[0].append(-4);

    QList<QList<Signal> > acSignals2;
    acSignals2.append(em);
    acSignals2.append(em);
    acSignals2.append(em);
    acSignals2.append(em);

    acSignals2[3].append(Signal(-4, x));

    QList<QList<Signal> > trSignals2;
    trSignals2.append(em);
    trSignals2.append(em);
    trSignals2.append(em);
    trSignals2.append(em);

    QList<Signal> init2;

    init2.append(Signal(-4, _y));

    ActiveTile * t2 = new ActiveTile(acLabels2, inLabels2, acSignals2, trSignals2, init2,2);

    QList<QList<int> > acLabels3;
    acLabels3.append(empty);
    acLabels3.append(empty);
    acLabels3.append(empty);
    acLabels3.append(empty);

    acLabels3[1].append(-3);
    acLabels3[2].append(1);
    acLabels3[3].append(1);

    QList<QList<int> > inLabels3;
    inLabels3.append(empty);
    inLabels3.append(empty);
    inLabels3.append(empty);
    inLabels3.append(empty);

    inLabels3[0].append(-4);

    QList<QList<Signal> > acSignals3;
    acSignals3.append(em);
    acSignals3.append(em);
    acSignals3.append(em);
    acSignals3.append(em);

    acSignals3[1].append(Signal(-4, x));

    QList<QList<Signal> > trSignals3;
    trSignals3.append(em);
    trSignals3.append(em);
    trSignals3.append(em);
    trSignals3.append(em);


    QList<Signal> init3;
    init3.append(Signal(-4, y));

    ActiveTile * t3 = new ActiveTile(acLabels3, inLabels3, acSignals3, trSignals3, init3,3);
/*
    acLabels[0].clear();
    acLabels[0].append(3);
    acLabels[1].clear();
    acLabels[1].append(3);
    acLabels[2].clear();
    acLabels[2].append(3);
    acLabels[2].append(-2);
    acLabels[3].clear();
    acLabels[3].append(3);

    inLabels[0].clear();
    inLabels[0].append(3);

    acSignals[2].clear();
    acSignals[2].append(Signal(3, x));

    trSignals[2].clear();
    trSignals[2].append(Signal(4, x));
    trSignals[2].append(Signal(2, _y));

    qDebug()<<"Creating Active tile t2";
    ActiveTile t2(acLabels, inLabels, acSignals, trSignals, init,2);

    acLabels[0].clear();
    acLabels[0].append(3);
    acLabels[1].clear();
    acLabels[1].append(3);
    acLabels[2].clear();
    acLabels[2].append(-3);
    acLabels[3].clear();
    acLabels[3].append(3);

    inLabels[0].clear();


    acSignals[2].clear();

    trSignals[2].clear();
    trSignals[2].append(Signal(4, x));

    init.append(Signal(4, _x));

    qDebug()<<"Creating Active tile t3";
    ActiveTile t3(acLabels, inLabels, acSignals, trSignals, init,3);*/
qDebug()<<"Generating Assembly Tiles";
    AssemblyTile* T0 = new AssemblyTile(t0, StrengthFunction);
    AssemblyTile* T1 = new AssemblyTile(t1, StrengthFunction);
    AssemblyTile* T2 = new AssemblyTile(t2, StrengthFunction);
    AssemblyTile* T3 = new AssemblyTile(t3, StrengthFunction);
    //AssemblyTile T2(&t2);
    //AssemblyTile T3(&t3);
qDebug()<<"Adding Assembly tiles to the set";
    simulationSet->addAssemblyTile(T0);
    simulationSet->addAssemblyTile(T1);
    simulationSet->addAssemblyTile(T2);
    simulationSet->addAssemblyTile(T3);
    //simulationSet->addAssemblyTile(T2);
    //simulationSet->addAssemblyTile(T3);
    qDebug()<<"Creating simulator";

    Simulator sim(simulationSet, StrengthFunction, theta, steps);

    sim.initialize();

    sim.startSimulation();


    //delete simulationSet;
qDebug()<<"DOOOOONNNNNEEEEEEEE!!!!!!!!!!!!!!!!!!!";
#endif

#ifdef TEST3

    int theta = 2;
    int steps = 20;
    QMap<int, int> StrengthFunction;
    QMap<int, QColor> ColorMap;
/*
 1 - black
 2 - green
 3 - purple
 4 - pink
 */
    qDebug()<<"Setting up a strength function";

    for(int i = 1; i < 9; i++)
    {
        StrengthFunction[i] = 1;
        StrengthFunction[-i] = 1;
    }

    StrengthFunction[1] = 2;
    StrengthFunction[-1] = 2;
    StrengthFunction[2] = 2;
    StrengthFunction[-2] = 2;
    StrengthFunction[3] = 2;
    StrengthFunction[-3] = 2;
    StrengthFunction[4] = 2;
    StrengthFunction[-4] = 2;
    StrengthFunction[5] = 2;
    StrengthFunction[-5] = 2;
    StrengthFunction[6] = 2;
    StrengthFunction[-6] = 2;

    SetOfAssemblyTiles *simulationSet = new SetOfAssemblyTiles;


    QList<int> empty;
    QList<Signal> em;

    QList<QList<int> > acLabels0;
    acLabels0.append(empty);
    acLabels0.append(empty);
    acLabels0.append(empty);
    acLabels0.append(empty);

    acLabels0[0].append(1);

    QList<QList<int> > inLabels0;
    inLabels0.append(empty);
    inLabels0.append(empty);
    inLabels0.append(empty);
    inLabels0.append(empty);

    QList<QList<Signal> > acSignals0;
    acSignals0.append(em);
    acSignals0.append(em);
    acSignals0.append(em);
    acSignals0.append(em);

    QList<QList<Signal> > trSignals0;
    trSignals0.append(em);
    trSignals0.append(em);
    trSignals0.append(em);
    trSignals0.append(em);

    QList<Signal> init0;
    init0.append(Signal(8, x));

    ActiveTile * t0 = new ActiveTile(acLabels0, inLabels0, acSignals0, trSignals0, init0,0);

    QList<QList<int> > acLabels1;
    acLabels1.append(empty);
    acLabels1.append(empty);
    acLabels1.append(empty);
    acLabels1.append(empty);

    acLabels1[2].append(-1);
    acLabels1[0].append(2);

    QList<QList<int> > inLabels1;
    inLabels1.append(empty);
    inLabels1.append(empty);
    inLabels1.append(empty);
    inLabels1.append(empty);

    inLabels1[3].append(7);

    QList<QList<Signal> > acSignals1;
    acSignals1.append(em);
    acSignals1.append(em);
    acSignals1.append(em);
    acSignals1.append(em);

    acSignals1[0].append(Signal(7, _y));

    QList<QList<Signal> > trSignals1;
    trSignals1.append(em);
    trSignals1.append(em);
    trSignals1.append(em);
    trSignals1.append(em);

    trSignals1[2].append(Signal(8, x));

    QList<Signal> init1;

    ActiveTile * t1 = new ActiveTile(acLabels1, inLabels1, acSignals1, trSignals1, init1, 1);

    QList<QList<int> > acLabels2;
    acLabels2.append(empty);
    acLabels2.append(empty);
    acLabels2.append(empty);
    acLabels2.append(empty);

    acLabels2[2].append(-2);
    acLabels2[0].append(3);

    QList<QList<int> > inLabels2;
    inLabels2.append(empty);
    inLabels2.append(empty);
    inLabels2.append(empty);
    inLabels2.append(empty);

    QList<QList<Signal> > acSignals2;
    acSignals2.append(em);
    acSignals2.append(em);
    acSignals2.append(em);
    acSignals2.append(em);

    QList<QList<Signal> > trSignals2;
    trSignals2.append(em);
    trSignals2.append(em);
    trSignals2.append(em);
    trSignals2.append(em);

    trSignals2[2].append(Signal(8, x));
    trSignals2[0].append(Signal(7, _x));

    QList<Signal> init2;

    ActiveTile * t2 = new ActiveTile(acLabels2, inLabels2, acSignals2, trSignals2, init2, 2);

    QList<QList<int> > acLabels3;
    acLabels3.append(empty);
    acLabels3.append(empty);
    acLabels3.append(empty);
    acLabels3.append(empty);

    acLabels3[2].append(-3);

    QList<QList<int> > inLabels3;
    inLabels3.append(empty);
    inLabels3.append(empty);
    inLabels3.append(empty);
    inLabels3.append(empty);

    inLabels3[3].append(8);

    QList<QList<Signal> > acSignals3;
    acSignals3.append(em);
    acSignals3.append(em);
    acSignals3.append(em);
    acSignals3.append(em);

    acSignals3[2].append(Signal(8, _y));

    QList<QList<Signal> > trSignals3;
    trSignals3.append(em);
    trSignals3.append(em);
    trSignals3.append(em);
    trSignals3.append(em);


    QList<Signal> init3;

    init3.append(Signal(7, _x));

    ActiveTile * t3 = new ActiveTile(acLabels3, inLabels3, acSignals3, trSignals3, init3, 3);

    QList<QList<int> > acLabels4;
    acLabels4.append(empty);
    acLabels4.append(empty);
    acLabels4.append(empty);
    acLabels4.append(empty);

    acLabels4[0].append(4);

    QList<QList<int> > inLabels4;
    inLabels4.append(empty);
    inLabels4.append(empty);
    inLabels4.append(empty);
    inLabels4.append(empty);

    inLabels4[1].append(-7);

    QList<QList<Signal> > acSignals4;
    acSignals4.append(em);
    acSignals4.append(em);
    acSignals4.append(em);
    acSignals4.append(em);

    acSignals4[0].append(Signal(-7, y));

    QList<QList<Signal> > trSignals4;
    trSignals4.append(em);
    trSignals4.append(em);
    trSignals4.append(em);
    trSignals4.append(em);


    QList<Signal> init4;

    init4.append(Signal(-8, x));

    ActiveTile * t4 = new ActiveTile(acLabels4, inLabels4, acSignals4, trSignals4, init4, 4);

    QList<QList<int> > acLabels5;
    acLabels5.append(empty);
    acLabels5.append(empty);
    acLabels5.append(empty);
    acLabels5.append(empty);

    acLabels5[0].append(5);
    acLabels5[2].append(-4);

    QList<QList<int> > inLabels5;
    inLabels5.append(empty);
    inLabels5.append(empty);
    inLabels5.append(empty);
    inLabels5.append(empty);


    QList<QList<Signal> > acSignals5;
    acSignals5.append(em);
    acSignals5.append(em);
    acSignals5.append(em);
    acSignals5.append(em);

    QList<QList<Signal> > trSignals5;
    trSignals5.append(em);
    trSignals5.append(em);
    trSignals5.append(em);
    trSignals5.append(em);

    trSignals5[0].append(Signal(7, _x));
    trSignals5[2].append(Signal(-8, x));

    QList<Signal> init5;

    ActiveTile * t5 = new ActiveTile(acLabels5, inLabels5, acSignals5, trSignals5, init5, 5);

    QList<QList<int> > acLabels6;
    acLabels6.append(empty);
    acLabels6.append(empty);
    acLabels6.append(empty);
    acLabels6.append(empty);

    acLabels6[0].append(6);
    acLabels6[2].append(-5);

    QList<QList<int> > inLabels6;
    inLabels6.append(empty);
    inLabels6.append(empty);
    inLabels6.append(empty);
    inLabels6.append(empty);

    inLabels6[1].append(-8);

    QList<QList<Signal> > acSignals6;
    acSignals6.append(em);
    acSignals6.append(em);
    acSignals6.append(em);
    acSignals6.append(em);

    acSignals6[2].append(Signal(8, y));

    QList<QList<Signal> > trSignals6;
    trSignals6.append(em);
    trSignals6.append(em);
    trSignals6.append(em);
    trSignals6.append(em);

    trSignals6[0].append(Signal(7, _x));

    QList<Signal> init6;

    ActiveTile * t6 = new ActiveTile(acLabels6, inLabels6, acSignals6, trSignals6, init6, 6);

    QList<QList<int> > acLabels7;
    acLabels7.append(empty);
    acLabels7.append(empty);
    acLabels7.append(empty);
    acLabels7.append(empty);

    acLabels7[2].append(-6);

    QList<QList<int> > inLabels7;
    inLabels7.append(empty);
    inLabels7.append(empty);
    inLabels7.append(empty);
    inLabels7.append(empty);

    QList<QList<Signal> > acSignals7;
    acSignals7.append(em);
    acSignals7.append(em);
    acSignals7.append(em);
    acSignals7.append(em);

    QList<QList<Signal> > trSignals7;
    trSignals7.append(em);
    trSignals7.append(em);
    trSignals7.append(em);
    trSignals7.append(em);

    QList<Signal> init7;

    init7.append(Signal(7, _x));

    ActiveTile * t7 = new ActiveTile(acLabels7, inLabels7, acSignals7, trSignals7, init7, 7);

    AssemblyTile* T0 = new AssemblyTile(t0, StrengthFunction);
    AssemblyTile* T1 = new AssemblyTile(t1, StrengthFunction);
    AssemblyTile* T2 = new AssemblyTile(t2, StrengthFunction);
    AssemblyTile* T3 = new AssemblyTile(t3, StrengthFunction);
    AssemblyTile* T4 = new AssemblyTile(t4, StrengthFunction);
    AssemblyTile* T5 = new AssemblyTile(t5, StrengthFunction);
    AssemblyTile* T6 = new AssemblyTile(t6, StrengthFunction);
    AssemblyTile* T7 = new AssemblyTile(t7, StrengthFunction);
    //AssemblyTile T2(&t2);
    //AssemblyTile T3(&t3);
qDebug()<<"Adding Assembly tiles to the set";
    simulationSet->addAssemblyTile(T0);
    simulationSet->addAssemblyTile(T1);
    simulationSet->addAssemblyTile(T2);
    simulationSet->addAssemblyTile(T3);
    simulationSet->addAssemblyTile(T4);
    simulationSet->addAssemblyTile(T5);
    simulationSet->addAssemblyTile(T6);
    simulationSet->addAssemblyTile(T7);

    qDebug()<<"Creating simulator";

    Simulator sim(simulationSet, StrengthFunction, theta, steps, ColorMap);

    sim.initialize();

    sim.startSimulation();



qDebug()<<"DOOOOONNNNNEEEEEEEE!!!!!!!!!!!!!!!!!!!";

#endif
    return a.exec();
}
