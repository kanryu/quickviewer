#include <QLocale>

#include "exifdialog.h"
#include "ui_exifdialog.h"

ExifDialog::ExifDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExifDialog)
{
    ui->setupUi(this);
}

ExifDialog::~ExifDialog()
{
    delete ui;
}

QString ExifDialog::generateFlash(char flash)
{
	QString notflash = tr("Flash did not fire");
    switch(flash) {
    case 0x0000: return notflash;
    case 0x0001: return tr("Flash fired");
    case 0x0005: return tr("Strobe return light not detected");
    case 0x0007: return tr("Strobe return light detected");
    case 0x0009: return tr("Flash fired, compulsory flash mode");
    case 0x000D: return tr("Flash fired, compulsory flash mode, return light not detected");
    case 0x000F: return tr("Flash fired, compulsory flash mode, return light detected");
    case 0x0010: return tr("Flash did not fire, compulsory flash mode");
    case 0x0018: return tr("Flash did not fire, auto mode");
    case 0x0019: return tr("Flash fired, auto mode");
    case 0x001D: return tr("Flash fired, auto mode, return light not detected");
    case 0x001F: return tr("Flash fired, auto mode, return light detected");
    case 0x0020: return tr("No flash function");
    case 0x0041: return tr("Flash fired, red-eye reduction mode");
    case 0x0045: return tr("Flash fired, red-eye reduction mode, return light not detected");
    case 0x0047: return tr("Flash fired, red-eye reduction mode, return light detected");
    case 0x0049: return tr("Flash fired, compulsory flash mode, red-eye reduction mode");
    case 0x004D: return tr("Flash fired, compulsory flash mode, red-eye reduction mode, return light not detected");
    case 0x004F: return tr("Flash fired, compulsory flash mode, red-eye reduction mode, return light detected");
    case 0x0059: return tr("Flash fired, auto mode, red-eye reduction mode");
    case 0x005D: return tr("Flash fired, auto mode, return light not detected, red-eye reduction mode");
    case 0x005F: return tr("Flash fired, auto mode, return light detected, red-eye reduction mode");
    }
    return notflash;
}

QString ExifDialog::generateOrientation(unsigned short orient)
{
    QString normal = tr("Horizontal (normal)");
    switch(orient) {
    case 0: return normal;
    case 1: return normal;
    case 2: return tr("Mirror horizontal");
    case 3: return tr("Rotate 180");
    case 4: return tr("Mirror vertical");
    case 5: return tr("Mirror horizontal and rotate 270 CW");
    case 6: return tr("Rotate 90 CW");
    case 7: return tr("Mirror horizontal and rotate 90 CW");
    case 8: return tr("Rotate 270 CW");
    }
    return normal;
}


void ExifDialog::setExif(const easyexif::EXIFInfo& info)
{
    if(!info.ImageWidth) {
        ui->textEdit->setText(tr("Exif is empty."));
        return;
    }
    QStringList tags;
    QString linefmt = "<tr><th>%1</th><td>%2</td></tr>";

    tags << linefmt.arg(tr("ImageWidth")).arg(info.ImageWidth);
    tags << linefmt.arg(tr("ImageHeight")).arg(info.ImageHeight);
    tags << linefmt.arg(tr("Make")).arg(QString::fromStdString(info.Make));
    tags << linefmt.arg(tr("Model")).arg(QString::fromStdString(info.Model));
    tags << linefmt.arg(tr("Orientation")).arg(generateOrientation(info.Orientation));

    tags << linefmt.arg(tr("BitsPerSample")).arg(info.BitsPerSample);
    tags << linefmt.arg(tr("Software")).arg(QString::fromStdString(info.Software));
    tags << linefmt.arg(tr("DateTime")).arg(QString::fromStdString(info.DateTime));
    tags << linefmt.arg(tr("DateTimeOriginal")).arg(QString::fromStdString(info.DateTimeOriginal));
    tags << linefmt.arg(tr("DateTimeDigitized")).arg(QString::fromStdString(info.DateTimeDigitized));
    tags << linefmt.arg(tr("SubSecTimeOriginal")).arg(QString::fromStdString(info.SubSecTimeOriginal));
    tags << linefmt.arg(tr("ExposureTime")).arg(info.ExposureTime);
    tags << linefmt.arg(tr("FNumber")).arg(info.FNumber);
    tags << linefmt.arg(tr("ISOSpeedRatings")).arg(info.ISOSpeedRatings);
    tags << linefmt.arg(tr("ShutterSpeedValue")).arg(info.ShutterSpeedValue);
    tags << linefmt.arg(tr("ExposureBiasValue")).arg(info.ExposureBiasValue);
    tags << linefmt.arg(tr("SubjectDistance")).arg(info.SubjectDistance);
    tags << linefmt.arg(tr("FocalLength")).arg(info.FocalLength);
    tags << linefmt.arg(tr("FocalLengthIn35mm")).arg(info.FocalLengthIn35mm);
    tags << linefmt.arg(tr("Flash")).arg(generateFlash(info.Flash));
    tags << linefmt.arg(tr("MeteringMode")).arg(info.MeteringMode);
    tags << linefmt.arg(tr("ImageDescription")).arg(QString::fromStdString(info.ImageDescription));
    tags << linefmt.arg(tr("Copyright")).arg(QString::fromStdString(info.Copyright));

    QString text = QString("<style>th {text-align: right;padding-right: 10px;} </style><table>%1</table>").arg(tags.join(""));

    ui->textEdit->setAcceptRichText(true);
    ui->textEdit->setText(text);
}

void ExifDialog::closeEvent(QCloseEvent *e)
{
    QWidget::closeEvent(e);
    emit closed();
}

