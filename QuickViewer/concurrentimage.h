#ifndef CONCURRENTIMAGE_H
#define CONCURRENTIMAGE_H

#include <QPixmap>
#include <QtConcurrentRun>
#include "filevolume.h"

class ConcurrentImage : public QObject
{
    Q_OBJECT
public:
    explicit ConcurrentImage(QObject *parent, IFileVolume* filevolume);

    QFuture<QPixmap> loadConcurrent(QStringList paths);

signals:

public slots:
private:
    IFileVolume* m_filevolume;
};

#endif // CONCURRENTIMAGE_H
