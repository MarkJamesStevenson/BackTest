#ifndef DATAPROVIDER_H
#define DATAPROVIDER_H


class DataProvider
{
public:
    DataProvider() = default;

    virtual void UpdateBars() = 0;
};

#endif // DATAPROVIDER_H
