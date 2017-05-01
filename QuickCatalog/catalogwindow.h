#ifndef CATALOGWINDOW_H
#define CATALOGWINDOW_H

#include <QtWidgets>

namespace Ui {
class CatalogWindow;
}

class CatalogWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CatalogWindow(QWidget *parent = 0);
    ~CatalogWindow();

public slots:
    void on_treeItemChanged(QString path);

private:
    Ui::CatalogWindow *ui;
};

#endif // CATALOGWINDOW_H
