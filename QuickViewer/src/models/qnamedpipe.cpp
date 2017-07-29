#include "qnamedpipe.h"
#include <QtConcurrent>

#ifdef Q_OS_WIN
#include <Windows.h>

#define PIPE_BUFFER_LENGTH 2048

class QNamedPipePrivate
{
public:
    QNamedPipePrivate(QNamedPipe* parent, QString path)
        : m_parent(parent)
        , m_handlepipe(NULL)
        , m_event(NULL)
        , m_serverMode(false)
        , m_willBeClose(false)
    {
        QString pipeBase = "\\\\.\\pipe\\";
        QString pipepath = pipeBase + path;
        std::wstring p = pipepath.toStdWString();
        m_handlepipe = ::CreateNamedPipeW(
                    p.data(),
                    PIPE_ACCESS_DUPLEX | FILE_FLAG_OVERLAPPED,
                    PIPE_TYPE_BYTE,
                    1,
                    PIPE_BUFFER_LENGTH,
                    PIPE_BUFFER_LENGTH,
                    1000,
                    NULL);
        if(m_handlepipe != INVALID_HANDLE_VALUE)
            m_serverMode = true;
        else {
            m_handlepipe = ::CreateFileW(
                        p.data(),
                        GENERIC_READ | GENERIC_WRITE,
                        0, NULL, OPEN_EXISTING, 0, NULL
                        );
        }
    }
    ~QNamedPipePrivate()
    {
        dispose();
    }
    void dispose()
    {
        if(m_handlepipe) {
            m_willBeClose = true;
            if(m_event) {
                HANDLE event = m_event;
                m_event = NULL;
                ::CloseHandle(event);
            }
            m_handlepipe = NULL;
        }
    }

    void sendMessage(QByteArray bytes)
    {
        DWORD dwResult = 0;
        ::WriteFile(m_handlepipe, bytes.data(), (DWORD)bytes.size(), &dwResult, NULL);
        qDebug() << dwResult;
    }
    void waitAsync()
    {
        DWORD dwResult;
        m_event = ::CreateEventW(NULL, FALSE, FALSE, NULL);
        HANDLE handlePipe = m_handlepipe;
        do {
            OVERLAPPED ov = {0};
            ov.hEvent = m_event;
            ::ConnectNamedPipe(handlePipe, &ov);
            dwResult = ::WaitForSingleObject(m_event, 100);
            if(dwResult == 0xFFFFFFFF) {
//                qDebug() << "waitAsync" << dwResult;
                ::CloseHandle(handlePipe);
                return;
            }
            DWORD dwLength = 0;
            if(dwResult == WAIT_OBJECT_0) {
                QByteArray bytes(PIPE_BUFFER_LENGTH, 0);
                ::ReadFile(m_handlepipe, bytes.data(), PIPE_BUFFER_LENGTH, &dwLength, NULL);
                if(dwLength > 0) {
                    bytes.resize(dwLength);
                    m_parent->parseCommand(bytes);
                }
            }
            ::DisconnectNamedPipe(m_handlepipe);
        } while(1);

    }

    HANDLE m_handlepipe;
    HANDLE m_event;
    bool m_serverMode;
    QNamedPipe* m_parent;
    bool m_willBeClose;
};
QNamedPipe::QNamedPipe(QString pipepath, bool valid, QObject *parent)
    : QObject(parent)
    , d(valid ? new QNamedPipePrivate(this, pipepath) : nullptr)
{

}
#else

class QNamedPipePrivate
{
public:
    QNamedPipePrivate();
    void sendMessage(QByteArray bytes) {}
    void waitAsync() {}

    void* m_handlepipe;
    bool m_serverMode;
    QNamedPipe* m_parent;
    bool m_willBeClose;
};

QNamedPipe::QNamedPipe(QString pipepath, bool valid, QObject *parent)
    : QObject(parent)
    , d(nullptr)
{

}
#endif


QNamedPipe::~QNamedPipe()
{
    if(d)
        delete d;
}

void QNamedPipe::sendMessage(QByteArray bytes)
{
    if(d)
        d->sendMessage(bytes);
}

bool QNamedPipe::isServerMode()
{
    return !d || d->m_serverMode;
}

void QNamedPipe::waitAsync()
{
    if(d)
        QtConcurrent::run(d, &QNamedPipePrivate::waitAsync);
}

bool QNamedPipe::isValid()
{
    return !d || d->m_handlepipe != nullptr;
}

void QNamedPipe::parseCommand(QByteArray bytes)
{
    if(bytes.size() == 1) {
        emit beetUp();
    }
    else if(bytes.size() > 0) {
        auto string = QString::fromUtf8(bytes);
        emit open(string);
    }

}
