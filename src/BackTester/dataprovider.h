#ifndef DATAPROVIDER_H
#define DATAPROVIDER_H


class DataProvider
{
public:
    DataProvider() = default;

    //Do any set-up that is required.
    void Initialise();

    // This function should only be overriden
    // by backtesting data providers to pre-download
    // the required stock data before running.
    virtual void DownloadData() {}

    virtual void UpdateBars() = 0;
};

#endif // DATAPROVIDER_H
