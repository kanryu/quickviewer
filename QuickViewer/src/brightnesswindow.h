#ifndef BRIGHTNESSWINDOW_H
#define BRIGHTNESSWINDOW_H

#include <QtWidgets>
#include "imageview.h"


namespace Ui {
class BrightnessWindow;
class MainWindow;
}

class BrightnessWindow : public QWidget
{
    Q_OBJECT

public:
    explicit BrightnessWindow(QWidget *parent, Ui::MainWindow* uiMain);
    ~BrightnessWindow();
    float sliderToFloat(int value);
    int floatToSlider(float value);
    void setImageView(ImageView* imageView);
    void resetSliders();

signals:
    void brightnessChanged(ImageRetouch value);

public slots:
    void onSliderBrightness_valueChanged(int value);
    void onSliderContrast_valueChanged(int value);
    void onSliderGamma_valueChanged(int value);
    void onResetButton_clicked();

private:
    Ui::BrightnessWindow *ui;
    ImageView* m_imageView;
    ImageRetouch m_retouchParams;
};

#endif // BRIGHTNESSWINDOW_H
