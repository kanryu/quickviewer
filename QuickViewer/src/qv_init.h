#ifndef QV_INIT_H
#define QV_INIT_H

#include <QtCore>

#define APP_ORGANIZATION "KATO Kanryu(k.kanryu@gmail.com)"
#define APP_COPYRIGHT    "Copyright 2017 KATO Kanryu"

#ifdef Q_OS_WIN
#define APP_INI "quickviewer.ini"
#define PROGRESS_INI "progress.ini"
#else
#define APP_INI ".quickviewer.ini"
#define PROGRESS_INI ".quickviewer-progress.ini"
#endif
#define TURBO_JPEG_FMT "turbojpeg"

class qvEnums : public QObject
{
    Q_OBJECT
public:
    qvEnums(QObject* parent):QObject(parent) {}

    enum ShaderEffect {
        UnPrepared,
        CpuBicubic,

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

};






#endif // QV_INIT_H
