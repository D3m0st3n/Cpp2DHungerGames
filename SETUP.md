# Setup

*** 

Step-by-step set up for my project


### Mac OS

***

Requirements :
    -
    -
    -
    -

1. Setup VS Code
    - Download & install the software
    - Install all necessary extension to run C++ : in particular C++ with IntelliSense
2. Setup Homebrew & external packages
    - Install Homewbrew
    - Download SDL2 library
    - Link library with project in *cpp_properties.json* 
3. Setup CMake
    - Download and install cmake (can be done through Homebrew)
    *Note* : When adding a new external library, do not forget to link it in the CMake file to compile it properly

You should be done for installing all the requirements

Now, go within the project directory and enter build it :


> $ mkdir build
> 
> $ cd build
> 
> $ cmake ..
> 
> $ cmake --build .

The project will be built and compiled.

*Note* : A few warnings will be generated. They stem from the use of *auto* type in some file.  ***Correct this in the future***


### Windows

***


Requirements :
    - MinGW
    - CMake
    - gcc/g++
    - SDL library

1. Install VS Code to edit the code

2. MinGW & C++ compilers
    - Download & install the latest MinGW version
    - Add g++/gcc paths to PATH global environment variables

    External libraries : SDL
    - Download SDL library for MinGW
    - Extract content of the zip file anywhere
    - Copy content of *i686-w64-mingw32* to the MinGW directory
    Your external library should be set up

3. Cmake installation
    - Simply install the latest CMake version
    - Make sure to add the cmake path to PATH environment variables

4. Build the project
    - In the repo directory : 
    
    > $ mkdir build && cd build 
    >
    > $ cmake -DCMAKE_C_COMPILER="/path/to/gcc.exe" -DCMAKE_CXX_COMPILER="/path/to/g++.exe" -G "MinGW Makefiles" ..
    >
    > $ cmake --build .

*Note : compile cmake command  for me, $ cmake -DCMAKE_C_COMPILER="C:/MinGW/bin/gcc.exe" -DCMAKE_CXX_COMPILER="C:/MinGW/bin/g++.exe" -G "MinGW Makefiles" ..*


