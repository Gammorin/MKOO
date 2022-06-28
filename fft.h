#ifndef FOURIERTRANSFORMVISUALISATION_H
#define FOURIERTRANSFORMVISUALISATION_H

#include <QWidget>
#include <imagewidget.h>

namespace Ui {
class FourierTransformVisualisation;
}

class FourierTransformVisualisation : public QWidget
{
    Q_OBJECT

public:
    explicit FourierTransformVisualisation(QWidget *parent = 0);
    ~FourierTransformVisualisation();
     void setImage(QImage*);

private:
    Ui::FourierTransformVisualisation *ui;
    imagewidget* redPhase;
    imagewidget* redMagnitude;
        QImage *image,tImage;
   //----------------------------

//        imagewidget *imageWidget;

        imagewidget *iwFazaRed;
        imagewidget *iwModulRed;
        imagewidget *iwFazaGreen;
        imagewidget *iwModulGreen;
        imagewidget *iwFazaBlue;
        imagewidget *iwModulBlue;


         static void zmianaCw(QImage* image);

public slots:

         void updateTransformata();
};


#endif // FOURIERTRANSFORMVISUALISATION_H
