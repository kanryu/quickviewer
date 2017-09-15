#include <QLocale>

#include "exifdialog.h"
#include "ui_exifdialog.h"

struct ImageMetaContents
{
    QStringList stringsRichText;
    QStringList stringsClipBoard;

    template<typename ValueType>
    void addContent(QString key, ValueType value) {
        const QString richfmt = "<tr><th>%1</th><td>%2</td></tr>";
        const QString clipfmt = "%1\t%2";
        stringsRichText << richfmt.arg(key).arg(value);
        stringsClipBoard << clipfmt.arg(key).arg(value);
    }
    QString getRichText() {
        QString text = QString("<style>th {text-align: right;padding-right: 10px;} </style><table>%1</table>").arg(stringsRichText.join(""));
        return text;
    }
    QString getClipBoard() {
        QString clip = stringsClipBoard.join(LINEFEED);
        return clip;
    }
};




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
    QString notflash = tr("Flash did not fire", "JPEG EXIF Flash setting value (0x0)");
    switch(flash) {
    default:break;
//    case 0x0: return notflash;
//    case 0x1: return tr("Flash fired", "JPEG EXIF Flash setting value (0x1)");
    case 0x0000: return notflash;
    case 0x0001: return tr("Flash fired", "JPEG EXIF Flash setting value (0x1)");
    case 0x0005: return tr("Strobe return light not detected", "JPEG EXIF Flash setting value (0x5)");
    case 0x0007: return tr("Strobe return light detected", "JPEG EXIF Flash setting value (0x7)");
    case 0x0009: return tr("Flash fired, compulsory flash mode", "JPEG EXIF Flash setting value (0x9)");
    case 0x000D: return tr("Flash fired, compulsory flash mode, return light not detected", "JPEG EXIF Flash setting value (0xD)");
    case 0x000F: return tr("Flash fired, compulsory flash mode, return light detected", "JPEG EXIF Flash setting value (0xF)");
    case 0x0010: return tr("Flash did not fire, compulsory flash mode", "JPEG EXIF Flash setting value (0x10)");
    case 0x0018: return tr("Flash did not fire, auto mode", "JPEG EXIF Flash setting value (0x18)");
    case 0x0019: return tr("Flash fired, auto mode", "JPEG EXIF Flash setting value (0x19)");
    case 0x001D: return tr("Flash fired, auto mode, return light not detected", "JPEG EXIF Flash setting value (0x1D)");
    case 0x001F: return tr("Flash fired, auto mode, return light detected", "JPEG EXIF Flash setting value (0x1F)");
    case 0x0020: return tr("No flash function", "JPEG EXIF Flash setting value (0x20)");
    case 0x0041: return tr("Flash fired, red-eye reduction mode", "JPEG EXIF Flash setting value (0x41)");
    case 0x0045: return tr("Flash fired, red-eye reduction mode, return light not detected", "JPEG EXIF Flash setting value (0x45)");
    case 0x0047: return tr("Flash fired, red-eye reduction mode, return light detected", "JPEG EXIF Flash setting value (0x47)");
    case 0x0049: return tr("Flash fired, compulsory flash mode, red-eye reduction mode", "JPEG EXIF Flash setting value (0x49)");
    case 0x004D: return tr("Flash fired, compulsory flash mode, red-eye reduction mode, return light not detected", "JPEG EXIF Flash setting value (0x4D)");
    case 0x004F: return tr("Flash fired, compulsory flash mode, red-eye reduction mode, return light detected", "JPEG EXIF Flash setting value (0x4F)");
    case 0x0059: return tr("Flash fired, auto mode, red-eye reduction mode", "JPEG EXIF Flash setting value (0x59)");
    case 0x005D: return tr("Flash fired, auto mode, return light not detected, red-eye reduction mode", "JPEG EXIF Flash setting value (0x5D)");
    case 0x005F: return tr("Flash fired, auto mode, return light detected, red-eye reduction mode", "JPEG EXIF Flash setting value (0x5F)");
    }
    return notflash;
}

//QString ExifDialog::generateFlashMode(unsigned short mode)
//{
//    QString notflash = tr("unknown");
//    switch(mode) {
//    default:break;
//    case 0x0: return notflash;
//    case 0x1: return tr("Compulsory flash mode", "JPEG EXIF Flash setting value with (0x8)");
//    case 0x2: return tr("Compulsory flash suppression", "JPEG EXIF Flash setting value with (0x9)");
//    case 0x3: return tr("Automatic mode", "JPEG EXIF Flash setting value with (0xa)");
//    }
//    return notflash;
//}

//QString ExifDialog::generateFlashReturnedLight(unsigned short light)
//{
//    QString notflash = tr("No strobe return detection function", "JPEG EXIF Flash setting value without (0x6)");
//    switch(light) {
//    default:break;
//    case 0x0: return notflash;
//    case 0x1: return tr("Reserved", "JPEG EXIF Flash setting value with (0x2)");
//    case 0x2: return tr("Strobe return light not detected", "JPEG EXIF Flash setting value with (0x4)");
//    case 0x3: return tr("Strobe return light detected", "JPEG EXIF Flash setting value with (0x6)");
//    }
//    return notflash;
//}

QString ExifDialog::generateOrientation(unsigned short orient)
{
    QString normal = tr("Horizontal (normal)", "JPEG EXIF Orientation of the main body of the camera(0 or 1)");
    switch(orient) {
    case 0: return normal;
    case 1: return normal;
    case 2: return tr("Mirror horizontal", "JPEG EXIF Orientation of the main body of the camera(2)");
    case 3: return tr("Rotate 180", "JPEG EXIF Orientation of the main body of the camera(3)");
    case 4: return tr("Mirror vertical", "JPEG EXIF Orientation of the main body of the camera(4)");
    case 5: return tr("Mirror horizontal and rotate 270 CW", "JPEG EXIF Orientation of the main body of the camera(5)");
    case 6: return tr("Rotate 90 CW", "JPEG EXIF Orientation of the main body of the camera(6)");
    case 7: return tr("Mirror horizontal and rotate 90 CW", "JPEG EXIF Orientation of the main body of the camera(7)");
    case 8: return tr("Rotate 270 CW", "JPEG EXIF Orientation of the main body of the camera(8)");
    }
    return normal;
}


void ExifDialog::setExif(const ImageContent& content)
{
    const easyexif::EXIFInfo& info = content.Info;
    if(!info.ImageWidth) {
        ui->textEdit->setText(tr("Exif is not included.", "Text to display if EXIF is not included in JPEG"));
        return;
    }
    ImageMetaContents meta;
    meta.addContent(tr("Filename"), content.Path);
    meta.addContent(tr("Pixels"), QString("%L1").arg(content.BaseSize.width()*content.BaseSize.height()));
    meta.addContent(tr("ImageWidth"), info.ImageWidth);
    meta.addContent(tr("ImageHeight"), info.ImageHeight);
    meta.addContent(tr("Make"), QString::fromStdString(info.Make));
    meta.addContent(tr("Model"), QString::fromStdString(info.Model));
    meta.addContent(tr("Orientation of camera"), generateOrientation(info.Orientation));

    meta.addContent(tr("BitsPerSample"), info.BitsPerSample);
    meta.addContent(tr("Software"), QString::fromStdString(info.Software));
    meta.addContent(tr("DateTime"), QString::fromStdString(info.DateTime));
    meta.addContent(tr("DateTimeOriginal"), QString::fromStdString(info.DateTimeOriginal));
    meta.addContent(tr("DateTimeDigitized"), QString::fromStdString(info.DateTimeDigitized));
    meta.addContent(tr("SubSecTimeOriginal"), QString::fromStdString(info.SubSecTimeOriginal));
    meta.addContent(tr("ExposureTime"), info.ExposureTime);
    meta.addContent(tr("FNumber"), info.FNumber);
    meta.addContent(tr("ISOSpeedRatings"), info.ISOSpeedRatings);
    meta.addContent(tr("ShutterSpeedValue"), info.ShutterSpeedValue);
    meta.addContent(tr("ExposureBiasValue"), info.ExposureBiasValue);
    meta.addContent(tr("SubjectDistance"), info.SubjectDistance);
    meta.addContent(tr("FocalLength"), info.FocalLength);
    meta.addContent(tr("FocalLengthIn35mm"), info.FocalLengthIn35mm);
    meta.addContent(tr("Flash"), generateFlash(info.Flash | (info.FlashMode<<3) | (info.FlashReturnedLight<<1)));
    meta.addContent(tr("MeteringMode"), info.MeteringMode);
    meta.addContent(tr("ImageDescription"), QString::fromStdString(info.ImageDescription));
    meta.addContent(tr("Copyright"), QString::fromStdString(info.Copyright));

    m_exif = meta.getClipBoard();
    ui->textEdit->setAcceptRichText(true);
    ui->textEdit->setText(meta.getRichText());
}

void ExifDialog::closeEvent(QCloseEvent *e)
{
    QWidget::closeEvent(e);
    emit closed();
}

void ExifDialog::onBtnClipbard_clicked()
{
    QClipboard* clipboard = QApplication::clipboard();
    clipboard->setText(m_exif);
}

