[![Build Status](https://travis-ci.org/MarkJamesStevenson/BackTest.svg?branch=master)](https://travis-ci.org/MarkJamesStevenson/BackTest)

Test trading strategies with historical data.

## Overview
BackTest allows you to write your own algorithm and test it on historical stock data. Currently
stock data must be downloaded manually from yahoo finance. e.g. MSFT historical data can be downloaded
here [MSFT][].
To use your own stock data you can derive from the dataprovider class.

To write your own strategy, derive from the strategy class. A basic example is given with the BuyAndHoldStrategy class.

## Example screenshots

A full backtest of MSFT is shown below:
![Alt text](screenshots/MSFT_full_plot.png?raw=true)

You can zoom in on areas of interest:
![Alt text](screenshots/MSFT_enlarged.png?raw=true)

## Dependencies
To build and run BackTest the following dependencies must first be installed:
- Qt5
- libcurl
- C++14 compiler

## How to build
First, you will need an installation of [CMake][]. Once this is done, you can `cd` to the root
of the project and setup the build directory:
```shell
mkdir build
cd build
cmake ..
```

<!-- Links -->
[CMake]: http://www.cmake.org
[MSFT]: https://uk.finance.yahoo.com/quote/MSFT/history?p=MSFT