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

bool FileVolume7zArchive::findImageByIndex(int idx)
{
    if(idx < 0 || idx >= m_filelist.size())
        return false;
    m_cnt = idx;
    m_current = m_filelist[m_cnt];
    return true;
}

bool FileVolume7zArchive::findImageByName(QString name)
{
    for(int i = 0; i < m_filelist.size(); i++) {
        if(name == m_filelist[i]) {
            m_cnt = i;
            m_current = name;
            return true;
        }
    }
    return false;
}

QImage FileVolume7zArchive::loadImageByName(const QString& name)
{
    QImage ret = QImage();
    foreach(const QString& e, m_filelist) {
        if(name == e) {
            m_mutex.lock();
            Qt7zFileInfo info = m_fileinfomap[name];
            QByteArray bytes;
            QBuffer iobuffer(&bytes, this);
            iobuffer.open(QIODevice::WriteOnly);
            bool result = m_reader.extractFile(name, &iobuffer);
            m_mutex.unlock();

            ret.loadFromData(bytes);
            return ret;
        }
    }
    return ret;
}

int FileVolume7zArchive::size()
{
    return m_filelist.size();
}


QString FileVolume7zArchive::currentPath()
{
    return m_current;
}

const QPixmap FileVolume7zArchive::currentImage()
{
    if(m_cachedPath == currentPath()) {
        return m_cachedImage;
    }
    if(!m_currentCache.isFinished())
        m_currentCache.waitForFinished();

    const ImageContent& ic = m_currentCache.result();
    m_cachedImage = ic.Image;
    return m_cachedImage;
}
