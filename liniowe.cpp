#include "liniowe.h"
#include "ui_liniowe.h"

Filtry_Liniowe::Filtry_Liniowe(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Filtry_Liniowe)
{
    ui->setupUi(this);

    setWindowTitle("Filtry liniowe");

    connect(ui->spinBox_wartMaski, SIGNAL(valueChanged(int)), this , SLOT(jakaMaska(int)));
    connect(ui->liczFiltr,SIGNAL(clicked()),this,SLOT(mask()));
    connect(ui->pAnuluj, SIGNAL(clicked()), this, SLOT(cancel()));
    connect(ui->pOk, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->pCzysc, SIGNAL(clicked()),this, SLOT(czysc()));


    connect(ui->radio_rozmyw, SIGNAL(clicked()), this, SLOT(jakiFiltr()));
    connect(ui->radio_gorno, SIGNAL(clicked()), this, SLOT(jakiFiltr()));
    connect(ui->radio_dolno, SIGNAL(clicked()), this, SLOT(jakiFiltr()));
    connect(ui->radio_gauss, SIGNAL(clicked()), this, SLOT(jakiFiltr()));
    connect(ui->radio_piw0st, SIGNAL(clicked()), this, SLOT(jakiFiltr()));
    connect(ui->radio_piw90st, SIGNAL(clicked()), this, SLOT(jakiFiltr()));
    connect(ui->radio_zeruj, SIGNAL(clicked()), this, SLOT(jakiFiltr()));
    connect(ui->radio_plasko, SIGNAL(clicked()), this, SLOT(jakiFiltr()));
    connect(ui->radio_sob0st, SIGNAL(clicked()), this, SLOT(jakiFiltr()));
    connect(ui->radio_sob90st, SIGNAL(clicked()), this, SLOT(jakiFiltr()));
    connect(ui->radio_plasko, SIGNAL(clicked()), this, SLOT(jakiFiltr()));

    ui->spinBox_wartMaski->setRange(3,9);
    ui->spinBox_wartMaski->setValue(3);
    this->jakaMaska(3);



}

Filtry_Liniowe::~Filtry_Liniowe()
{
    delete ui;
}

void Filtry_Liniowe::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void Filtry_Liniowe::setImage(QImage *im)
{
    image = im;
    tImage = *im;
}

void Filtry_Liniowe::cancel()
{
    *image = tImage;
    emit sigUpdateImage();
}

QColor Filtry_Liniowe::wstawKolor(int size, QColor** kolor, int** tabMaska, int wagaM)
{
    QColor kol;
    int red = 0;
    int green = 0;
    int blue = 0;

    for(int i=0;i<size;i++)
    {
        for(int j=0;j<size;j++)
        {
            red += kolor[i][j].red()*tabMaska[i][j];
            green += kolor[i][j].green()*tabMaska[i][j];
            blue += kolor[i][j].blue()*tabMaska[i][j];
        }
    }

    red = red / wagaM;
    if (red > 255)
        red = 255;
    if (red < 0)
        red = 0;

    green = green / wagaM;
    if (green > 255)
        green = 255;
    if (green < 0)
        green = 0;

    blue = blue / wagaM;
    if (blue > 255)
        blue = 255;
    if (blue < 0)
        blue = 0;


    kol.setRed(red);
    kol.setGreen(green);
    kol.setBlue(blue);
    return kol;
}


void Filtry_Liniowe::mask()
{

    if (ui->spinBox_wartMaski->value() == 1) return;
    int **tablica;

    int wagaMaski = 0;  // suma wszystkich skladnikow pol maski

    tablica = new int*[ui->spinBox_wartMaski->value()];
    for(int i=0; i<ui->spinBox_wartMaski->value(); i++)
        tablica[i] = new int[ui->spinBox_wartMaski->value()];

    for(int i=0; i<ui->spinBox_wartMaski->value(); i++)
        for(int j=0; j<ui->spinBox_wartMaski->value() ;j++)
        {
            QTableWidgetItem *WarKom = ui->maska->item(i,j);
            if (WarKom != NULL)
            {
                tablica[i][j] = WarKom->text().toDouble();
                wagaMaski += tablica[i][j];
            }
        }

    if (wagaMaski == 0)
        wagaMaski = 1;

    int *p;
    QColor **color;
    color = new QColor*[ui->spinBox_wartMaski->value()];
    for(int i=0; i<ui->spinBox_wartMaski->value(); i++)
        color[i] = new QColor[ui->spinBox_wartMaski->value()];

    //tworzenie wymiaru nowego obrazka (+dodatkowe rzedy pikseli potrzebne do splotu)

         cout<<"wartosc maski = "<<ui->spinBox_wartMaski->value()<<endl;
    int ileDodac = ui->spinBox_wartMaski->value() / 2;
         cout<<"ileDodac = "<<ileDodac<<endl;
    int SzerNowy = image->width() + 2*ileDodac;
         cout<<"SzerNowy = "<<SzerNowy<<endl;
    int WysNowy = image->height() + 2*ileDodac;
    int SzerStary = image->width();
    int WysStary = image->height();

    //--------------------------------------------

    QImage *newImage = new QImage(SzerNowy,WysNowy,QImage::Format_RGB32);

    int *pOld, *pNew;


    pOld = (int*)image->scanLine(0);
    for (int i = 0; i < ileDodac; i++){
        pNew = (int*)newImage->scanLine(i);

    for( int j = 0; j < ileDodac; j++ )
        pNew[j] = pOld[0];
    for( int j = SzerStary + ileDodac; j < SzerNowy; j++ )
        pNew[j] = pOld[SzerStary-1];

        memcpy(&(pNew[ileDodac]),&(pOld[0]),4*SzerStary);
    }


    for (int i = 0; i < WysStary; i++)
    {
        pOld = (int*)image->scanLine(i);
        pNew = (int*)newImage->scanLine(i+ileDodac);

        for( int j = 0; j < ileDodac; j++ )
            pNew[j] = pOld[0];
        for( int j = SzerStary + ileDodac; j < SzerNowy; j++ )
            pNew[j] = pOld[SzerStary-1];

        memcpy(&(pNew[ileDodac]),&(pOld[0]),4*SzerStary);
    }


    pOld = (int*)image->scanLine(WysStary-1);
    for (int i = WysStary + ileDodac-1; i < WysNowy; i++){
        pNew = (int*)newImage->scanLine(i);

        for( int j = 0; j < ileDodac; j++ )
            pNew[j] = pOld[0];
        for( int j = SzerStary + ileDodac; j < SzerNowy; j++ )
            pNew[j] = pOld[SzerStary-1];

        memcpy(&(pNew[ileDodac]),&(pOld[0]),4*SzerStary);

    }

    tImage2 = newImage->copy(0,0,newImage->width(),newImage->height());

    delete newImage;

    for(int y=0;y<image->height();y++)
    {
        p = (int*) image->scanLine(y);


        for(int x=0;x<image->width();x++)
        {
            for(int i=0;i<ui->spinBox_wartMaski->value();i++)
                for(int j=0;j<ui->spinBox_wartMaski->value();j++)
                    color[i][j].setRgb(tImage2.pixel(x+i,y+j));
            p[x] = wstawKolor(ui->spinBox_wartMaski->value(),color,tablica,wagaMaski).rgb();
        }
    }

    emit sigUpdateImage();

}

//ustala rozmiar maski
void Filtry_Liniowe::jakaMaska(int rozmiar)
{
    {
        for(int i = 0; i < ui->spinBox_wartMaski->value(); i++)
            for(int j = 0; j < ui->spinBox_wartMaski->value(); j++)
                ui->maska->setItem(i,j,new QTableWidgetItem(""));
    }
    ui->maska->setColumnCount(rozmiar);
    ui->maska->setRowCount(rozmiar);
    for (int i = 0; i < rozmiar ; i++)
    {
        ui->maska->setColumnWidth(i,35);
        ui->maska->setRowHeight(i,25);
    }
}

void Filtry_Liniowe::czysc(){
    for(int i = 0; i < ui->spinBox_wartMaski->value(); i++)
        for(int j = 0; j < ui->spinBox_wartMaski->value(); j++)
            ui->maska->setItem(i,j,new QTableWidgetItem(""));
}



void Filtry_Liniowe::jakiFiltr()
{
    if(ui->radio_zeruj->isChecked())
    {
    for(int i = 0; i < (ui->spinBox_wartMaski->value()); i++)
        for(int j = 0; j < (ui->spinBox_wartMaski->value()); j++)
            ui->maska->setItem(i,j,new QTableWidgetItem("0"));
    }

    if(ui->radio_rozmyw->isChecked())
    {
        for(int i = 0; i < (ui->spinBox_wartMaski->value()); i++)
            for(int j = 0; j < (ui->spinBox_wartMaski->value()); j++)
            ui->maska->setItem(i,j,new QTableWidgetItem("1"));
    }

    if(ui->radio_dolno->isChecked())
    {
        for(int i = 0; i < (ui->spinBox_wartMaski->value()); i++)
            for(int j = 0; j < (ui->spinBox_wartMaski->value()); j++)
            ui->maska->setItem(i,j,new QTableWidgetItem("1"));
    if(ui->spinBox_wartMaski->value()==3){
            ui->maska->setItem(1,1,new QTableWidgetItem("4"));
    }
    if(ui->spinBox_wartMaski->value()==5){
            ui->maska->setItem(2,2,new QTableWidgetItem("4"));
    }
    if(ui->spinBox_wartMaski->value()==7){
            ui->maska->setItem(3,3,new QTableWidgetItem("4"));
    }
    if(ui->spinBox_wartMaski->value()==9){
            ui->maska->setItem(4,4,new QTableWidgetItem("4"));
    }
    }

    if(ui->radio_gauss->isChecked())
    {
            ui->maska->setItem(0,0,new QTableWidgetItem("1"));
            ui->maska->setItem(0,2,new QTableWidgetItem("1"));
            ui->maska->setItem(2,0,new QTableWidgetItem("1"));
            ui->maska->setItem(2,2,new QTableWidgetItem("1"));
            ui->maska->setItem(0,1,new QTableWidgetItem("2"));
            ui->maska->setItem(1,0,new QTableWidgetItem("2"));
            ui->maska->setItem(1,2,new QTableWidgetItem("2"));
            ui->maska->setItem(2,1,new QTableWidgetItem("2"));
            ui->maska->setItem(1,1,new QTableWidgetItem("4"));
    }

    if(ui->radio_gorno->isChecked())
    {
        if(ui->spinBox_wartMaski->value()==3){
        for(int i = 0; i < (ui->spinBox_wartMaski->value()); i++)
            for(int j = 0; j < (ui->spinBox_wartMaski->value()); j++)
            ui->maska->setItem(i,j,new QTableWidgetItem("-1"));
            ui->maska->setItem(1,1,new QTableWidgetItem("9"));
        }
    }

    if(ui->radio_piw0st->isChecked())
    {
        if(ui->spinBox_wartMaski->value()==3){
            ui->maska->setItem(0,0,new QTableWidgetItem("-1"));
            ui->maska->setItem(0,1,new QTableWidgetItem("-1"));
            ui->maska->setItem(0,2,new QTableWidgetItem("-1"));
            ui->maska->setItem(1,0,new QTableWidgetItem("0"));
            ui->maska->setItem(1,1,new QTableWidgetItem("0"));
            ui->maska->setItem(1,2,new QTableWidgetItem("0"));
            ui->maska->setItem(2,0,new QTableWidgetItem("1"));
            ui->maska->setItem(2,1,new QTableWidgetItem("1"));
            ui->maska->setItem(2,2,new QTableWidgetItem("1"));
        }

    }

    if(ui->radio_piw90st->isChecked())
    {
            ui->maska->setItem(0,0,new QTableWidgetItem("-1"));
            ui->maska->setItem(0,1,new QTableWidgetItem("0"));
            ui->maska->setItem(0,2,new QTableWidgetItem("1"));
            ui->maska->setItem(1,0,new QTableWidgetItem("-1"));
            ui->maska->setItem(1,1,new QTableWidgetItem("0"));
            ui->maska->setItem(1,2,new QTableWidgetItem("1"));
            ui->maska->setItem(2,0,new QTableWidgetItem("-1"));
            ui->maska->setItem(2,1,new QTableWidgetItem("0"));
            ui->maska->setItem(2,2,new QTableWidgetItem("1"));

    }

    if(ui->radio_sob0st->isChecked())
    {
            ui->maska->setItem(0,0,new QTableWidgetItem("-1"));
            ui->maska->setItem(0,1,new QTableWidgetItem("-2"));
            ui->maska->setItem(0,2,new QTableWidgetItem("-1"));
            ui->maska->setItem(1,0,new QTableWidgetItem("0"));
            ui->maska->setItem(1,1,new QTableWidgetItem("0"));
            ui->maska->setItem(1,2,new QTableWidgetItem("0"));
            ui->maska->setItem(2,0,new QTableWidgetItem("1"));
            ui->maska->setItem(2,1,new QTableWidgetItem("2"));
            ui->maska->setItem(2,2,new QTableWidgetItem("1"));

    }

    if(ui->radio_sob90st->isChecked())
    {
            ui->maska->setItem(0,0,new QTableWidgetItem("-1"));
            ui->maska->setItem(0,1,new QTableWidgetItem("0"));
            ui->maska->setItem(0,2,new QTableWidgetItem("1"));
            ui->maska->setItem(1,0,new QTableWidgetItem("-2"));
            ui->maska->setItem(1,1,new QTableWidgetItem("0"));
            ui->maska->setItem(1,2,new QTableWidgetItem("2"));
            ui->maska->setItem(2,0,new QTableWidgetItem("-1"));
            ui->maska->setItem(2,1,new QTableWidgetItem("0"));
            ui->maska->setItem(2,2,new QTableWidgetItem("1"));

    }

    if(ui->radio_plasko->isChecked())
    {
        if(ui->spinBox_wartMaski->value()==3){
            ui->maska->setItem(0,0,new QTableWidgetItem("-1"));
            ui->maska->setItem(0,1,new QTableWidgetItem("0"));
            ui->maska->setItem(0,2,new QTableWidgetItem("1"));
            ui->maska->setItem(1,0,new QTableWidgetItem("-1"));
            ui->maska->setItem(1,1,new QTableWidgetItem("1"));
            ui->maska->setItem(1,2,new QTableWidgetItem("1"));
            ui->maska->setItem(2,0,new QTableWidgetItem("-1"));
            ui->maska->setItem(2,1,new QTableWidgetItem("0"));
            ui->maska->setItem(2,2,new QTableWidgetItem("1"));
        }
        if(ui->spinBox_wartMaski->value()==5){
            ui->maska->setItem(0,0,new QTableWidgetItem("-1"));
            ui->maska->setItem(0,1,new QTableWidgetItem("-1"));
            ui->maska->setItem(0,2,new QTableWidgetItem("-1"));
            ui->maska->setItem(0,3,new QTableWidgetItem("-1"));
            ui->maska->setItem(0,4,new QTableWidgetItem("-1"));
            ui->maska->setItem(1,0,new QTableWidgetItem("-1"));
            ui->maska->setItem(1,1,new QTableWidgetItem("-1"));
            ui->maska->setItem(1,2,new QTableWidgetItem("-1"));
            ui->maska->setItem(1,3,new QTableWidgetItem("-1"));
            ui->maska->setItem(1,4,new QTableWidgetItem("-1"));
            ui->maska->setItem(2,0,new QTableWidgetItem("0"));
            ui->maska->setItem(2,1,new QTableWidgetItem("0"));
            ui->maska->setItem(2,2,new QTableWidgetItem("1"));
            ui->maska->setItem(2,3,new QTableWidgetItem("0"));
            ui->maska->setItem(2,4,new QTableWidgetItem("0"));
            ui->maska->setItem(3,0,new QTableWidgetItem("1"));
            ui->maska->setItem(3,1,new QTableWidgetItem("1"));
            ui->maska->setItem(3,2,new QTableWidgetItem("1"));
            ui->maska->setItem(3,3,new QTableWidgetItem("1"));
            ui->maska->setItem(3,4,new QTableWidgetItem("1"));
            ui->maska->setItem(4,0,new QTableWidgetItem("1"));
            ui->maska->setItem(4,1,new QTableWidgetItem("1"));
            ui->maska->setItem(4,2,new QTableWidgetItem("1"));
            ui->maska->setItem(4,3,new QTableWidgetItem("1"));
            ui->maska->setItem(4,4,new QTableWidgetItem("1"));
        }

    }
}
