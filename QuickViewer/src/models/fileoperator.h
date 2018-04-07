#ifndef FILEOPERATOR_H
#define FILEOPERATOR_H

#include <QObject>

class FileOperator : public QObject
{
    Q_OBJECT
    enum OperateAs
    {
        AsFile,
        AsDirectory,
    };
    enum OperateMode
    {
        CopyMode,
        MoveMode
    };

public:
    explicit FileOperator(QObject *parent = nullptr);
    void Run();
signals:

public slots:
private:
    OperateAs m_operateAs;
    OperateMode m_mode;
};

#endif // FILEOPERATOR_H
