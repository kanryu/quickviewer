#include "fileassocdialog.h"
#include "ui_fileassocdialog.h"
#include <windows.h>
#include <shobjidl.h>

#define APPLICATION_ID                    "QuickViewer"
//#define REGKEYFORMAT_ASSOCFILE          "QuickViewer.AssocFile.%1"
#define REGKEYFORMAT_ASSOCFILE            APPLICATION_ID ".AssocFile.%1"
//#define REGKEYFORMAT_ASSOCPATH          "HKEY_CLASSES_ROOT\\QuickViewer.AssocFile.%1"
//#define REGKEY_QUICKVIEWER              "HKEY_LOCAL_MACHINE\\SOFTWARE\\QuickViewer"
//#define REGKEY_REGISTEREDAPPLICATIONS   "HKEY_LOCAL_MACHINE\\SOFTWARE\\RegisteredApplications"
//#define REGKEY_ROOT_QUICKVIEWER         "HKEY_CLASSES_ROOT\\Applications\\QuickViewer.exe"

#ifdef EXECUTE_ON_UAC
#  define REGKEY_SOFTWARE               "HKEY_LOCAL_MACHINE\\SOFTWARE"
#  define REGKEY_CLASSES                REGKEY_SOFTWARE "\\Classes"
#  define REGKEYFORMAT_CLASSES          REGKEY_SOFTWARE "\\Classes\\%1"
#  define REGKEYFORMAT_ASSOCPATH        REGKEY_CLASSES  "\\" APPLICATION_ID ".AssocFile.%1"
#  define REGKEY_REGISTEREDAPPLICATIONS REGKEY_SOFTWARE "\\RegisteredApplications"
#  define REGKEY_APPLICATION            REGKEY_SOFTWARE "\\" APPLICATION_ID
#  define REGKEY_APPLICATION_INAPP      REGKEY_CLASSES  "\\Applications\\" APPLICATION_ID ".exe"
#else
#  define REGKEY_SOFTWARE               "HKEY_CURRENT_USER\\Software"
#  define REGKEY_CLASSES                REGKEY_SOFTWARE "\\Classes"
#  define REGKEYFORMAT_CLASSES          REGKEY_SOFTWARE "\\Classes\\%1"
#  define REGKEYFORMAT_ASSOCPATH        REGKEY_CLASSES  "\\" APPLICATION_ID ".AssocFile.%1"
#  define REGKEY_REGISTEREDAPPLICATIONS REGKEY_SOFTWARE "\\RegisteredApplications"
#  define REGKEY_APPLICATION            REGKEY_SOFTWARE "\\" APPLICATION_ID
#  define REGKEY_APPLICATION_INAPP      REGKEY_CLASSES  "\\Applications\\" APPLICATION_ID ".exe"
#endif


#if QT_VERSION_MAJOR >= 5
#  ifdef WIN64
QSettings::Format FileAssocDialog::RegFormat = QSettings::Registry64Format;
#  else
QSettings::Format FileAssocDialog::RegFormat = QSettings::Registry32Format;
#  endif
#else
QSettings::Format FileAssocDialog::RegFormat = QSettings::NativeFormat;
#endif

FileAssocDialog::FileAssocDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileAssocDialog)
{
    ui->setupUi(this);

    m_assocOfActions["Jpeg"] = ui->checkBoxJpeg;
    m_assocs["Jpeg"] = AssocInfo{"Jpeg", tr("JPEG Image", "description of File format on Explorer(.jpeg)"), "qv_jpeg.ico", {".jpg",".jpeg"}};

    m_assocOfActions["Png"] = ui->checkBoxPng;
    m_assocs["Png"] = AssocInfo{"Png", tr("PNG File", "description of File format on Explorer(.png)"), "qv_png.ico", {".png"}};

    m_assocOfActions["Tga"] = ui->checkBoxTga;
    m_assocs["Tga"] = AssocInfo{"Tga", tr("Truevision Graphics Adapter Format Image", "description of File format on Explorer(.tga)"), "qv_tga.ico", {".tga"}};

    m_assocOfActions["Apng"] = ui->checkBoxApng;
    m_assocs["Apng"] = AssocInfo{"Apng", tr("Animated PNG File", "description of File format on Explorer(.apng)"), "qv_apng.ico", {".apng"}};

    m_assocOfActions["Bitmap"] = ui->checkBoxBmp;
    m_assocs["Bitmap"] = AssocInfo{"Bitmap", tr("Bitmap File", "description of File format on Explorer(.bmp)"), "qv_bmp.ico", {".bmp"}};

    m_assocOfActions["Dds"] = ui->checkBoxDds;
    m_assocs["Dds"] = AssocInfo{"Dds", tr("DirectDraw Surface Image", "description of File format on Explorer(.dds)"), "qv_dds.ico", {".dds"}};

    m_assocOfActions["Gif"] = ui->checkBoxGif;
    m_assocs["Gif"] = AssocInfo{"Gif", tr("GIF Image", "description of File format on Explorer(.gif)"), "qv_gif.ico", {".gif"}};

    m_assocOfActions["Icon"] = ui->checkBoxIcon;
    m_assocs["Icon"] = AssocInfo{"Icon", tr("Windows Icon File", "description of File format on Explorer(.ico)"), "", {".ico"}};

    m_assocOfActions["Tiff"] = ui->checkBoxTiff;
    m_assocs["Tiff"] = AssocInfo{"Tiff", tr("Tiff Image", "description of File format on Explorer(.tiff)"), "qv_tiff.ico", {".tif", ".tiff"}};

    m_assocOfActions["WebP"] = ui->checkBoxWebp;
    m_assocs["WebP"] = AssocInfo{"WebP", tr("WebP Image", "description of File format on Explorer(.webp)"), "qv_webp.ico", {".webp"}};

    m_assocOfActions["RawCanon"] = ui->checkBoxRawCanon;
    m_assocs["RawCanon"] = AssocInfo{"RawCanon", tr("Canon Raw Format", "description of File format on Explorer(.cr2)"), "qv_raw.ico", {".crw", ".cr2"}};

    m_assocOfActions["RawDng"] = ui->checkBoxRawDng;
    m_assocs["RawDng"] = AssocInfo{"RawDng", tr("Adobe Digital Negative Format", "description of File format on Explorer(.dng)"), "qv_raw.ico", {".dng"}};

    m_assocOfActions["RawNicon"] = ui->checkBoxRawNicon;
    m_assocs["RawNicon"] = AssocInfo{"RawNicon", tr("Nicon Raw Format", "description of File format on Explorer(.nef)"), "qv_raw.ico", {".nef"}};

    m_assocOfActions["RawSony"] = ui->checkBoxRawSony;
    m_assocs["RawSony"] = AssocInfo{"RawSony", tr("Sony Raw Format", "description of File format on Explorer(.arw)"), "qv_raw.ico", {".arw"}};


    {
        // check on if assoiation exists for each extension
        foreach(const QString &fmt, m_assocOfActions.keys()) {
            QSettings settings(REGKEY_CLASSES, RegFormat);
            settings.beginGroup(QString(REGKEYFORMAT_ASSOCFILE).arg(fmt));
            if(!settings.allKeys().isEmpty())
                m_assocOfActions[fmt]->setChecked(true);
            settings.endGroup();
        }
    }

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
    foreach(const QString& fmt, m_assocOfActions.keys()) {
        QCheckBox* c = m_assocOfActions[fmt];
        if(c && c->isChecked())
            result << fmt;
    }

    return result;
}

void FileAssocDialog::on_allOn_triggered()
{
    foreach(QCheckBox* c, m_assocOfActions.values()) {
        if(c)
            c->setChecked(true);
    }
}

void FileAssocDialog::on_allOff_triggered()
{
    foreach(QCheckBox* c, m_assocOfActions.values()) {
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
            QSettings settings(REGKEY_CLASSES, RegFormat);
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
        QSettings settings(REGKEY_APPLICATION, RegFormat);
        settings.beginGroup("Capabilities");
        settings.setValue("ApplicationDescription", "QuickViewer for folders/archives");
        settings.setValue("ApplicationName", APPLICATION_ID);
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
        settings2.setValue(APPLICATION_ID, "Software\\" APPLICATION_ID "\\Capabilities");
        settings2.sync();
    }
    {
        // assoiation for application
        QSettings settings(REGKEY_APPLICATION_INAPP, RegFormat);
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
        QSettings settings(REGKEY_APPLICATION, RegFormat);
        settings.clear();
        settings.sync();
    }
    {
        // RegisteredApplications
        QSettings settings(REGKEY_REGISTEREDAPPLICATIONS, RegFormat);
        settings.remove(APPLICATION_ID);
        settings.sync();
    }
    {
        // assoiation for application
        QSettings settings(REGKEY_APPLICATION_INAPP, RegFormat);
        settings.clear();
        settings.sync();
    }
}

QString FileAssocDialog::getExecuteApplication()
{
    return QString("\"%1\\" APPLICATION_ID ".exe\" \"%2\"")
            .arg(QDir::toNativeSeparators(qApp->applicationDirPath()))
            .arg("%1");
}

QString FileAssocDialog::getIconPath(QString iconName)
{
    return QString("\"%1\\iconengines\\%2\"")
            .arg(QDir::toNativeSeparators(qApp->applicationDirPath()))
            .arg(iconName);
}

