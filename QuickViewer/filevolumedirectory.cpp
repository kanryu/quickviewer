#include "filevolumedirectory.h"


FileVolumeDirectory::FileVolumeDirectory(QObject* parent, QString dir) : IFileVolume(parent)
{
    m_directory.setPath(dir);
    m_cnt = 0;
    m_current = "";

    if(!m_directory.exists())
        return;

    m_filelist = m_directory.entryList(QDir::Files, QDir::Name);
    m_current = m_filelist[m_cnt];
}


bool FileVolumeDirectory::nextFile()
{
    if(m_filelist.size() <= m_cnt+1)
        return false;
    m_current = m_filelist[++m_cnt];
    return true;
}

bool FileVolumeDirectory::prevFile()
{
    if(m_cnt-1 < 0)
        return false;
    m_current = m_filelist[--m_cnt];
    return true;
}

bool FileVolumeDirectory::findImageByIndex(int idx)
{
    if(idx < 0 || idx >= m_filelist.size())
        return false;
    m_cnt = idx;
    m_current = m_filelist[m_cnt];
    return true;
}

bool FileVolumeDirectory::findImageByName(QString name)
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

QImage FileVolumeDirectory::loadImageByName(const QString& name)
{
    QImage ret = QImage();
    int idx = m_filelist.indexOf(name);
    if(idx >= 0) {
        const QString abso = m_directory.absoluteFilePath(name);

        QFile file(abso);
        bool result = file.open(QIODevice::ReadOnly);
        QByteArray bytes = file.readAll();

        ret.loadFromData(bytes);

        return ret;
    }
    return ret;
}

int FileVolumeDirectory::size()
{
    return m_filelist.size();
}

QString FileVolumeDirectory::currentPath()
{
    return m_directory.absoluteFilePath(m_current);
}

const QPixmap FileVolumeDirectory::currentImage()
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
