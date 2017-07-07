#ifndef MOVIE_H
#define MOVIE_H

#include <QtGui>

class Movie : public QObject
{
    Q_OBJECT
public:
    Movie(QByteArray bytes, QString format, QObject* parent=nullptr);
    Movie(QObject* parent=nullptr);
    Movie(const Movie& rhs)
        : QObject(nullptr)
        , m_movie(rhs.m_movie)
        , m_buffer(rhs.m_buffer)
        , m_bytes(rhs.m_bytes)
        , m_format(rhs.m_format)
    {}
    inline Movie& operator=(const Movie &rhs)
    {
        m_movie = rhs.m_movie;
        m_buffer = rhs.m_buffer;
        m_bytes = rhs.m_bytes;
        m_format = rhs.m_format;
        return *this;
    }
    void load();

    QMovie* data() { return m_movie.data(); }
    bool isNull() { return m_bytes.isNull(); }
    void reset() { m_buffer.data()->reset(); }
private:
    QSharedPointer<QMovie> m_movie;
    QSharedPointer<QBuffer> m_buffer;
    QSharedPointer<QByteArray> m_bytes;
    QString m_format;
};

#endif // MOVIE_H
