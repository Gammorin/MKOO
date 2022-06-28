#include "unsharpmask.h"
#include "ui_unsharpmask.h"

#include <math.h>

#define PI 3.14159265
#define E 2.71828183

UnsharpMask::UnsharpMask(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UnsharpMask)
{
    ui->setupUi(this);

     setWindowTitle("UnsharpMask");

    ui->sigmaSlider->setRange(0,100);
    ui->alfaSlider->setRange(1,4999);

    ui->sig->setNum(0);
    ui->al->setNum(0.001);

    ui->spinBox->setValue(3);

    connect(ui->pOk, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->pAnuluj, SIGNAL(clicked()), this, SLOT(cancel()));
    connect(ui->sigmaSlider, SIGNAL(valueChanged(int)), this, SLOT(label1(int)));
    connect(ui->alfaSlider, SIGNAL(valueChanged(int)), this, SLOT(label2(int)));
    connect(ui->pPrzycisk, SIGNAL(clicked()), this, SLOT(oblicz()));
}

UnsharpMask::~UnsharpMask()
{
    delete ui;
}


void UnsharpMask::label1(int cos)
{
    ui->sig->setNum(cos/100.0);
}

void UnsharpMask::label2(int cos)
{
    ui->al->setNum(cos/1000.0);
}


void UnsharpMask::setImage(QImage *im)
{
    image = im;
    tmpImage = *im;
}

void UnsharpMask::cancel()
{
    *image = tmpImage;

    ui->sigmaSlider->setValue(0);;
    ui->alfaSlider->setValue(0.001);
    ui->spinBox->setValue(3);

    emit sigUpdateImage();
}

void UnsharpMask::oblicz()
{    
    int s=ui->spinBox->value();
    double sig = ui->sigmaSlider->value()/100.0;

    double fi,se;

    int *p,*pt,suma;

    suma = 0;
    tablica = new double*[s];
    for(int i=0;i<s;i++)
        tablica[i] = new double[s];

    for(int i=-s/2;i<=s/2;i++)
        for(int j=-s/2;j<=s/2;j++)
        {
            fi = 1.0/(2*PI*sig*sig);
            se = -1.0*((i*i)+(j*j))/(2*sig*sig);
            tablica[i+s/2][j+s/2] = fi*pow(E,se);
        }

    for(int i=0;i<s;i++)
        for(int j=0;j<s;j++)
            suma += (int)(100*tablica[i][j]);

    if (suma==0)
        suma = 1;

    QColor **color;
    color = new QColor*[s];
    for(int i=0;i<s;i++)
        color[i] = new QColor[s];


    int r = s / 2;
    int wNew = image->width() + 2*r;
    int hNew = image->height() + 2*r;
    int wOld = image->width();
    int hOld = image->height();

    QImage *newImage = new QImage(wNew,hNew,QImage::Format_RGB32);

    int *pOld, *pNew;

    // top
    pOld = (int*)image->scanLine(0);
    for (int i = 0; i < r; i++){
        pNew = (int*)newImage->scanLine(i);

        for( int j = 0; j < r; j++ ) pNew[j] = pOld[0];
        for( int j = wOld+r; j < wNew; j++ ) pNew[j] = pOld[wOld-1];
        memcpy(&(pNew[r]),&(pOld[0]),4*wOld);
    }

    // middle
    for (int i = 0; i < hOld; i++){
        pOld = (int*)image->scanLine(i);
        pNew = (int*)newImage->scanLine(i+r);

        for( int j = 0; j < r; j++ ) pNew[j] = pOld[0];
        for( int j = wOld+r; j < wNew; j++ ) pNew[j] = pOld[wOld-1];;
        memcpy(&(pNew[r]),&(pOld[0]),4*wOld);
    }

    //bottom
    pOld = (int*)image->scanLine(hOld-1);
    for (int i = hOld+r-1; i < hNew; i++){
        pNew = (int*)newImage->scanLine(i);

        for( int j = 0; j < r; j++ ) pNew[j] = pOld[0];
        for( int j = wOld+r; j < wNew; j++ ) pNew[j] = pOld[wOld-1];
        memcpy(&(pNew[r]),&(pOld[0]),4*wOld);
    }

    tmpImage2 = newImage->copy(0,0,newImage->width(),newImage->height());

    delete newImage;

    QColor tmpC;


    //bez krawedzi
    for(int y=0;y<image->height();y++)
    {
        p = (int*) image->scanLine(y);
        //wypelnienie kolorami sasiadow
        for(int x=0;x<image->width();x++)
        {
            for(int i=0;i<s;i++)
                for(int j=0;j<s;j++)
                    color[i][j].setRgb(tmpImage2.pixel(x+i,y+j));
            int r,g,b;
            r = g = b = 0;
            for(int i=0;i<s;i++)
            {
                for(int j=0;j<s;j++)
                {
                    r += color[i][j].red()*((int)(100*tablica[i][j]));
                    g += color[i][j].green()*((int)(100*tablica[i][j]));
                    b += color[i][j].blue()*((int)(100*tablica[i][j]));
                }
            }
            r = r/suma;
            if (r>255) r = 255;
            if (r<0) r = 0;
            g = g/suma;
            if (g>255) g = 255;
            if (g<0) g = 0;
            b = b/suma;
            if (b>255) b = 255;
            if (b<0) b = 0;
            tmpC.setRed(r);
            tmpC.setGreen(g);
            tmpC.setBlue(b);
            p[x] = tmpC.rgb();
        }
    }

    QColor tmpCG;
    double a = ui->alfaSlider->value()/1000.0;
    for(int y=0;y<image->height();y++)
    {
        p = (int*) image->scanLine(y);
        pt = (int*) tmpImage.scanLine(y);
        for(int x=0;x<image->width();x++)
        {
            int r,g,b;
            tmpCG.setRgb(p[x]);
            tmpC.setRgb(pt[x]);
            r = (int)(a*(tmpC.red()-tmpCG.red())+tmpC.red());
            g = (int)(a*(tmpC.green()-tmpCG.green())+tmpC.green());
            b = (int)(a*(tmpC.blue()-tmpCG.blue())+tmpC.blue());
            if (r>255) r = 255;
            if (r<0) r = 0;
            if (g>255) g = 255;
            if (g<0) g = 0;
            if (b>255) b = 255;
            if (b<0) b = 0;
            tmpC.setRed(r);
            tmpC.setBlue(b);
            tmpC.setGreen(g);
            p[x] = tmpC.rgb();
        }
    }
    emit sigUpdateImage();
}
