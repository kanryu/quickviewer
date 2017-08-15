# How to build

Since I was told before that He hadn't known how to build from this source code, I wrote this document.

With GPLv 3, you have copied this source code and the right to build it yourself is guaranteed, so please build it if you are interested in this application.

If you have something you do not recognize or are aware of when building, please send me a email or post to the Issue of the project.

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

Switch to the **Projects** tab and select **Add Build Step** -> **Make**. Type install into **Make arguments:**.

If you has setuped Qt SDK as 'mingw53_32'. Also you can build.
Since there is no script of the distribution package, I want you to create it yourself.

### for command line builders

```
$ cd ../
$ mkdir build
$ cd build
$ [QTSDK]/bin/qmake -spec win32-msvc2015 -o Makefile -recursive ../quickviewer/QVProject.pro
```
The **-spec** option is determined automatically by the setting of QtSDK you installed. For details, to see qmake's manual and **[QtSDK]/src/qtbase/mkspecs**

A Makefile for the compiler will be generated to build QuickViewer. All you have to do is build it with that Makefile.

Please note that if you use VisualStudio2015, you need nmake instead of MinGW make. Of course there is a distinction x86 / x64.

```
$ [amd64]/vsvars64.bat
$ nmake
$ cd QuickViewer
$ nmake install
(created QuickViewer distribution)
```

### for Visual Studio 2015

1. install VisualStudio2015Community, QtSDK(msvc2015 or msvc2015_64), QtVSTools
1. select menu [Qt VS Tools] -> [Open Qt Project File(.pro)]
1. select QVProject.pro
1. open dialog of zlib project
1. select C/C++ PreProcessor tab
1. remove "ASMV;ASMINF;" from Definition of PreProcessor
1. build the solution
1. copy from "QuickViewer\Debug\moc_catalogwindow.cpp;Debug\moc_mainwindowforwindows.cpp" to "QuickViewer\Debug"
1. continue to build

I think that [Qt VS Tools] has some broken :(

Since VisualStudio can use masm, you can set it to assemble asm files if you have skills. This time it is a procedure to change to a setting not used.


## Build directory structure

You can find the directories in the build directry named e.g. *'build-QVproject-Desktop_Qt_5_7_1_MSVC2015_64bit-Debug'* after building completed. (VisualStudio won't make [build])

- bin
- lib
- (each sub projects)

**lib** has static libraries built from each subproject.

**bin** has executable programs built from each subproject.

To test all the functions of QuickViewer, please do the following.

```
$ cd [build]/bin
$ ln -s ../../quickviewer/QuickViewer/database database
$ ln -s ../../quickviewer/QuickViewer/shaders shaders
$ ln -s ../../quickviewer/QuickViewer/translations translations
```

**database** is a SQLite database which contains Catalogs and thumbnails.

**shaders** has Fragment Shaders for image resizing.

**translations** has multi-language qm files.


Enjoy! :)
