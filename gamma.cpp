#include "gamma.h"
#include "ui_gamma.h"
#include <math.h>

bcdkorekcja::bcdkorekcja(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::bcdkorekcja)
{
    ui->setupUi(this);

    setWindowTitle("Jasnosc Kontrast Gamma");

    ui->ok->setText("OK");
    ui->anuluj->setText("Zerowanie");
    ui->label->setText("Jasnosc");
    ui->label_2->setText("Kontrast");
    ui->label_3->setText("Gamma");


    ui->horizontalSlider_1->setValue(0);
    ui->horizontalSlider_3->setValue(0);
    ui->horizontalSlider_2->setValue(10);

    ui->horizontalSlider_1->setRange(-255, 255);
    ui->horizontalSlider_3->setRange(-127, 127);
    ui->horizontalSlider_2->setRange(-0, 19);

    ui->label_4->setNum(0);
    ui->label_5->setNum(0);
    ui->label_6->setNum(0);

    connect(ui->horizontalSlider_1, SIGNAL(valueChanged(int)), this->ui->label_4, SLOT(setNum(int)));
    connect(ui->horizontalSlider_1, SIGNAL(valueChanged(int)), this, SLOT(wykonaj()) );

    connect(ui->horizontalSlider_3, SIGNAL(valueChanged(int)), this->ui->label_5, SLOT(setNum(int)));
    connect(ui->horizontalSlider_3, SIGNAL(valueChanged(int)), this, SLOT(wykonaj()) );

    connect(ui->horizontalSlider_2, SIGNAL(valueChanged(int)), this, SLOT(wartGamma(int)));
    connect(ui->horizontalSlider_2, SIGNAL(valueChanged(int)), this, SLOT(wykonaj()) );

// --- przyciski ---
    connect(ui->ok, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->anuluj, SIGNAL(clicked()), this, SLOT(zresetuj()));
// -----------------
    stworztablice();


 }
bcdkorekcja::~bcdkorekcja()
{
    delete ui;
}


void bcdkorekcja::setImage(QImage *im)
{
    obraz = im;
    tObraz = *im;
}


void bcdkorekcja::wartGamma(int i){
    if (i<10)
           ui->label_6->setNum((double)i/10);
       else
           ui->label_6->setNum(i-9);
}

// ----------------------------------------------


    void bcdkorekcja:: stworztablice(){
        tab = new double*[256];

        for (int i=0; i<256; ++i)
            {
                tab[i] = new double[19];
            }

        for (int i=0; i<256; ++i)
            {
                for(int j=0;j<9;j++)
                    tab[i][j] = round( pow(i/255.0,10.0/(j+1))*255.0 );
                for(int j = 9; j < 19; j++ )
                    tab[i][j] = round( pow(i/255.0,1.0/(j-8))*255.0 );
            }

    }


    int bcdkorekcja::zakres(int wartosc, int min, int max)
    {
        if(wartosc>max)
        {
            return max;
        }
        else
        {
            if(wartosc<min)
            {
                return min;
            }
            else
                return wartosc;
        }
    }

 // ------------------------------------------

    void bcdkorekcja:: wykonaj(){
        *obraz = tObraz;
        uchar *p;

        for(int y=0; y < obraz->height(); ++y)
        {
            p = obraz->scanLine(y);
            for(int x=0; x < 4*obraz->width(); ++x)
            {
                p[x] = zakres(p[x] + ui->horizontalSlider_1->value(), 0,255);
                p[x] = zakres(p[x] + ui->horizontalSlider_3->value() - ((p[x] * ui->horizontalSlider_3->value()) / 127), 0,255);
                p[x] = tab[p[x]][ui->horizontalSlider_2->value()-1];
            }
        }

        emit sigUpdateImage();
    }

    void bcdkorekcja::zresetuj(){

        ui->horizontalSlider_1->setValue(0);
        ui->horizontalSlider_3->setValue(0);
        ui->horizontalSlider_2->setValue(10);

        emit sigUpdateImage();
    }
