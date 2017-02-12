#include "dataprovider.h"

void DataProvider::Initialise()
{
    //Call the DownloadData function which can
    //be overridden by derived classes.
    DownloadData();
}
