#include "cmyk.h"
#include "ui_cmyk.h"

rgb_na_cmyk::rgb_na_cmyk(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::rgb_na_cmyk)
{
    ui->setupUi(this);

    setWindowTitle("Cyan Magenta Yellow blacK");


    ui->horizontalSlider_c->setRange(-255,255);
    ui->horizontalSlider_m->setRange(-255,255);
    ui->horizontalSlider_y->setRange(-255,255);
    ui->horizontalSlider_k->setRange(-255,255);


    connect(ui->horizontalSlider_c, SIGNAL(valueChanged(int)), this->ui->label_c, SLOT(setNum(int)));
    connect(ui->horizontalSlider_c, SIGNAL(valueChanged(int)), this, SLOT(cmyk()));

    connect(ui->horizontalSlider_m, SIGNAL(valueChanged(int)), this->ui->label_m, SLOT(setNum(int)));
    connect(ui->horizontalSlider_m, SIGNAL(valueChanged(int)), this, SLOT(cmyk()));

    connect(ui->horizontalSlider_y, SIGNAL(valueChanged(int)), this->ui->label_y, SLOT(setNum(int)));
    connect(ui->horizontalSlider_y, SIGNAL(valueChanged(int)), this, SLOT(cmyk()));

    connect(ui->horizontalSlider_k, SIGNAL(valueChanged(int)), this->ui->label_b, SLOT(setNum(int)));
    connect(ui->horizontalSlider_k, SIGNAL(valueChanged(int)), this, SLOT(cmyk()));

    connect(ui->anuluj, SIGNAL(clicked()), this, SLOT(zresetuj()));
    connect(ui->OK, SIGNAL(clicked()),this, SLOT(close()));

}

rgb_na_cmyk::~rgb_na_cmyk()
{
    delete ui;
}

void rgb_na_cmyk::changeEvent(QEvent *e){
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void rgb_na_cmyk::setImage(QImage *im)
{
    obraz = im;
    tObraz = *im;
}

void rgb_na_cmyk::zresetuj(){

        ui->horizontalSlider_c->setValue(0);
        ui->horizontalSlider_k->setValue(0);
        ui->horizontalSlider_m->setValue(0);
        ui->horizontalSlider_y->setValue(0);

        emit sigUpdateImage();
}



//---------------------------------------------------------


double rgb_na_cmyk::min(double a,double b)
{
    if (a < b)
    {
        return a;
    }
    else
        return b;
}

void rgb_na_cmyk::cmyk(){
    QColor piksel;
         double cyjan,magenta,yellow,black;
         int red, green, blue;

    for(int i = 0; i<obraz->height(); i++){
        for(int j = 0; j<obraz->width(); j++){

            piksel = tObraz.pixel(j, i);
             red = piksel.red();
             green = piksel.green();
             blue = piksel.blue();

            // ------------------------------------------------------
             cyjan = 1.0 -(red / 255.0);
             magenta = 1.0 - (green / 255.0);
             yellow = 1.0 - (blue / 255.0);
            // ------------------------------------------------------

            black = min(min(cyjan,magenta),yellow) + ui->horizontalSlider_k->value()/255.0;
            black = (black > 1.0) ?1.0: (black < 0) ?0:black;

            cyjan =(cyjan - black) / (1.0 - black);
            cyjan = cyjan + (ui->horizontalSlider_c->value()/255.0);
            magenta = (magenta - black) / (1.0 - black);
            magenta = magenta + (ui->horizontalSlider_m->value()/255.0);
            yellow = (yellow - black) / (1.0 - black);
            yellow = yellow + (ui->horizontalSlider_y->value()/255.0);
            black=black+(ui->horizontalSlider_k->value())/255.0;

            cyjan =  cyjan*(1.0 - black) + black;
            magenta = magenta * (1.0 - black) + black;
            yellow = yellow * (1.0 - black) + black;

            cyjan = (cyjan > 1.0) ?1.0: (cyjan < 0) ?0:cyjan;
            yellow = (yellow > 1.0) ?1.0: (yellow < 0) ?0:yellow;
            magenta = (magenta > 1.0) ?1.0: (magenta < 0) ?0:magenta;

            red = 1 - cyjan;
            green = 1 - magenta;
            blue = 1 - yellow;

            red =(int) ((1.0-cyjan)*255.0);
            blue =(int) ((1.0-yellow)*255.0);
            green =(int) ((1.0-magenta)*255.0);

            piksel.setRgb(red, green, blue);
            obraz->setPixel(j,i, piksel.rgb());

        }

    }
    emit sigUpdateImage();
}
