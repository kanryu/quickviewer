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

bool FileVolumeDirectory::setIndexedFile(int idx)
{
    if(idx < 0 || idx >= m_filelist.size())
        return false;
    m_cnt = idx;
    m_current = m_filelist[m_cnt];
    return true;
}

bool FileVolumeDirectory::nextVolume()
{
    return false;
}

bool FileVolumeDirectory::prevVolume()
{
    return false;
}

int FileVolumeDirectory::size()
{
    return m_filelist.size();
}

QString FileVolumeDirectory::currentPath()
{
    return m_directory.absoluteFilePath(m_current);
}

QImage FileVolumeDirectory::currentImage()
{
    if(m_cachedPath == currentPath()) {
        return m_cachedImage;
    }
    return m_cachedImage = QImage(currentPath());
}
