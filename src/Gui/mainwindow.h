#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"
#include "eventloop.h"

class ErrorMessage;
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

signals:
    void RunLoop();
    void ErrorMessage(const std::string& error);

public slots:
    void ProcessMarketEvent(const MarketEvent& marketEvent);


private slots:
    void Run();

private:
    Ui::MainWindow *ui;
    QCPFinancial *candlesticks;
    QThread* workerThread;
    QErrorMessage* errorMessage;

    void AssignListeners(Broker *broker, PortfolioHandler *portfolio, DataProvider *dataProvider, Strategy *strategy) const;
};

#endif // MAINWINDOW_H
