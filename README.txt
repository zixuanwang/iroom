iroom
=====

You need to install boost, OpenCV, and libcurl to compile the code.

Windows (MS Visual Studio):
    mkdir build
    cd build
    cmake .. -G "Visual Studio 11 Win64" -DCMAKE_PREFIX_PATH:PATH=C:/lib/libcurl-7.29.0
    start iroom.sln 

