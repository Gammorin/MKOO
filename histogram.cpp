#include "histogram.h"
#include "ui_histogram.h"
#include <math.h>

#include <iostream>
using namespace std;

histogram::histogram(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::histogram)
{
    ui->setupUi(this);

    setWindowTitle("Histogram");


    tab_v = new int[256];
    tab_red = new int[256];
    tab_green = new int[256];
    tab_blue = new int [256];

    // zerowanie tablic
    for (int i = 0; i<256; i++){
        tab_v[i] = 0;
        tab_red[i] = 0;
        tab_green[i] = 0;
        tab_blue[i] = 0;
    }

    connect(ui->ok, SIGNAL(clicked()), this, SLOT(close()));

}

histogram::~histogram()
{
    delete ui;
}

void histogram::setImage(QImage *im)
{
    obraz = im;
    tObraz = *im;
}


void histogram::zczytaj(QImage *image){


    int *poczatek;
    QColor color;
    for (int y=0; y < image->height(); y++)
    {

        poczatek = (int*) image->scanLine(y);

        for (int x=0; x < image->width(); x++)
        {
            color.setRgb(poczatek[x]);
            tab_v[color.value()]++;
            tab_red[color.red()]++;
            tab_green[color.green()]++;
            tab_blue[color.blue()]++;
        }
    }



    max = 0 ;
    for(int x =1; x<=255; x++)
    {
        if(tab_red[x]>max)
            max=tab_red[x];
    }
    for(int x =1; x<=255; x++)
    {
        if(tab_green[x]>max)
            max=tab_green[x];
    }
    for(int x =1; x<=255; x++)
    {
        if(tab_blue[x]>max)
            max=tab_blue[x];
    }
    for(int x =1; x<=255; x++)
    {
        if(tab_v[x]>max)
            max=tab_v[x];
    }

    if(max==0)max=1;
}


void histogram::paintEvent( QPaintEvent * )
{

    QPainter poczatek;
    poczatek.begin(this);
    poczatek.setBackground(Qt::white);
    QTransform trans;
    trans.translate(50,40);
    poczatek.setTransform(trans);
    poczatek.fillRect ( 0, 0,  255,  255,  Qt::white  );


    {
        QPainter painter;
        painter.begin(this);
        painter.translate(50, 40);
        for(int i=1; i<256;i++)
        {

            double j = (tab_v[i]/max)*255;


            QColor kolor(0, 0, 0);
            painter.setPen(kolor);
            painter.drawLine(i,255,i,255-j);
        }
        painter.end();
    }


    {
        QPainter painter;
        painter.begin(this);
        painter.translate(50, 40);
        for(int i=1; i<256;i++)
        {

            double j = (tab_red[i]/max)*255;


            QColor kolor(255, 0, 0);
            painter.setPen(kolor);
            painter.drawLine(i,255,i,255-j);
        }
        painter.end();
    }


    {
        QPainter painter;
        painter.begin(this);
        painter.translate(50, 40);
        for(int i=1; i<256;i++)
        {

            double j = (tab_green[i]/max)*255;


            QColor kolor(0, 255, 0);
            painter.setPen(kolor);
            painter.drawLine(i,255,i,255-j);
        }
        painter.end();
    }

    {
        QPainter painter;
        painter.begin(this);
        painter.translate(50, 40);
        for(int i=1; i<256;i++)
        {

            double j = (tab_blue[i]/max)*255;


            QColor kolor(0, 0, 255);
            painter.setPen(kolor);
            painter.drawLine(i,255,i,255-j);
        }
        painter.end();
    }
    poczatek.end();
}



