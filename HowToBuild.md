# How to build

Since I was told before that he hadn't known how to build from this source code, so I wrote this document.

With GPLv 3, you have copied this source code and the right to build it yourself is guaranteed, so please build it if you are interested in this application.

If you have something you do not recognize or are aware of when building, please send me a email or post to a issue of the project.

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
So you just need to have QtCreator load the QVProject.pro.

If you has setuped Qt SDK as 'msvc2015' or 'msvc2015_64', the distribution package is automatically generated. By running "jom install".

Switch to the **Projects** tab and select **Add Build Step** -> **Make**. Type install into **Make arguments:**.

If you has setuped Qt SDK as 'mingw53_32'. Also you can build.
Since there is no script of the distribution package, I want you to create it yourself.

### for command line builders

```
$ cd ../
$ mkdir build
$ cd build
$ [QTSDK]/bin/qmake -o Makefile -recursive ../quickviewer/QVProject.pro
```
A Makefile for the compiler will be generated to build QuickViewer. All you have to do is build it with that Makefile.


#### MinGW
```
$ mingw32-make
$ cd QuickViewer
$ mingw32-make install
(created QuickViewer distribution)
```

#### VisualStudio2015

You need nmake instead of MinGW make. Of course there is a distinction x86 / x64.

```
$ [amd64]/vsvars64.bat
$ nmake
$ cd QuickViewer
$ nmake install
(created QuickViewer distribution)
```

### for Visual Studio 2015

Normal project generation methods are as follows:

1. install VisualStudio2015Community, QtSDK(msvc2015 or msvc2015_64), QtVSTools
1. select menu [Qt VS Tools] -> [Open Qt Project File(.pro)]
1. select QVProject.pro

However, I think it would be better to run qmake on the command line. This method is hard to make a mistake.

```
$ cd ../
$ mkdir build
$ cd build
$ [QTSDK]/bin/qmake  -tp vc ..\quickviewer\QVProject.pro -recursive QMAKE_INCDIR_QT=$(QTDIR)\include QMAKE_LIBDIR=$(QTDIR)\lib QMAKE_MOC
=$(QTDIR)\bin\moc.exe QMAKE_QMAKE=$(QTDIR)\bin\qmake.exe
```

1. open dialog of zlib project
1. select C/C++ PreProcessor tab
1. remove "ASMV;ASMINF;" from Definition of PreProcessor
    - if you are building for x64, add *inffast.c* to **Source Files** of zlib
1. build the solution

Since VisualStudio can use masm, you can set it to assemble asm files if you have skills. This time it is a procedure to change to a setting not used.

If you debug the x64 version of QuickViewer, you may encounter an error that QtCored.dll is missing.
In that case, dropping the built QuickViewer.exe onto [QtSDK]/bin/windeployqt.exe copies the required DLLs.

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

## Selection of rendering method

QuickViewer renders images mainly in three ways.

1. Standard rendering method of each OS
   - on Windows, it is Windows GDI
1. OpenGL
1. Direct2D

If you want to use QuickViewer with OpenGL, you need to comment out the **QV_WITHOUT_OPENGL** switch in QuickViewer.pro.

I read a document that Windows GDI doesn't use hardware acceleration in Windows Vista and later, but in bilinear interpolation drawing of 2D graphics, there is no difference from GPU and it is not necessary to transfer it to drawing texture, so it is even faster .

Direct2D is implemented as a QPA plugin, and rendering method is automatically changed when plug-in is enabled at application startup.

Although it has not tried yet, in other OSs it should be possible to change the drawing method by other QPAs.

Enjoy! :)
