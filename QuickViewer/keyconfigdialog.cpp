#include "keyconfigdialog.h"
#include <QKeySequence>
//#include "ui_keyconfigdialog.h"
#include "ui_exifdialog.h"

KeyConfigDialog::KeyConfigDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExifDialog)
{
    ui->setupUi(this);

    setWindowTitle(tr("Keybord Input Configuration"));

    QStringList tags;
//    tags << QString("<dt>%1</dt><dd>%2</dd>").arg("Make").arg(QString::fromStdString(info.Make));
//    tags << QString("<dt>%1</dt><dd>%2</dd>").arg("Model").arg(QString::fromStdString(info.Model));
//    QString text = QString("<dl>%1</dl>").arg(tags.join(""));
    QString linefmt = "<tr><th>%1</th><td>%2</td><td>%3</td></tr>";

    tags << linefmt.arg(tr("Next Page")).arg(tr("Right")).arg("");
    tags << linefmt.arg("").arg(tr("Space")).arg("");
    tags << linefmt.arg(tr("Prev Page")).arg(tr("Left")).arg("");
    tags << linefmt.arg(tr("First Page")).arg(tr("Home")).arg("");
    tags << linefmt.arg(tr("Last Page")).arg(tr("End")).arg("");
    tags << linefmt.arg(tr("Next Volume")).arg(tr("Page Down")).arg(tr("open a folder/archive of neigibher"));
    tags << linefmt.arg(tr("Prev Volume")).arg(tr("Page Up")).arg(tr("open a folder/archive of neigibher"));
    tags << linefmt.arg(tr("Toggle Fullscreen")).arg(tr("F11")).arg("");
    tags << linefmt.arg("").arg(tr("Return")).arg("");
    tags << linefmt.arg("").arg(tr("Enter")).arg("");
    tags << linefmt.arg(tr("Exit Fullscreen")).arg(tr("ESC")).arg(tr("on Fullscreen only"));
    tags << linefmt.arg(tr("Exit Application")).arg(tr("ESC")).arg(tr("not on Fullscreen only"));
    tags << linefmt.arg(tr("Fitting")).arg(tr("F12")).arg("");
    tags << linefmt.arg("").arg(tr("Asterisk(*)")).arg("");
    tags << linefmt.arg(tr("Scale Up")).arg(tr("Plus(+)")).arg("");
    tags << linefmt.arg(tr("Scale Out")).arg(tr("Minus(-)")).arg("");


    QString text = QString("<style>th {text-align: right;padding-right: 10px;} </style><table>%1</table>").arg(tags.join(""));

    ui->textEdit->setAcceptRichText(true);
    ui->textEdit->setText(text);


}

KeyConfigDialog::~KeyConfigDialog()
{
    delete ui;
}
