#ifndef FILEOPERATOR_H
#define FILEOPERATOR_H

#include <QObject>

/**
 * @brief The FileOperator class
 *
 * Provides operation for the currently displayed image or volume.
 * When Run () of this object is executed, pre-registered copy, move, command execution, etc. are executed.
 * These settings can be serialized to JSON and saved on ini file.
 */
class FileOperator : public QObject
{
    Q_OBJECT
    enum OperateAs
    {
        AsFile,
        AsVolume,
    };
    enum OperateMode
    {
        CopyMode,
        MoveMode,
        CommandMode,
    };

public:
    explicit FileOperator(QString json, QObject *parent = nullptr);
    void Run();
    QVariant toVariant();
signals:

public slots:
private:
    OperateAs m_operateAs;
    OperateMode m_mode;
    QString m_command;
};

#endif // FILEOPERATOR_H
