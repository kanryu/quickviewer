#ifndef FILEASSOCDIALOG_H
#define FILEASSOCDIALOG_H

#include <QtGui>
#if QT_VERSION_MAJOR >= 5
#  include <QtWidgets>
#endif

namespace Ui {
class FileAssocDialog;
}

class AssocInfo
{
public:
    QString Name;
    QString Description;
    QString IconName;
    QStringList Extensions;
};

class FileAssocDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FileAssocDialog(QWidget *parent = 0);
    ~FileAssocDialog();
//    void closeEvent(QCloseEvent *event) override;
    QStringList enumrateFormats();
    void registEntries(QStringList formats);
    void unregistEntries();
    QString getExecuteApplication();
    QString getIconPath(QString iconName);

    static QSettings::Format RegFormat;

public slots:
    void on_allOn_triggered();
    void on_allOff_triggered();
    void on_tryRegist_triggered();

signals:
    void closed();

private:
    Ui::FileAssocDialog *ui;
    QMap<QString, AssocInfo> m_assocs;
    QMap<QString, QCheckBox*> m_assocOfActions;
};

#endif // FILEASSOCDIALOG_H
