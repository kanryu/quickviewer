#include "fileassocdialog.h"
#include "ui_fileassocdialog.h"
#include <windows.h>
#include <shobjidl.h>

#define REGKEYFORMAT_ASSOCFILE          "QuickViewer.AssocFile.%1"
#define REGKEYFORMAT_ASSOCPATH          "HKEY_CLASSES_ROOT\\QuickViewer.AssocFile.%1"
#define REGKEY_QUICKVIEWER              "HKEY_LOCAL_MACHINE\\SOFTWARE\\QuickViewer"
#define REGKEY_REGISTEREDAPPLICATIONS   "HKEY_LOCAL_MACHINE\\SOFTWARE\\RegisteredApplications"
#define REGKEY_ROOT_QUICKVIEWER         "HKEY_CLASSES_ROOT\\Applications\\QuickViewer.exe"
#define APPLICATION_ID                  "QuickViewer"


#ifdef WIN64
QSettings::Format FileAssocDialog::RegFormat = QSettings::Registry64Format;
#else
QSettings::Format FileAssocDialog::RegFormat = QSettings::Registry32Format;
#endif


FileAssocDialog::FileAssocDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileAssocDialog)
{
    ui->setupUi(this);

    m_assocOfActions[ui->checkBoxJpeg] = "Jpeg";
    m_assocs["Jpeg"] = AssocInfo{"Jpeg", tr("JPEG Format Image", "description of File format on Explorer(.jpeg)"), "qv_jpeg.ico", {".jpg",".jpeg"}};

    m_assocOfActions[ui->checkBoxPng]  = "Png";
    m_assocs["Png"] = AssocInfo{"Png", tr("PNG Format Image", "description of File format on Explorer(.png)"), "qv_png.ico", {".png"}};

    m_assocOfActions[ui->checkBoxTga]  = "Tga";
    m_assocs["Tga"] = AssocInfo{"Tga", tr("Truevision Graphics Adapter Format Image", "description of File format on Explorer(.tga)"), "qv_tga.ico", {".tga"}};

    m_assocOfActions[ui->checkBoxApng] = "Apng";
    m_assocs["Apng"] = AssocInfo{"Apng", tr("Animated PNG Format Image", "description of File format on Explorer(.apng)"), "qv_apng.ico", {".apng"}};

    m_assocOfActions[ui->checkBoxBmp]  = "Bitmap";
    m_assocs["Bitmap"] = AssocInfo{"Bitmap", tr("Windows Bitmap Format Image", "description of File format on Explorer(.bmp)"), "qv_bmp.ico", {".bmp"}};

    m_assocOfActions[ui->checkBoxDds]  = "Dds";
    m_assocs["Dds"] = AssocInfo{"Dds", tr("DirectDraw Surface Format Image", "description of File format on Explorer(.dds)"), "qv_dds.ico", {".dds"}};

    m_assocOfActions[ui->checkBoxGif]  = "Gif";
    m_assocs["Gif"] = AssocInfo{"Gif", tr("GIF Format Image", "description of File format on Explorer(.gif)"), "qv_gif.ico", {".gif"}};

    m_assocOfActions[ui->checkBoxIcon] = "Icon";
    m_assocs["Icon"] = AssocInfo{"Icon", tr("Windows Icon Format", "description of File format on Explorer(.ico)"), "", {".ico"}};

    m_assocOfActions[ui->checkBoxTiff] = "Tiff";
    m_assocs["Tiff"] = AssocInfo{"Tiff", tr("Tiff Format Image", "description of File format on Explorer(.tiff)"), "qv_tiff.ico", {".tif", ".tiff"}};

    m_assocOfActions[ui->checkBoxWebp] = "WebP";
    m_assocs["WebP"] = AssocInfo{"WebP", tr("WebP Format Image", "description of File format on Explorer(.webp)"), "qv_webp.ico", {".webp"}};

    m_assocOfActions[ui->checkBoxRawCanon] = "RawCanon";
    m_assocs["RawCanon"] = AssocInfo{"RawCanon", tr("Canon Raw Format", "description of File format on Explorer(.cr2)"), "qv_raw.ico", {".crw", ".cr2"}};

    m_assocOfActions[ui->checkBoxRawDng]   = "RawDng";
    m_assocs["RawDng"] = AssocInfo{"RawDng", tr("Adobe Digital Negative Format", "description of File format on Explorer(.dng)"), "qv_raw.ico", {".dng"}};

    m_assocOfActions[ui->checkBoxRawNicon] = "RawNicon";
    m_assocs["RawNicon"] = AssocInfo{"RawNicon", tr("Nicon Raw Format", "description of File format on Explorer(.nef)"), "qv_raw.ico", {".nef"}};

    m_assocOfActions[ui->checkBoxRawSony]  = "RawSony";
    m_assocs["RawSony"] = AssocInfo{"RawSony", tr("Sony Raw Format", "description of File format on Explorer(.arw)"), "qv_raw.ico", {".arw"}};
}

FileAssocDialog::~FileAssocDialog()
{
    delete ui;
}

//void FileAssocDialog::closeEvent(QCloseEvent *event)
//{
//    QDialog::closeEvent(event);
//    if(result() == QDialog::Accepted) {
//        auto formats = enumrateFormats();
//        if(formats.isEmpty())
//            unregistEntries();
//        else
//            registEntries(formats);
//    }

//    emit closed();
//}

QStringList FileAssocDialog::enumrateFormats()
{
    QStringList result;
    foreach(QWidget* w, m_assocOfActions.keys()) {
        QCheckBox* c = dynamic_cast<QCheckBox*>(w);
        if(c && c->isChecked())
            result << m_assocOfActions[w];
    }

    return result;
}

void FileAssocDialog::on_allOn_triggered()
{
    foreach(QWidget* w, m_assocOfActions.keys()) {
        QCheckBox* c = dynamic_cast<QCheckBox*>(w);
        if(c)
            c->setChecked(true);
    }
}

void FileAssocDialog::on_allOff_triggered()
{
    foreach(QWidget* w, m_assocOfActions.keys()) {
        QCheckBox* c = dynamic_cast<QCheckBox*>(w);
        if(c)
            c->setChecked(false);
    }
}

void FileAssocDialog::on_tryRegist_triggered()
{
    auto formats = enumrateFormats();
    if(formats.isEmpty())
        unregistEntries();
    else
        registEntries(formats);
    accept();
    return;
}

void FileAssocDialog::registEntries(QStringList formats)
{
//    qDebug() << "registEntries()";
    {
        // assoiation for each extension
        foreach(const QString &fmt, formats) {
//            qDebug() << QString(REGKEYFORMAT_ASSOCFILE).arg(fmt);
            QSettings settings("HKEY_CLASSES_ROOT", RegFormat);
            settings.beginGroup(QString(REGKEYFORMAT_ASSOCFILE).arg(fmt));
            settings.setValue(".", m_assocs[fmt].Description);
            if(!m_assocs[fmt].IconName.isEmpty()) {
                settings.beginGroup("DefaultIcon");
                settings.setValue(".", getIconPath(m_assocs[fmt].IconName));
                settings.endGroup();
            }
            settings.beginGroup("shell");
            settings.beginGroup("open");
            settings.setValue(".", tr("&View with QuickViewer", "Menu displayed when right clicking on file in Explorer"));
            settings.beginGroup("command");
            settings.setValue(".", getExecuteApplication());
            settings.endGroup();
            settings.endGroup();
            settings.endGroup();
            settings.endGroup();
            settings.sync();
        }
    }
    {
        // QuickViewer Capabilities
        QSettings settings(REGKEY_QUICKVIEWER, RegFormat);
        settings.beginGroup("Capabilities");
        settings.setValue("ApplicationDescription", "QuickViewer for folders/archives");
        settings.setValue("ApplicationName", "QuickViewer");
        settings.beginGroup("FileAssociations");
        foreach(const QString &fmt, formats) {
            foreach(const QString &assoc, m_assocs[fmt].Extensions)
                settings.setValue(assoc, QString(REGKEYFORMAT_ASSOCFILE).arg(fmt));
        }
        settings.endGroup();
        settings.endGroup();
        settings.sync();
    }
    {
        // RegisteredApplications
        QSettings settings2(REGKEY_REGISTEREDAPPLICATIONS, RegFormat);
        settings2.setValue(APPLICATION_ID, "Software\\QuickViewer\\Capabilities");
        settings2.sync();
    }
    {
        // assoiation for application
        QSettings settings(REGKEY_ROOT_QUICKVIEWER, RegFormat);
        settings.beginGroup("shell");
        settings.beginGroup("open");
        settings.setValue(".", tr("&View with QuickViewer", "Menu displayed when right clicking on file in Explorer"));
        settings.beginGroup("command");
        settings.setValue(".", getExecuteApplication());
        settings.endGroup();
        settings.endGroup();
        settings.endGroup();
        settings.sync();
    }

    IApplicationAssociationRegistrationUI* pAARUI = NULL;
    HRESULT hr = ::CoCreateInstance( CLSID_ApplicationAssociationRegistrationUI, NULL, CLSCTX_INPROC, __uuidof( IApplicationAssociationRegistrationUI ), reinterpret_cast< void** >( &pAARUI ) );

    if ( SUCCEEDED( hr ) && pAARUI != NULL )
    {
        hr = pAARUI->LaunchAdvancedAssociationUI(L"QuickViewer");
        pAARUI->Release();
    }
}

void FileAssocDialog::unregistEntries()
{
    {
        // assoiation for each extension
        foreach(const QString &fmt, m_assocs.keys()) {
            QSettings settings(QString(REGKEYFORMAT_ASSOCPATH).arg(fmt), RegFormat);
            settings.clear();
            settings.sync();
        }
    }
    {
        // QuickViewer Capabilities
        QSettings settings(REGKEY_QUICKVIEWER, RegFormat);
        settings.clear();
        settings.sync();
    }
    {
        // RegisteredApplications
        QSettings settings(REGKEY_REGISTEREDAPPLICATIONS, RegFormat);
        settings.remove("QuickViewer");
        settings.sync();
    }
    {
        // assoiation for application
        QSettings settings(REGKEY_ROOT_QUICKVIEWER, RegFormat);
        settings.clear();
        settings.sync();
    }
}

QString FileAssocDialog::getExecuteApplication()
{
    return QString("\"%1\\QuickViewer.exe\" \"%2\"")
            .arg(QDir::toNativeSeparators(qApp->applicationDirPath()))
            .arg("%1");
}

QString FileAssocDialog::getIconPath(QString iconName)
{
    return QString("\"%1\\iconengines\\%2\"")
            .arg(QDir::toNativeSeparators(qApp->applicationDirPath()))
            .arg(iconName);
}

