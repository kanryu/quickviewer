# How to build

Since I was told before that he hadn't known how to build from this source code, so I wrote this document.

With GPLv 3, you have copied this source code and the right to build it yourself is guaranteed, so please build it if you are interested in this application.

If you have something you do not recognize or are aware of when building, please send me a email or post to a issue of the project.

## 1. Setup

### Set Up Qt SDK
You should install Qt SDK on your pc.

https://www.qt.io/download-open-source/

### Set up the source

Clone the repo and submodules

```
$ git clone https://github.com/kanryu/quickviewer
#
$ cd quickviewer
$ git submodule init
#
$ git submodule update
```

## 2. Make a project to build

Note: For Linux builds, [linuxdeployqt](https://github.com/probonopd/linuxdeployqt) and [appimagetool](https://github.com/AppImage/AppImageKit) are required.

### for QtCreator

QuickViewer is developed with QtCreator.
So you just need to have QtCreator load the QVProject.pro.

If you has setuped Qt SDK as 'msvc2015' or 'msvc2015_64', the distribution package is automatically generated. By running "jom install".

Switch to the **Projects** tab and select **Add Build Step** -> **Make**. Type install into **Make arguments:**.

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
$ mingw32-make install
(created QuickViewer distribution)
```

#### VisualStudio2015

You need nmake instead of MinGW make. Of course there is a distinction x86 / x64.

```
$ [amd64]/vsvars64.bat
$ nmake
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

If you debug the x64 version of QuickViewer, you may encounter an error that QtCored.dll is missing.
In that case, dropping the built QuickViewer.exe onto [QtSDK]/bin/windeployqt.exe copies the required DLLs.

## 3. Directory structure at build time

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

## 4. Directory structure at runtime

### for Windows

- **[database]**
    - SQLite database which contains Catalogs and thumbnails.
- **[shaders]**
    - Fragment Shaders for image resizing.(obsolete)
- **[translations]**
    - multi-language qm files.
- **QuickViewer.exe**
    - Application main
- **AssociateFilesWithQuickViewer.exe**
    - Set the association of image formats with UAC
- **quickviewer.ini**
    - Main configuration file. Includes keyboard and mouse settings
- **progress.ini**
    - Record the last displayed image in volume

### for Linux (AppImage)

Note: For Linux builds, [linuxdeployqt](https://github.com/probonopd/linuxdeployqt) and [appimagetool](https://github.com/AppImage/AppImageKit) are required.

- **[QuickViewer-XXX-AppDir]**
    - Base directory making up AppImage
    - It is extracted on /tmp at runtime
- **[AppDir/usr/bin]**
    - Destination of executable installation
- **[AppDir/usr/lib]**
    - Destination of shared libraries installation
- **[AppDir/translations]**
    - Destination of multi-language qm files, and languages.ini
- **AppDir/QuickViewer.desktop**
    - open desktop configulation
- **$HOME/.quickviewer/quickviewer.ini**
    - Main configuration file. Includes keyboard and mouse settings
- **$HOME/.quickviewer/progress.ini**
    - Record the last displayed image in volume
- **$HOME/.quickviewer/thumbnail.sqlite3.db**
    - SQLite database which contains Catalogs and thumbnails.

**AppDir/usr/bin/qt.conf** is currently not used.

## 5. Selection of rendering method

QuickViewer renders images mainly in three ways.

1. Standard rendering method of each OS
   - on Windows, it is Windows GDI
1. OpenGL
1. Direct2D

If you want to use QuickViewer with OpenGL, you need to comment out the **QV_WITHOUT_OPENGL** switch in QuickViewer.pro.

I read a document that Windows GDI doesn't use hardware acceleration in Windows Vista and later, but in bilinear interpolation drawing of 2D graphics, there is no difference from GPU and it is not necessary to transfer it to drawing texture, so it is even faster .

Direct2D is implemented as a QPA plugin, and rendering method is automatically changed when plug-in is enabled at application startup.

Although it has not tried yet, in other OSs it should be possible to change the drawing method by other QPAs.

## 6. Portable or System Standards

There will be different opinion depending on the person whether an application should be able to boot on any PC from your USB memory or as a part of the PC's system.

In QuickViewer, QV_PORTABLE in QVproject.pri makes it possible to select these two policies.

When QV_PORTABLE is defined, it becomes an application that can copy to USB memory. Would you like to store data files such as ini files and DBs on the same drive as much as possible? For Linux and Mac, they are output as AppImage, dmg respectively.

If not, QuickViewer will be built as an application embedded in the system. On Windows it will be installed in "C:\Program FIles".
On Linux it will be /usr/local/bin. You may load system-specific shared libraries (eg 7z).



Enjoy! :)
