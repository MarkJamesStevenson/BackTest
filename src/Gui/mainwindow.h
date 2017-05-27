#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"
#include "eventloop.h"
#include <memory>
#include "dataprovider.h"


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

public slots:
    void ProcessMarketEvent(const MarketEvent& marketEvent);

    void UpdateCandlesticks();

    void DisplayErrorMessage(const QString &error);
private slots:
    void Run();

private:
    Ui::MainWindow *ui;
    QCPFinancial *candlesticks;
    QErrorMessage* errorMessage;
    EventLoop* eventLoop = nullptr;
    QThread* workerThread = nullptr;

    void AssignListeners(Broker *broker, PortfolioHandler *portfolio, DataProvider *dataProvider, Strategy *strategy) const;
};

#endif // MAINWINDOW_H
