#ifndef QT7Z_GLOBAL_H
#define QT7Z_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef QT7Z_STATIC

#define QT7ZSHARED_EXPORT

#else

//#if defined(QT7Z_LIBRARY)
//#  define QT7ZSHARED_EXPORT Q_DECL_EXPORT
//#else
//#  define QT7ZSHARED_EXPORT Q_DECL_IMPORT
//#endif

#  define QT7ZSHARED_EXPORT

#endif    // QT7Z_STATIC

#endif // QT7Z_GLOBAL_H
