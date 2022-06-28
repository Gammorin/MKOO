#include "lab.h"
#include "ui_lab.h"
#include <math.h>


Lab::Lab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Lab)
{
    ui->setupUi(this);

     setWindowTitle("LAB");
    // ********  ustawienie wartosci sliderow ******
    ui->l_slider->setRange(-100, 100);
    ui->l_slider->setValue(0);

    ui->a_slider->setRange(-128, 127);
    ui->a_slider->setValue(0);

    ui->b_slider->setRange(-128, 127);
    ui->b_slider->setValue(0);

    //******** połączenia ********
    connect(ui->pAnuluj, SIGNAL(clicked()), this, SLOT(zresetuj()));
    connect(ui->pOK, SIGNAL(clicked()), this, SLOT(close()));


    connect(ui->l_slider, SIGNAL(valueChanged(int)), this->ui->label_L, SLOT(setNum(int)));
    connect(ui->a_slider, SIGNAL(valueChanged(int)), this->ui->label_A, SLOT(setNum(int)));
    connect(ui->b_slider, SIGNAL(valueChanged(int)), this->ui->label_B, SLOT(setNum(int)));

    connect(ui->l_slider, SIGNAL(valueChanged(int)), this, SLOT(glowna_funkcja()));
    connect(ui->a_slider, SIGNAL(valueChanged(int)), this, SLOT(glowna_funkcja()));
    connect(ui->b_slider, SIGNAL(valueChanged(int)), this, SLOT(glowna_funkcja()));

    //******** tablice ***********
    tSqrt = new float[256];
    tSqr = new float[256];
    tL = new float[1000];

    for(int i=0;i<256;i++)
    {
            tSqrt[i] = pow(i/256.0,1/2.2);
            tSqr[i] =  pow(i/256.0,2.2);

    }
}//Lab


Lab::~Lab()
{
    delete ui;
}

//----------------------------------------------------------------------------------------
void Lab::changeEvent(QEvent *e){
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void Lab::setImage(QImage *im)
{
    Obraz = im;
    tObraz = *im;
}

void Lab::zresetuj(){
    ui->l_slider->setValue(0);
    ui->a_slider->setValue(0);
    ui->b_slider->setValue(0);
    emit sigUpdateImage();
}


double Lab::funkX(double x){
    double E = 0.008856;
    double K = 903.3;

    if ( x > E )
    {
        return (pow(x,1.0/3.0));
    }

    else
    {
        return ( (K * x + 16)/116 );
    }
}//funkX

double Lab::funkY(double y){
    double E = 0.008856;
    double K = 903.3;

    if ( y > E )
    {
        return (pow(y,1.0/3.0));
    }

    else
    {
        return ( (K * y + 16)/116 );
    }
}

double Lab::funkZ(double z){
    double E = 0.008856;
    double K = 903.3;

    if ( z > E )
    {
        return (pow(z,1.0/3.0));
    }

    else
    {
        return ( (K * z + 16)/116 );
    }
}

float Lab::funkX2(float L,float a,float yr){
    return (a/500.0)+funkY2(L,yr);
}

float Lab::funkY2(float L, float yr){
    double E = 0.008856;
    double K = 903.3;

        if(yr>E)
                return (L+16)/116.0;
        else
                return (K*yr+16)/116.0;
}//funkY2

float Lab::funkZ2(float L, float b, float yr){
    return funkY2(L,yr) - (b/200.0);
}//funkZ2

float* Lab::multiply(float r,float g,float b,float *M)
{
        float *ret = new float[3];
        ret[0] = r*M[0]+g*M[1]+b*M[2];
        for(int i=0;i<3;i++)
                ret[i] = r*M[i]+g*M[i+3]+b*M[i+6];
        return ret;
}//multiply

float Lab::zakres(float v,float min,float max)
{
    if(v>max) return max;
    if(v<min) return min;
    return v;
}//zakres


void Lab::glowna_funkcja(){
    QColor color;
    int *p,*pt;
    float lval,aval,bval;
    float *tab;
    float fxval,fzval;
    float Mrgb[9] = {0.576700, 0.297361,  0.0270328,  0.185556, 0.627355,  0.0706879,  0.188212, 0.0752847, 0.991248};
    float Mxyz[9] = {2.04148, -0.969258, 0.0134455,   -0.564977, 1.87599, -0.118373,   -0.344713, 0.0415557, 1.01527};


    for(int y=0;y<Obraz->height();y++)
    {
            p = (int*) Obraz->scanLine(y);
            pt =(int*) tObraz.scanLine(y);
            for(int x=0;x<Obraz->width();x++)
            {
                    color.setRgb(pt[x]);
                    //rgb to cie xyz

                    tab = multiply(tSqr[color.red()],tSqr[color.green()],tSqr[color.blue()],Mrgb);


                    //cie xyz to cie lab
                    lval = 116*funkY(tab[1])-16;
                    aval = 500*(funkX(tab[0])-funkY(tab[1]));
                    bval = 200*(funkY(tab[1])-funkZ(tab[2]));

                    lval = zakres(lval + (ui->l_slider->value()), 0.0,100.0);
                    aval = zakres(aval + (ui->a_slider->value()),-128.0,127.0);
                    bval = zakres(bval + (ui->b_slider->value()),-128.0,127.0);

                    //cie lab to cie xyz
                    if(lval>(0.008856*903.3))
                            tab[1] = pow((lval + 16)/116,3.0);
                    else
                            tab[1] = lval/903.3;

                    fxval = funkX2(lval,aval,tab[1]);
                    fzval = funkZ2(lval,bval,tab[1]);

                    if(pow(fxval,3.0)>0.008856)
                            tab[0] = pow(fxval,3);
                    else
                            tab[0] = (116*fxval-16)/903.3;

                    if(pow(fzval,3.0)>0.008856)
                            tab[2] = pow(fzval,3.0);
                    else
                            tab[2] = (116*fzval-16)/903.3;

                    tab[0] = 0.9505 * tab[0];
                    tab[2] = 1.0891 * tab[2];

                    //cie xyz to rgb
                    tab = multiply(tab[0],tab[1],tab[2],Mxyz);

                    for(int i=0;i<3;i++)
                            tab[i] = zakres(tab[i],0.0,1.0);

                    color.setRgbF(tSqrt[(int)(tab[0]*255.0)],tSqrt[(int)(tab[1]*255.0)],tSqrt[(int)(tab[2]*255.0)]);
                    p[x] = color.rgb();
            }
    }
    emit sigUpdateImage();
}
