#include "xyz.h"
#include "ui_xyz.h"

CIE::CIE(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CIE)
{
    ui->setupUi(this);

    setWindowTitle("CIE1931");
    ui->slider_x->setRange(-100, 100);
    ui->slider_x->setValue(0);
    ui->slider_y->setRange(-100, 100);
    ui->slider_y->setValue(0);
    ui->slider_z->setRange(-100, 100);
    ui->slider_z->setValue(0);


    connect(ui->slider_x, SIGNAL(valueChanged(int)), this, SLOT(ustawX(int)));
    connect(ui->slider_y, SIGNAL(valueChanged(int)), this, SLOT(ustawY(int)));
    connect(ui->slider_z, SIGNAL(valueChanged(int)), this, SLOT(ustawZ(int)));

    connect(ui->slider_x, SIGNAL(valueChanged(int)), this, SLOT(konwersja_aRGB()));
    connect(ui->slider_y, SIGNAL(valueChanged(int)), this, SLOT(konwersja_aRGB()));
    connect(ui->slider_z, SIGNAL(valueChanged(int)), this, SLOT(konwersja_aRGB()));

    connect(ui->Anuluj, SIGNAL(clicked()), this, SLOT(zresetuj()));
    connect(ui->OK, SIGNAL(clicked()), this, SLOT(close()));


    tabSqr = new float[256];
    tabSqrt = new float[256];

    for(int i=0;i<256;i++)
    {
        tabSqr[i] =  pow(i/255.0,2.2);
        tabSqrt[i] = pow(i/255.0,1/2.2);
     }
}

CIE::~CIE()
{
    delete ui;
}

// --------- pobieranie na label ---------------
void CIE::ustawX(int x){
    ui->w_x->setNum(x / 100.0);
}

void CIE::ustawY(int y){
    ui->w_y->setNum(y/100.0);
}

void CIE::ustawZ(int z){
    ui->w_z->setNum(z/100.0);
}
// -----------------------------------------------

void CIE::setImage(QImage *i){
    Obraz = i;
    tObraz = *i;
}

void CIE::zresetuj(){
    ui->slider_x->setValue(0);
    ui->slider_y->setValue(0);
    ui->slider_z->setValue(0);
    emit sigUpdateImage();
}

float CIE::od_do(float wart, float min, float max){
    if (wart < min)
        return min;
    if (wart > max)
        return max;
    else
        return wart;
}

void CIE::konwersja_aRGB(){
    //float gamma = 2.2;
    float TabR, TabB, TabG,  green, red , blue;
   // int r,g,b;
    QColor piksel;
    int *p, *pt;

    float aRGB[] = {0.57667,0.29734, 0.02703, 0.18556, 0.62736, 0.07069, 0.18823, 0.07529, 0.99134};
    float aXYZ[] = {2.04159, -0.96924, 0.01344, -0.56501, 1.87597, -0.11836, -0.34473, 0.04156, 1.01517};

    for(int y=0;y<Obraz->height();y++)
        {           
            pt =(int*) tObraz.scanLine(y);
            p = (int*) Obraz->scanLine(y);

            for(int x=0; x < Obraz->width(); x++)
                {
                    piksel.setRgb(pt[x]);

                    blue = tabSqr[piksel.blue()];
                    red = tabSqr[piksel.red()];
                    green = tabSqr[piksel.green()];

                        //rgb cie xyz

                    TabR = red*aRGB[0] + green*aRGB[3] +blue*aRGB[6] ;
                    TabG = red*aRGB[1] + green*aRGB[4] +blue*aRGB[7] ;
                    TabB = red*aRGB[2] + green*aRGB[5] +blue*aRGB[8] ;


                    TabR = od_do(TabR + ui->slider_x->value()/100.0, 0.0,1.0);
                    TabG = od_do(TabG + ui->slider_y->value()/100.0, 0.0,1.0);
                    TabB = od_do(TabB + ui->slider_z->value()/100.0, 0.0,1.0);

                        //cie xyz rgb

                    red = TabR*aXYZ[0] + TabG*aXYZ[3] +TabB*aXYZ[6] ;
                    green = TabR*aXYZ[1] + TabG*aXYZ[4] +TabB*aXYZ[7] ;
                    blue = TabR*aXYZ[2] + TabG*aXYZ[5] +TabB*aXYZ[8] ;

                    red = od_do(red,0.0,1.0);
                    green = od_do(green,0.0,1.0);
                    blue = od_do(blue,0.0,1.0);

                    piksel.setRgbF(tabSqrt[(int)(red*255.0)],tabSqrt[(int)(green*255.0)],tabSqrt[(int)(blue*255.0)]);
                    p[x] = piksel.rgb();
                }
        }


    emit sigUpdateImage();
}


void CIE::konwersja_sRGB(){
    float gamma = 2.2;
    float sRGB[] = {0.41242, 0.21266 , 0.01933, 0.35759, 0.71517, 0.11919, 0.18046, 0.07218, 0.95044};
    float sXYZ[] = {3.24071, -0.96925, 0.05563, -1.53726, 1.87599, -0.20399, -0.49857, 0.04155, 1.05707};

}

