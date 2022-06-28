#include "nieliniowe.h"
#include "ui_nieliniowe.h"
#include <iostream>
#include <algorithm>
#include <vector>

Filtry_Nieliniowe::Filtry_Nieliniowe(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Filtry_Nieliniowe)
{
    ui->setupUi(this);

    setWindowTitle("Filtry nieliniowe");

    ui->spinBox->setValue(1);

    connect(ui->pMaximum, SIGNAL(clicked()), this, SLOT(maximum()));
    connect(ui->pMediana, SIGNAL(clicked()), this, SLOT(mediana()));
    connect(ui->pMinimum, SIGNAL(clicked()), this, SLOT(minimum()));
    connect(ui->pAnuluj, SIGNAL(clicked()), this, SLOT(cancel()));
    connect(ui->pOk, SIGNAL(clicked()), this, SLOT(close()));
}

Filtry_Nieliniowe::~Filtry_Nieliniowe()
{
    delete ui;
}

// ----------- funkcje -------------------

void Filtry_Nieliniowe::setImage(QImage *im)
{
    image = im;
    tmpImage = *image;
}

void Filtry_Nieliniowe::cancel(){
    *image = tmpImage;
    emit sigUpdateImage();
}
bool colorCompare(QColor c1, QColor c2)
{
    int v1 = (77 * c1.red() + 150 * c1.green() + 29 * c1.blue()) >> 8;
    int v2 = (77 * c2.red() + 150 * c2.green() + 29 * c2.blue()) >> 8;
    return v1<v2;
}

QColor medC(QColor** c,int size)
{
    QVector<QColor> *med = new QVector<QColor>();
    med->clear();
    for(int i=0;i<size;i++)
        for(int j=0;j<size;j++)
            med->push_back(c[i][j]);


//    return med->at(size/2);

    std::nth_element(med->begin(),med->begin()+(med->size()/2),med->end(),colorCompare);

    return med->at((size*size)/2);
}



void Filtry_Nieliniowe::maximum(){

    int ileOdjac = (ui->spinBox->value()-1)/2;
    QRgb rgb;


for (int i=ileOdjac; i<image->width()-ileOdjac; ++i)
    for (int j=ileOdjac; j<image->height()-ileOdjac; ++j)
        {
            int rmax = 0;
            int gmax = 0;
            int bmax = 0;
            for (int k=0; k<ui->spinBox->value(); k++)
                for (int l=0; l<ui->spinBox->value(); l++)
                    {
                        if (rmax < qRed(image->pixel(i+k-ileOdjac,j+l-ileOdjac)))
                            rmax = qRed(image->pixel(i+k-ileOdjac,j+l-ileOdjac));
                        if (gmax < qGreen(image->pixel(i+k-ileOdjac,j+l-ileOdjac)))
                            gmax = qGreen(image->pixel(i+k-ileOdjac,j+l-ileOdjac));
                        if (bmax < qBlue(image->pixel(i+k-ileOdjac,j+l-ileOdjac)))
                            bmax = qBlue(image->pixel(i+k-ileOdjac,j+l-ileOdjac));
                    }
            rgb = qRgb(rmax,gmax,bmax);
            image->setPixel(i-ileOdjac,j-ileOdjac,rgb);
        }

        emit sigUpdateImage();
}

void Filtry_Nieliniowe::minimum(){
    QRgb rgb;
    int ileOdjac = ((ui->spinBox->value()-1)/2);

    for (int i = ileOdjac; i < image->width()-ileOdjac; ++i)
      for (int j = ileOdjac; j < image->height()-ileOdjac; ++j)
        {
            int rmin = 255;
            int gmin = 255;
            int bmin = 255;
            for (int k = 0; k < ui->spinBox->value(); k++)
                for (int l = 0; l < ui->spinBox->value(); l++)
                    {
                        if (rmin > qRed(image->pixel(i+k-ileOdjac,j+l-ileOdjac))) rmin = qRed(image->pixel(i+k-ileOdjac,j+l-ileOdjac));
                        if (gmin > qGreen(image->pixel(i+k-ileOdjac,j+l-ileOdjac))) gmin = qGreen(image->pixel(i+k-ileOdjac,j+l-ileOdjac));
                        if (bmin > qBlue(image->pixel(i+k-ileOdjac,j+l-ileOdjac))) bmin = qBlue(image->pixel(i+k-ileOdjac,j+l-ileOdjac));
                    }
            rgb = qRgb(rmin,gmin,bmin);
            image->setPixel(i-ileOdjac,j-ileOdjac,rgb);

        }
    emit sigUpdateImage();

}

void Filtry_Nieliniowe::mediana(){
    int s = ui->spinBox->value();

    int *p;

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

    // topButton
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
    //bez krawedzir
    for(int y=0;y<image->height();y++)
    {
        p = (int*) image->scanLine(y);
        //wypelnienie kolorami sasiadow
        for(int x=0;x<image->width();x++)
        {
            for(int i=0;i<s;i++)
                for(int j=0;j<s;j++)
                    color[i][j].setRgb(tmpImage2.pixel(x+i,y+j));
            p[x] = medC(color,s).rgb();
        }
    }
    emit sigUpdateImage();
}
