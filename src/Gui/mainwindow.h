#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"
#include "eventloop.h"

class MarketEvent;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setupCandleStickGraph(QCustomPlot *customPlot);

public slots:
    void ProcessMarketEvent(const MarketEvent& marketEvent);

private slots:
    void Run();

private:
    Ui::MainWindow *ui;
    QDateTime start;
    EventLoop eventLoop;
    QCPFinancial *candlesticks;
    double binSize = 3600*24; // bin data in 1 day intervals
};

#endif // MAINWINDOW_H