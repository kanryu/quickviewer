#ifndef QV_INIT_H
#define QV_INIT_H

#include <QtCore>

#define APP_ORGANIZATION "KATO Kanryu(k.kanryu@gmail.com)"
#define APP_COPYRIGHT    "Copyright 2017 KATO Kanryu"
#define QV_APPNAME "QuickViewer"
#define QV_THUMBNAILS "thumbnail.sqlite3.db"

#ifdef Q_OS_WIN
#define CONFIG_SUBDIR "config"
#define APP_INI "quickviewer.ini"
#define PROGRESS_INI "progress.ini"
#define LINEFEED "\r\n"
#else
#define QV_DATADIR ".quickviewer"
#define APP_INI QV_DATADIR "/quickviewer.ini"
#define PROGRESS_INI ".quickviewer/progress.ini"
#define LINEFEED "\n"
#endif
#define TURBO_JPEG_FMT "turbojpeg"

#define QV_STATUSBAR_FORMAT     "%p (%n)[%s(%m)] %f %2| %p [%s(%m)] %f"
#define QV_WINDOWTITLE_FORMAT   "%v"



class qvEnums : public QObject
{
    Q_OBJECT
public:
    qvEnums(QObject* parent):QObject(parent) {}

    enum ShaderEffect {
        UnPrepared,
        CpuBicubic,
        CpuSpline16,
        CpuSpline36,
        CpuLanczos3,
        CpuLanczos4,

        UsingFixedShader,
        NearestNeighbor,
        Bilinear,

        UsingCpuResizer,
        BilinearAndCpuBicubic,
        BilinearAndCpuSpline16,
        BilinearAndCpuSpline36,
        BilinearAndCpuLanczos,

        UsingSomeShader,
#ifndef QV_WITHOUT_OPENGL
        Bicubic,
        Lanczos
#endif
    };
    Q_ENUM(ShaderEffect)

    enum CatalogViewMode {
        List,
        Icon,
        IconNoText,
    };
    Q_ENUM(CatalogViewMode)

    enum FolderViewSort {
        OrderByName,
        OrderByUpdatedAt,
    };
    Q_ENUM(FolderViewSort)

    enum ToolbarIconSize {
		NormalIcon = 24,
		LargeIcon = 32,
		Large2Icon = 40,
	};
    Q_ENUM(ToolbarIconSize)

    enum FitMode {
        NoFitting,
        FitToRect,
        FitToWidth
    };
    Q_ENUM(FitMode)

    enum OptionViewOnStartup {
        NoViewStartup,
        FolderStartup,
        CatalogStartup,
        RetouchStartup,
//        ExifStartup,
    };
    Q_ENUM(OptionViewOnStartup)

    enum ImageSortBy {
        SortByFileName,
        SortByFileNameDescending,
        SortByFileSize,
        SortByFileSizeDescending,
        SortByModifiedTime,
        SortByModifiedTimeDescending,
    };
    Q_ENUM(ImageSortBy)
};






#endif // QV_INIT_H
