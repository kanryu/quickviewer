#include "qvmovie.h"

QvMovie::QvMovie(QByteArray bytes, QString format, QObject* parent)
    : QObject(parent)
    , m_format(format)
{
    m_bytes.reset(new QByteArray(bytes));
}

QvMovie::QvMovie(QObject *parent)
    : QObject(parent)
{

}

void QvMovie::load()
{
    m_buffer.reset(new QBuffer(m_bytes.data()));
    m_movie.reset(new QMovie(m_buffer.data(), m_format.toUtf8()));
}
