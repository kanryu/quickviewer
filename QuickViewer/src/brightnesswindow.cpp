#include "brightnesswindow.h"
#include "ui_brightnesswindow.h"
#include "pagemanager.h"

BrightnessWindow::BrightnessWindow(QWidget *parent, Ui::MainWindow* uiMain) :
    QWidget(parent)
    , ui(new Ui::BrightnessWindow)
    , ignoreTextChange(false)
{
    ui->setupUi(this);
    ui->checkBoxForAll->setVisible(false);
}

BrightnessWindow::~BrightnessWindow()
{
    delete ui;
}

float BrightnessWindow::sliderToFloat(int value)
{
    // -20 ->   0.01
    // -10 ->   0.1
    //   0 ->   1.0
    //  10 ->  10
    //  20 -> 100
    return powf(10, 0.1f/8*value);
}

int BrightnessWindow::floatToSlider(float value)
{
    //   0.01 -> -20
    //   0.1  -> -10
    //   1.0  ->   0
    //  10    ->  10
    // 100    ->  20
    return (int)(10*8*log10f(value));
}

void BrightnessWindow::setImageView(ImageView *imageView)
{
    m_imageView = imageView;
    auto pages = m_imageView->pages();
    if(pages->isEmpty())
        return;

    m_retouchParams = m_imageView->brightness();
    resetSliders();
}

void BrightnessWindow::resetSliders()
{
    ui->sliderBrightness->setValue((int)m_retouchParams.Brightness);
    ui->lineBrightness->setText(QString::number(ui->sliderBrightness->value()));

    ui->sliderContrast->setValue(floatToSlider(m_retouchParams.Contrast));
    ui->lineContrast->setText(QString::number(ui->sliderContrast->value()));

    ui->sliderGamma->setValue(floatToSlider(m_retouchParams.Gamma));
    ui->lineGamma->setText(QString::number(ui->sliderGamma->value()));
}

void BrightnessWindow::onSliderBrightness_valueChanged(int value)
{
    m_retouchParams.Brightness = value;
    if(!ignoreTextChange) ui->lineBrightness->setText(QString::number(value));
    emit brightnessChanged(m_retouchParams);
}

void BrightnessWindow::onSliderContrast_valueChanged(int value)
{
    m_retouchParams.Contrast = sliderToFloat(value);
    if(!ignoreTextChange) ui->lineContrast->setText(QString::number(value));
    emit brightnessChanged(m_retouchParams);
}

void BrightnessWindow::onSliderGamma_valueChanged(int value)
{
    m_retouchParams.Gamma = sliderToFloat(value);
    if(!ignoreTextChange) ui->lineGamma->setText(QString::number(value));
    emit brightnessChanged(m_retouchParams);
}

void BrightnessWindow::onLineBrightness_textChanged(QString text)
{
    int value = text.toInt();
    ignoreTextChange = true;
    ui->sliderBrightness->setValue((int)value);
    ignoreTextChange = false;
}

void BrightnessWindow::onLineContrast_textChanged(QString text)
{
    int value = text.toInt();
    ignoreTextChange = true;
    ui->sliderContrast->setValue((int)value);
    ignoreTextChange = false;
}

void BrightnessWindow::onLineGamma_textChanged(QString text)
{
    int value = text.toInt();
    ignoreTextChange = true;
    ui->sliderGamma->setValue((int)value);
    ignoreTextChange = false;
}

void BrightnessWindow::onResetButton_clicked()
{
    m_retouchParams = ImageRetouch();
    resetSliders();
    emit brightnessChanged(m_retouchParams);
}

