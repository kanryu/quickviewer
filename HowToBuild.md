## Set Up Qt SDK
You should install Qt SDK on your pc.

https://www.qt.io/download-open-source/

## Set up the source

Clone the repo and submodules

```
$ git clone https://github.com/kanryu/quickviewer
#
$ cd quickviewer
$ git submodule init
#
$ git submodule update
```

## Make a project to build

### for QtCreator

QuickViewer is developed with QtCreator.
So you just need to have QtCreator load the pro file.

If you has setuped Qt SDK as 'msvc2015' or 'msvc2015_64', the distribution package is automatically generated. By running "jom install".

You can custom build step. Edit the Release build, add new build step, enter 'install' into 'Argument of Make'.

If you has setuped Qt SDK as 'mingw53_32'. Also you can build.
Since there is no script of the distribution package, I want you to create it yourself.

### for command line builders

```
$ cd ../
$ mkdir build
$ cd build
$ [QTSDK]/bin/qmake -o Makefile -recursive ../quickviewer/QVProject.pro
```
Your QtSDK and Makefile for the compiler are built to build QuickViewer. All you have to do is build it with that Makefile.

Please note that if you use VisualStudio2015, you need nmake instead of MinGW make. Of course there is a distinction x86 / x64.

```
$ nmake install
(created QuickViewer distribution)
$ cd ../QuickViewer-0.8.2-x64
$ [QTSDK]/bin/windelpyqt  --release --compiler-runtime QuickViewer.exe
```

### for Visual Studio 2015

1. select menu [Qt VS Tools] -> [Open Qt Project File(.pro)]
1. open dialog of zlib project
1. select C/++ PreProcessor tab
1. remove "ASMV;ASMINF;" from Definition of PreProcessor
1. build the solution
1. copy from "QuickViewer\Debug\moc_catalogwindow.cpp;Debug\moc_mainwindowforwindows.cpp" to "QuickViewer\Debug\moc_catalogwindow.cpp;Debug"

I think that [Qt VS Tools] has some broken :(
Since VisualStudio can use masm, you can set it to assemble asm files if you have skills. This time it is a procedure to change to a setting not used.



Enjoy! :)
