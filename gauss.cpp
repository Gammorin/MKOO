#include "gauss.h"
#include "ui_gauss.h"

#include <math.h>


Filtr_Gaussa::Filtr_Gaussa(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Filtr_Gaussa)
{
    ui->setupUi(this);
     setWindowTitle("Filtr Gaussa");

   ui->Slider->setRange(1,15);
   ui->Slider->setValue(1);
   ui->wPromienia->setNum(1);


   connect(ui->Slider, SIGNAL(valueChanged(int)), this->ui->wPromienia, SLOT(setNum(int)));
   connect(ui->pOk, SIGNAL(clicked()), this, SLOT(close()));
   connect(ui->lButton, SIGNAL(clicked()), this, SLOT(oblicz()));
   connect(ui->pAnuluj, SIGNAL(clicked()), this, SLOT(zresetuj()));
}

Filtr_Gaussa::~Filtr_Gaussa()
{
    delete ui;
}



void Filtr_Gaussa::setImage(QImage *im)
{
    obrazek = im;
    tmpObrazek = *im;
}


QColor Filtr_Gaussa::ustawKolor(int size, QColor** c, int** wartoscMaski, int wspolczynnik)
{
    int blue = 0, red = 0, green = 0;

    for(int i=0;i<size;i++)
    {
        for(int j=0;j<size;j++)
        {
            red += c[i][j].red()*wartoscMaski[i][j];
            green += c[i][j].green()*wartoscMaski[i][j];
            blue += c[i][j].blue()*wartoscMaski[i][j];
        }
    }

    red = red / wspolczynnik;
    if (red > 255)
        red = 255;
    if (red < 0)
        red = 0;

    green = green / wspolczynnik;
    if (green > 255)
        green = 255;
    if (green < 0)
        green = 0;

    blue = blue / wspolczynnik;
    if (blue > 255)
        blue = 255;
    if (blue < 0)
        blue = 0;

    QColor color;
    color.setRed(red);
    color.setGreen(green);
    color.setBlue(blue);
    return color;
}

void Filtr_Gaussa::oblicz()
{
    double **tab;

    double sigma = ui->Slider->value() / 3.0;

    double pi = 3.14, suma = 0.0, E = 2.71828183;
    double pSigKwa = 2.0 * sigma * sigma * pi;
    double pierwSig = (double) sqrt(pSigKwa);

    tab = new double*[(ui->Slider->value() * 2  + 1)];
    for(int i=0; i<(ui->Slider->value() * 2  + 1); i++)
        tab[i] = new double[(ui->Slider->value() * 2  + 1)];

    for (int i = -ui->Slider->value(); i <= ui->Slider->value(); i++)
        for (int j = -ui->Slider->value(); j <= ui->Slider->value(); j++)
    {
        double a = 1.0 / pierwSig;
        double b = -1.0*((i*i)+(j*j))/(2*sigma*sigma);
        tab[i+(int)ui->Slider->value()][j+(int)ui->Slider->value()] = a*pow(E,b);

    }


    for(int i=0;i<(ui->Slider->value() * 2  + 1);i++)
        for(int j=0;j<(ui->Slider->value() * 2  + 1);j++)
                suma += (int)(100*tab[i][j]);


    if (suma==0)
        suma = 1;

    QColor **color;
    color = new QColor*[(ui->Slider->value() * 2  + 1)];
    for(int i=0;i<(ui->Slider->value() * 2  + 1);i++)
        color[i] = new QColor[(ui->Slider->value() * 2  + 1)];


    int SzerNowy = obrazek->width() + 2*ui->Slider->value();
    int WysNowy = obrazek->height() + 2*ui->Slider->value();
    int SzerStary = obrazek->width();
    int WysStary = obrazek->height();

    QImage *newObraz = new QImage(SzerNowy,WysNowy,QImage::Format_RGB32);

    int *pNowy, *pStary;

    pStary = (int*)obrazek->scanLine(0);
    for (int i = 0; i < ui->Slider->value(); i++){
        pNowy = (int*)newObraz->scanLine(i);

        for( int j = 0; j < ui->Slider->value(); j++ ) pNowy[j] = pStary[0];
        for( int j = SzerStary+ui->Slider->value(); j < SzerNowy; j++ ) pNowy[j] = pStary[SzerStary-1];
        memcpy(&(pNowy[ui->Slider->value()]),&(pStary[0]),4*SzerStary);
    }


    for (int i = 0; i < WysStary; i++){
        pStary = (int*)obrazek->scanLine(i);
        pNowy = (int*)newObraz->scanLine(i+ui->Slider->value());

        for( int j = 0; j < ui->Slider->value(); j++ ) pNowy[j] = pStary[0];
        for( int j = SzerStary+ui->Slider->value(); j < SzerNowy; j++ ) pNowy[j] = pStary[SzerStary-1];;
        memcpy(&(pNowy[ui->Slider->value()]),&(pStary[0]),4*SzerStary);
    }


    pStary = (int*)obrazek->scanLine(WysStary-1);
    for (int i = WysStary+ui->Slider->value()-1; i < WysNowy; i++){
        pNowy = (int*)newObraz->scanLine(i);

        for( int j = 0; j < ui->Slider->value(); j++ ) pNowy[j] = pStary[0];
        for( int j = SzerStary+ui->Slider->value(); j < SzerNowy; j++ ) pNowy[j] = pStary[SzerStary-1];
        memcpy(&(pNowy[ui->Slider->value()]),&(pStary[0]),4*SzerStary);
    }

    if (suma==0)
        suma = 1;


    //================
    tmpObrazek2 = newObraz->copy(0,0,newObraz->width(),newObraz->height());

    delete newObraz;

    QColor tmpC;
    int *p;

    for(int y=0;y<obrazek->height();y++)
    {
        p = (int*) obrazek->scanLine(y);

        for(int x=0;x<obrazek->width();x++)
        {
            for(int i=0;i<(ui->Slider->value() * 2  + 1);i++)
                for(int j=0;j<(ui->Slider->value() * 2  + 1);j++)
                    color[i][j].setRgb(tmpObrazek2.pixel(x+i,y+j));
            int r,g,b;
            r = g = b = 0;
            for(int i=0;i<(ui->Slider->value() * 2  + 1);i++)
            {
                for(int j=0;j<(ui->Slider->value() * 2  + 1);j++)
                {
                    r += color[i][j].red()*((int)(100*tab[i][j]));
                    g += color[i][j].green()*((int)(100*tab[i][j]));
                    b += color[i][j].blue()*((int)(100*tab[i][j]));
                }
            }

            b = b/suma;
            if (b>255) b = 255;
            if (b<0) b = 0;
            r = r/suma;
            if (r>255) r = 255;
            if (r<0) r = 0;
            g = g/suma;
            if (g>255) g = 255;
            if (g<0) g = 0;

            tmpC.setBlue(b);
            tmpC.setRed(r);
            tmpC.setGreen(g);

            p[x] = tmpC.rgb();
        }
    }
    emit sigUpdateImage();
}



void Filtr_Gaussa::zresetuj()
{
    *obrazek = tmpObrazek;

    ui->Slider->setValue(1);

    emit sigUpdateImage();
}
