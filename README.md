# MetaOpt

## Build Instructions

First install [Eigen](http://eigen.tuxfamily.org/index.php?title=Main_Page) to your system. Then run the following:

```bash
git clone git@github.com:samueljackson92/metaopt.git
git submodule update --init
cd metaopt
mkdir build && cd build
cmake ..
cmake --build .
```
