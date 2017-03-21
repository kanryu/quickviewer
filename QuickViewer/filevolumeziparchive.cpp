#include <QtDebug>
#include "filevolumeziparchive.h"

FileVolumeZipArchive::FileVolumeZipArchive(QObject* parent, QString zippath)
    : IFileVolume(parent)
    , m_reader(zippath)
    , m_zipfilepath(zippath)
{
    m_cnt = 0;
    m_current = "";

    if(!m_reader.exists())
        return;

    foreach(const QZipReader::FileInfo& info, m_reader.fileInfoList()) {
        if(info.isFile)
            m_filelist.append(info.filePath);
    }
    qSort(m_filelist);
    m_current = m_filelist[m_cnt];
}


bool FileVolumeZipArchive::nextFile()
{
    if(m_filelist.size() <= m_cnt+1)
        return false;
    m_current = m_filelist[++m_cnt];
    return true;
}

bool FileVolumeZipArchive::prevFile()
{
    if(m_cnt-1 < 0)
        return false;
    m_current = m_filelist[--m_cnt];
    return true;
}

bool FileVolumeZipArchive::setIndexedFile(int idx)
{
    if(idx < 0 || idx >= m_filelist.size())
        return false;
    m_cnt = idx;
    m_current = m_filelist[m_cnt];
    return true;
}

int FileVolumeZipArchive::size()
{
    return m_filelist.size();
}

QString FileVolumeZipArchive::currentPath()
{
    return m_current;
}

QPixmap FileVolumeZipArchive::currentImage()
{
    if(m_cachedPath == currentPath()) {
        return m_cachedImage;
    }
    QByteArray bytes = m_reader.fileData(currentPath());
    m_cachedImage = QPixmap();
    m_cachedImage.loadFromData(bytes);
//    qDebug() << m_cachedImage << m_cachedImage.size();
    return m_cachedImage;
}
