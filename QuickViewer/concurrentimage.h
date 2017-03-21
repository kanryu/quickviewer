#ifndef CONCURRENTIMAGE_H
#define CONCURRENTIMAGE_H

#include <QImage>
#include <QtConcurrentRun>
#include "filevolume.h"

class ConcurrentImage : public QObject
{
    Q_OBJECT
public:
    typedef QVector<QImage> result_type;
    explicit ConcurrentImage(QObject *parent, IFileVolume* filevolume);

    QFuture<result_type> loadConcurrent(QStringList paths);

signals:

public slots:
private:
    IFileVolume* m_filevolume;
};

#endif // CONCURRENTIMAGE_H
