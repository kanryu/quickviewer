#include "filevolume7zarchive.h"


FileVolume7zArchive::FileVolume7zArchive(QObject* parent, QString sevenzippath)
    : IFileVolume(parent)
    , m_reader(sevenzippath)
    , m_7zfilepath(sevenzippath)
{
    m_cnt = 0;
    m_current = "";

    if(!m_reader.open())
        return;

    foreach(const Qt7zFileInfo& info, m_reader.fileInfoList()) {
        if(!info.isDir) {
            m_filelist.append(info.fileName);
            m_fileinfomap[info.fileName] = info;
        }
    }
    m_current = m_filelist[m_cnt];
}


bool FileVolume7zArchive::nextFile()
{
    if(m_filelist.size() <= m_cnt+1)
        return false;
    m_current = m_filelist[++m_cnt];
    return true;
}

bool FileVolume7zArchive::prevFile()
{
    if(m_cnt-1 < 0)
        return false;
    m_current = m_filelist[--m_cnt];
    return true;
}

bool FileVolume7zArchive::setIndexedFile(int idx)
{
    if(idx < 0 || idx >= m_filelist.size())
        return false;
    m_cnt = idx;
    m_current = m_filelist[m_cnt];
    return true;
}

bool FileVolume7zArchive::nextVolume()
{
    return false;
}

bool FileVolume7zArchive::prevVolume()
{
    return false;
}

int FileVolume7zArchive::size()
{
    return m_filelist.size();
}


QString FileVolume7zArchive::currentPath()
{
    return m_current;
}

QImage FileVolume7zArchive::currentImage()
{
    if(m_cachedPath == currentPath()) {
        return m_cachedImage;
    }
    Qt7zFileInfo info = m_fileinfomap[m_current];
    QByteArray bytes;
//    bytes.resize(info.size);
    QBuffer iobuffer(&bytes, this);
    iobuffer.open(QIODevice::WriteOnly);
    bool result = m_reader.extractFile(currentPath(), &iobuffer);
    //QByteArray bytes2 = iobuffer.readAll();
    m_cachedImage = QImage::fromData(bytes);
//    qDebug() << m_cachedImage << m_cachedImage.size();
    return m_cachedImage;
}
