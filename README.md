[![Build Status](https://travis-ci.org/Markoprolo/BackTest.svg?branch=master)](https://travis-ci.org/Markoprolo/BackTest)

Test trading strategies with historical data.

## Overview
BackTest allows you to write your own algorithm and test it on historical stock data. Currently
stock data must be downloaded manually from yahoo finance. e.g. MSFT historical data can be downloaded
here [MSFT][].
To use your own stock data you can derive from the dataprovider class.

![Alt text](screenshots/MSFT_enlarged.png?raw=true)

![Alt text](screenshots/MSFT_full_plot.png?raw=true)

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