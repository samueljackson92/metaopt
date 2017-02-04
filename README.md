# Optima 

[![Build Status](https://travis-ci.org/samueljackson92/optima.svg?branch=master)](https://travis-ci.org/samueljackson92/optima)

## Build Instructions

First install [Eigen](http://eigen.tuxfamily.org/index.php?title=Main_Page) to 
your system and a C++11 compatible compiler. Currently only tested with gcc >=
4.9 and clang >= 3.6 on Ubuntu and OSX.

Then run the following:

```bash
git clone git@github.com:samueljackson92/optima.git
git submodule update --init
cd metaopt
mkdir build && cd build
cmake ..
cmake --build .
```
