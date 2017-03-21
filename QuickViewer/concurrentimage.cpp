#include "concurrentimage.h"

ConcurrentImage::ConcurrentImage(QObject *parent, IFileVolume* filevolume)
    : QObject(parent)
    , m_filevolume(filevolume)
{

}
