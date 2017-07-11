#include "folderitemdelegate.h"
#include "folderwindow.h"
#include "qvapplication.h"

FolderItemDelegate::FolderItemDelegate(QWidget *parent, FolderWindow *folderWindow)
    : QStyledItemDelegate(parent)
    , m_folderWindow(folderWindow)
{

}
#define PROGRESS_WIDTH 100
#define PROGRESS_HEIGHT 10

void FolderItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItem opt = option;
    initStyleOption(&opt, index);

    const QWidget *widget = option.widget;
    QStyle *style = widget ? widget->style() : QApplication::style();

    style->drawControl(QStyle::CE_ItemViewItem, &opt, painter, widget);
    // draw the read progless bar
    do {
        if(!qApp->ShowReadProgress() || index.column()!=0)
            break;
        QString path = QDir::fromNativeSeparators(m_folderWindow->itemPath(index));
        if(!qApp->bookshelfManager()->contains(path))
            break;
        BookProgress book = qApp->bookshelfManager()->at(path);
        QRect rect(option.rect);
        QPoint begin(rect.left()+30, rect.top()+PROGRESS_HEIGHT);
        //        painter->drawLine(begin, QPoint(begin.x()+100, begin.y()));

        int progress = book.Completed ? PROGRESS_WIDTH : book.Current * PROGRESS_WIDTH / book.Pages;
        QBrush brRead(QColor::fromRgb(0x0, 0xff, 0x0, 0x40)), brUnread(QColor::fromRgb(0xff, 0x0, 0x0, 0x40));
        painter->setPen(Qt::PenStyle::NoPen);
        painter->setBrush(brRead);
        painter->drawRect(begin.x(), begin.y(), progress, rect.height()-PROGRESS_HEIGHT-1);
        painter->setBrush(brUnread);
        painter->drawRect(begin.x()+progress, begin.y(), PROGRESS_WIDTH-progress, rect.height()-PROGRESS_HEIGHT-1);
    } while(0);

}
