#ifndef RGB_NA_HSL_H
#define RGB_NA_HSL_H

#include <QWidget>
#include <QSlider>
#include <QLabel>
#include <QSlider>
#include <QPushButton>


namespace Ui {
    class rgb_na_hsl;
}

class rgb_na_hsl : public QWidget
{
    Q_OBJECT
    Ui::rgb_na_hsl *ui;
       QLabel hLabel, sLabel, lLabel, hWartosc, sWartosc, lWartosc;
       QSlider hSlider, sSlider, lSlider;
       QPushButton ANULUJbutton, OKbutton;
       QImage *obrazek;
       QImage tmpObrazek;
       double max(double,double);
       double min(double,double);
       double zakres1(double,double,double);
       double zakres2(double);

   public:
       void setImage(QImage*);

   public:
       rgb_na_hsl(QWidget *parent = 0);
       ~rgb_na_hsl();

   protected:
       void changeEvent(QEvent *e);


   public slots:
       void HSL();
       void cancel();

   signals:
       void sigUpdateImage();

};

#endif // RGB_NA_HSL_H
