This is a an updated version of [mEngine](http://library.wolfram.com/infocenter/Demos/4821/ mEngine) developed by Robert Zhang, making it compatible with Mathematica 8 and Matlab R2011b. So far, it has been built and tested only under OS X 10.7

The following changes and additions have been made to the original code:

* It is now possible to build mEngine with CMake
    - A low level MathLink (mEngineLowLevel) is build and wrapped in a shell script (mEngine) that can be adjusted to take for providing paths to Matlab libraries etc. (following this [procedure](http://stackoverflow.com/questions/8326258/install-mathlink-program-with-arbitrary-path-environment stackoverflow))
    - Eventually, you'll have to adjust the CMakeLists.txt file to provide Matlab's lib and include paths as  CMake's Matlab package seems to be broken (on the other hand [FindMathematica](https://github.com/sakra/FindMathematica) does an awesome job in finding all necessary paths)
* The dimension argument of MLPutRealArray has been updated to type long
* The new Matlab type [mwSize](http://www.mathworks.com/help/techdoc/apiref/mwsize.html) has been introduced (necessary for 64 bit compatibility)
* The external variable Eng is now provided in Eng.h and Eng.c (following this [procedure](http://stackoverflow.com/questions/875655/linking-extern-variables-in-c))

