#include "test.h"
#include "ui_test.h"

Test::Test(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Test)
{
    ui->setupUi(this);

    connect(ui->klik_cz, SIGNAL(clicked()), this, SLOT(k_czerwony()));
    connect(ui->niebieski, SIGNAL(clicked()), this, SLOT(k_niebieski()));
    connect(ui->green, SIGNAL(clicked()), this, SLOT(k_zielony()));
}//Test

Test::~Test()
{
    delete ui;
}


//--------------------------------------------------------------

void Test::setImage(QImage *im){
    Obraz = im;
    tObraz = *im;
}

void Test::k_czerwony(){
    *Obraz = tObraz;
    uchar *p;
    p = Obraz->scanLine(1);

    emit sigUpdateImage();
}

void Test::k_niebieski(){
    int red;
    double konw;
    QColor piks;




        //------------------------------
        *Obraz = tObraz;
        uchar *p;                   // uchar -bez znaku

        for(int y=0; y <Obraz->height(); ++y)
        {
           // p = Obraz->scanLine(y);
            for(int x=0; x <Obraz->width(); ++x)
            {
                piks = tObraz.pixel(x, y);
                //konw = piks.red();
               // konw = konw / 255;
                red = piks.red();
                ui->wynik_r->setNum(red);

                piks.setRgb(0, 155,0);
                Obraz->setPixel(x, y, piks.rgb());
            }
        }


    emit sigUpdateImage();
}

void Test::k_zielony(){

}
