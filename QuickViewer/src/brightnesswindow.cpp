#include "brightnesswindow.h"
#include "ui_brightnesswindow.h"
#include "pagemanager.h"

BrightnessWindow::BrightnessWindow(QWidget *parent, Ui::MainWindow* uiMain) :
    QWidget(parent),
    ui(new Ui::BrightnessWindow)
{
    ui->setupUi(this);
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
    return powf(10, 0.1f*value);
}

int BrightnessWindow::floatToSlider(float value)
{
    //   0.01 -> -20
    //   0.1  -> -10
    //   1.0  ->   0
    //  10    ->  10
    // 100    ->  20
    return (int)(10*log10f(value));
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
    ui->sliderContrast->setValue(floatToSlider(m_retouchParams.Contrast));
    ui->sliderGamma->setValue(floatToSlider(m_retouchParams.Gamma));
}

void BrightnessWindow::onSliderBrightness_valueChanged(int value)
{
    m_retouchParams.Brightness = value;
    emit brightnessChanged(m_retouchParams);
}

void BrightnessWindow::onSliderContrast_valueChanged(int value)
{
    m_retouchParams.Contrast = sliderToFloat(value);
    emit brightnessChanged(m_retouchParams);
}

void BrightnessWindow::onSliderGamma_valueChanged(int value)
{
    m_retouchParams.Gamma = sliderToFloat(value);
    emit brightnessChanged(m_retouchParams);
}

void BrightnessWindow::onResetButton_clicked()
{
    m_retouchParams = ImageRetouch();
    resetSliders();
    emit brightnessChanged(m_retouchParams);
}

