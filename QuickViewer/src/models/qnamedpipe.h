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
 * and the server will call parseCommand() without any reply.
 *
 * In Microsoft Windows it is implemented with NamedPipe.
 * On Unix it will be implemented by pipe file created on / tmp.
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
     * @brief sendMessage is a method for sending bytes to the server side as a client
     * @param bytes
     */
    void sendMessage(QByteArray bytes);
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
     * @brief parseCommand
     * @param bytes
     * parseCommand interprets the message sent from the client and emits the appropriate SINGAL.
     * You may inherit and overwrite it
     */
    virtual void parseCommand(QByteArray bytes);

signals:
    /**
     * @brief open
     * SIGNAL to open the file specified by path.
     * The message to be sent is simply the full path of the UTF-8 encoded file.
     */
    void open(QString path);
    /**
     * @brief beetUp
     * SIGNAL indicating that the application window should be active.
     */
    void beetUp();

private:
    QNamedPipePrivate* d;
};

#endif // QNAMEDPIPE_H
