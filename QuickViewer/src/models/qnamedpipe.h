#ifndef QNAMEDPIPE_H
#define QNAMEDPIPE_H

#include <QtCore>
class QNamedPipePrivate;

/**
 * @brief The QNamedPipe class
 * QNamedPipe provides simple interprocess communication in local.
 *
 * Your first running process should be a server
 * and the second and subsequent processes should be clients.
 *
 * QNamedPipe automatically creates a thread for the server and waits.
 * It can receive binary messages from other processes.
 *
 * Messages are sent unilaterally from the client,
 * and the server will emit received(bytes) without any reply.
 *
 * In Microsoft Windows it is implemented with NamedPipe.
 * On Unix it is implemented by named pipe created on /tmp.
 */
class QNamedPipe : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief QNamedPipe
     * @param name: of NamedPipe
     * @param valid: If valid is false, QNamedPipe does not perform any operation and all operation results are true
     * @param parent
     */
    explicit QNamedPipe(QString name, bool valid, QObject *parent = nullptr);
    ~QNamedPipe();
    /**
     * @brief send
     * for sending bytes to the server side as a client
     */
    void send(QByteArray bytes);
    /**
     * @brief isServerMode
     * @return if the instanse is a server
     */
    bool isServerMode();
    /**
     * @brief waitAsync
     * Run worker thread and make it stand by as a server.
     * Control returns immediately after execution.
     */
    void waitAsync();
    /**
     * @brief isValid
     * @return if the instance is valid
     */
    bool isValid();
    /**
     * @brief generatePipePath
     * Returns the actual full path of the named pipe depending on the OS
     */
    virtual QString generatePipePath(QString name);

signals:
    /**
     * @brief received
     * SIGNAL which received a byte sequence from pipe.
     * "0" is reserved(for dispose)
     */
    void received(QByteArray bytes);

private:
    QNamedPipePrivate* d;
};

#endif // QNAMEDPIPE_H
