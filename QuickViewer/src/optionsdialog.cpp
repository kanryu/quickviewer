#include "optionsdialog.h"
#include "ui_optionsdialog.h"
#include "qvapplication.h"
#include "imageview.h"
#include "pagemanager.h"

class SamplePageContent : public PageContentProtocol, public PageManagerProtocol
{
public:
    SamplePageContent()
        : m_size(20)
        , m_currentPage(10)
        , m_volumePath("C:\\SampleBook")
    {
        m_pages = {PageContent(nullptr, nullptr,
                        ImageContent(
                            QImage(1000, 1200, QImage::Format_RGB32),
                            "page11.jpg",
                            QSize(1000,1200),
                            easyexif::EXIFInfo(),
                            1234567)),
                   PageContent(nullptr, nullptr,
                        ImageContent(
                            QImage(1000, 1200, QImage::Format_RGB32),
                            "page12.jpg",
                            QSize(1000,1200),
                            easyexif::EXIFInfo(),
                            1234567))
                  };
        m_pages[0].DrawScale = 0.5;
        m_pages[1].DrawScale = 0.5;
    }
    int size() { return m_size; }
    int currentPage() { return m_currentPage; }
    QString volumePath() { return m_volumePath; }
    QVector<PageContent>* pages() { return &m_pages; }

private:
    int m_size;
    int m_currentPage;
    QString m_volumePath;
    QVector<PageContent> m_pages;
};

static SamplePageContent *stSamplePageContent;

OptionsDialog::OptionsDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::OptionsDialog)
{
    ui->setupUi(this);
    if(!stSamplePageContent)
        stSamplePageContent = new SamplePageContent;
    m_imageString.initialize(stSamplePageContent, stSamplePageContent);
#ifndef Q_OS_WIN
    ui->checkBoxUseDirect2D->setVisible(false);
#endif
    m_slideShowWait = qApp->SlideShowWait();
    m_maxVolumesCache = qApp->MaxVolumesCache();
    m_backgroundColor = qApp->BackgroundColor();
    m_backgroundColor2 = qApp->BackgroundColor2();
    m_useCheckeredPattern = qApp->UseCheckeredPattern();

    ui->spinSlideshow->setValue(m_slideShowWait);
    ui->spinVolumes->setValue(m_maxVolumesCache);
    ui->spinImages->setValue(qApp->MaxImagesCache());
    ui->spinMaxTextureSize->setValue(qApp->MaxTextureSize());
    ui->checkBoxCheckeredPattern->setChecked(m_useCheckeredPattern);
    ui->checkBoxUseFastDctForJPEG->setChecked(qApp->UseFastDCTForJPEG());
    ui->checkBoxExtractSolidToTemporary->setChecked(qApp->ExtractSolidArchiveToTemporaryDir());
    ui->checkBoxProhibitMultipleRunning->setChecked(qApp->ProhibitMultipleRunning());
    ui->checkBoxUseDirect2D->setChecked(qApp->UseDirect2D());
    ui->checkBoxHidePageBarParmanently->setChecked(qApp->HidePageBarParmanently());
    ui->checkBoxHideScrollBarInFullscreen->setChecked(qApp->HideScrollBarInFullscreen());
    ui->checkBoxTopWindowWhenRunWithAssoc->setChecked(qApp->TopWindowWhenRunWithAssoc());
    ui->checkBoxTopWindowWhenDropped->setChecked(qApp->TopWindowWhenDropped());

    resetColorButton(ui->btnColorSelect, m_backgroundColor);
    resetColorButton(ui->btnColorSelect2, m_backgroundColor2);
    resetColorBox();

    // Caption Formats
    ui->labelFormatUsage->setText(m_imageString.getFormatUsage());

    ui->lineEditWindowTitleUserStyle->setText(qApp->TitleTextFormat());
    ui->labelWindowTitleSample->setText(m_imageString.formatString(qApp->TitleTextFormat()));
    if(qApp->TitleTextFormat() == QV_WINDOWTITLE_FORMAT) {
        ui->radioButtonWindowTitleNormalStyle->setChecked(true);
    } else if(qApp->TitleTextFormat() == IRFANVIEW_WINDOWTITLE_FORMAT) {
        ui->radioButtonWindowTitleIrfanViewStyle->setChecked(true);
    } else {
        ui->radioButtonWindowTitleUserDefined->setChecked(true);
    }
    if(!ui->radioButtonWindowTitleUserDefined->isChecked())
        ui->lineEditWindowTitleUserStyle->setEnabled(false);

    ui->lineEditStatusBarUserStyle->setText(qApp->StatusTextFormat());
    ui->labelStatusBarSample->setText(m_imageString.formatString(qApp->StatusTextFormat()));
    if(qApp->StatusTextFormat() == QV_STATUSBAR_FORMAT)
        ui->radioButtonStatusBarNormalStyle->setChecked(true);
    else if(qApp->StatusTextFormat() == IRFANVIEW_STATUSBAR_FORMAT)
        ui->radioButtonStatusBarIrfanViewStyle->setChecked(true);
    else
        ui->radioButtonStatusBarUserDefined->setChecked(true);
    if(!ui->radioButtonStatusBarUserDefined->isChecked())
        ui->lineEditStatusBarUserStyle->setEnabled(false);
}

OptionsDialog::~OptionsDialog()
{

}

void OptionsDialog::reflectResults()
{
    qApp->setSlideShowWait(ui->spinSlideshow->value());
    qApp->setMaxVolumesCache(ui->spinVolumes->value());
    qApp->setMaxImagesCache(ui->spinImages->value());
    qApp->setMaxTextureSize(ui->spinMaxTextureSize->value());
    qApp->setBackgroundColor(m_backgroundColor);
    qApp->setBackgroundColor2(m_backgroundColor2);
    qApp->setUseCheckeredPattern(m_useCheckeredPattern);
    qApp->setUseFastDCTForJPEG(ui->checkBoxUseFastDctForJPEG->isChecked());
    qApp->setExtractSolidArchiveToTemporaryDir(ui->checkBoxExtractSolidToTemporary->isChecked());
    qApp->setProhibitMultipleRunning(ui->checkBoxProhibitMultipleRunning->isChecked());
    qApp->setUseDirect2D(ui->checkBoxUseDirect2D->isChecked());
    qApp->setHidePageBarParmanently(ui->checkBoxHidePageBarParmanently->isChecked());
    qApp->setHideScrollBarInFullscreen(ui->checkBoxHideScrollBarInFullscreen->isChecked());
    qApp->setTopWindowWhenRunWithAssoc(ui->checkBoxTopWindowWhenRunWithAssoc->isChecked());
    qApp->setTopWindowWhenDropped(ui->checkBoxTopWindowWhenDropped->isChecked());

    if(ui->radioButtonWindowTitleNormalStyle->isChecked())
        qApp->setTitleTextFormat(QV_WINDOWTITLE_FORMAT);
    else if(ui->radioButtonWindowTitleIrfanViewStyle->isChecked())
        qApp->setTitleTextFormat(IRFANVIEW_WINDOWTITLE_FORMAT);
    else
        qApp->setTitleTextFormat(ui->lineEditWindowTitleUserStyle->text());

    if(ui->radioButtonStatusBarNormalStyle->isChecked())
        qApp->setStatusTextFormat(QV_STATUSBAR_FORMAT);
    else if(ui->radioButtonStatusBarIrfanViewStyle->isChecked())
        qApp->setStatusTextFormat(IRFANVIEW_STATUSBAR_FORMAT);
    else
        qApp->setStatusTextFormat(ui->lineEditStatusBarUserStyle->text());
}

void OptionsDialog::resetColorButton(QPushButton* btn, QColor color)
{
    QPixmap pix(16, 16);
    pix.fill(color);
    QIcon icon(pix);
    btn->setIcon(icon);
}

void OptionsDialog::resetColorBox()
{
    QPixmap pattern(48, 48);
    QBrush brush;
    if(!m_useCheckeredPattern) {
        brush = QBrush(m_backgroundColor, Qt::SolidPattern);

        ui->labelColor2->setEnabled(false);
        ui->btnColorSelect2->setEnabled(false);
    } else {
        QPixmap pix(16, 16);
        pix.fill(m_backgroundColor);
        QPainter paint(&pix);
        QBrush brush2(m_backgroundColor2, Qt::SolidPattern);
        paint.fillRect(QRect(0, 0, 8, 8), brush2);
        paint.fillRect(QRect(8, 8, 8, 8), brush2);
        brush = QBrush(pix);

        ui->labelColor2->setEnabled(true);
        ui->btnColorSelect2->setEnabled(true);
    }
    QPainter paint(&pattern);
    paint.fillRect(QRect(0, 0, 48, 48), brush);
    ui->labelBgSample->setPixmap(pattern);
}

void OptionsDialog::resetWindowTitleSample()
{
    QString format;
    format = ui->radioButtonWindowTitleNormalStyle->isChecked()    ? QV_WINDOWTITLE_FORMAT
           : ui->radioButtonWindowTitleIrfanViewStyle->isChecked() ? IRFANVIEW_WINDOWTITLE_FORMAT
           : ui->lineEditWindowTitleUserStyle->text();
    ui->labelWindowTitleSample->setText(m_imageString.formatString(format));

}

void OptionsDialog::resetStatusbarSample()
{
    QString format;
    format = ui->radioButtonStatusBarNormalStyle->isChecked()    ? QV_STATUSBAR_FORMAT
           : ui->radioButtonStatusBarIrfanViewStyle->isChecked() ? IRFANVIEW_STATUSBAR_FORMAT
           : ui->lineEditStatusBarUserStyle->text();
    ui->labelStatusBarSample->setText(m_imageString.formatString(format));
}

void OptionsDialog::onBtnColorSelect_clicked()
{
    QColorDialog dialog(this);
    dialog.setCurrentColor(m_backgroundColor);
    if(dialog.exec() == QDialog::Accepted) {
        m_backgroundColor = dialog.currentColor();
        resetColorButton(ui->btnColorSelect, m_backgroundColor);
        resetColorBox();
    }
}

void OptionsDialog::onBtnColorSelect2_clicked()
{
    QColorDialog dialog(this);
    dialog.setCurrentColor(m_backgroundColor2);
    if(dialog.exec() == QDialog::Accepted) {
        m_backgroundColor2 = dialog.currentColor();
        resetColorButton(ui->btnColorSelect2, m_backgroundColor2);
        resetColorBox();
    }
}

void OptionsDialog::onCheckBoxCheckeredPattern_clicked(bool enabled)
{
    m_useCheckeredPattern = enabled;
    resetColorBox();
}

void OptionsDialog::onRadioButtonWindowTitle_triggered(bool)
{
    resetWindowTitleSample();
    ui->lineEditWindowTitleUserStyle->setEnabled(ui->radioButtonWindowTitleUserDefined->isChecked());
}

void OptionsDialog::onRadioButtonStatusBar_triggered(bool)
{
    resetStatusbarSample();
    ui->lineEditStatusBarUserStyle->setEnabled(ui->radioButtonStatusBarUserDefined->isChecked());
}

void OptionsDialog::onLineEditWindowTitleUserStyle_textEdited(QString text)
{
    resetWindowTitleSample();
}

void OptionsDialog::onLineEditStatusBarUserStyle_textEdited(QString text)
{
    resetStatusbarSample();
}
