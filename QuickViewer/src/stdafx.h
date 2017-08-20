#ifndef STDAFX_H
#define STDAFX_H

#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include <QtConcurrent>

#ifndef QV_WITHOUT_OPENGL
#  include <QtOpenGL>
#endif

#ifdef Q_OS_WIN
#include <Windows.h>
#include <mapi.h>
#include <Shellapi.h>
#endif

// local headers
#include "qvapplication.h"
#include "bookprogressmanager.h"
#include "qmousesequence.h"
#include "qnamedpipe.h"
#include "shadermanager.h"
#include "timeorderdcache.h"
#include "fileloader.h"
#include "volumemanager.h"
#include "pagecontent.h"
#include "pagemanager.h"

// qfullscreenframe
#include "qfullscreenframe.h"
#include "qinnerframe.h"

// qlanguageselector
#include "qlanguageselector.h"

// catalog
#include "qc_init.h"
#include "volumeitemmodel.h"
#include "managedatabasedialog.h"
#include "databasesettingdialog.h"
#include "catalogwindow.h"

// folderview
#include "folderitemdelegate.h"
#include "folderitemmodel.h"
#include "foldertreeview.h"
#include "folderwindow.h"

// widgets
#include "flowlayout.h"
#include "pageslider.h"
#include "shortcutbutton.h"

// src
#include "qv_init.h"

#include "keyconfigdialog.h"
#include "mouseconfigdialog.h"
#include "optionsdialog.h"
#include "renamedialog.h"
#include "exifdialog.h"

#include "imageview.h"
#include "mainwindow.h"
#include "mainwindowforwindows.h"

/************************
 * other projects
 ************************/

// fileloader
#include "fileloaderdirectory.h"
#include "fileloadersubdirectory.h"
#include "fileloaderziparchive.h"
#include "fileloader7zarchive.h"
#include "fileloaderrararchive.h"

// qzimg
#include "qzimg.h"

// easyexif
#include "exif.h"

#endif // STDAFX_H
