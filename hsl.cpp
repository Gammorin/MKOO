#include "hsl.h"
#include "ui_hsl.h"

rgb_na_hsl::rgb_na_hsl(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::rgb_na_hsl)
{
    ui->setupUi(this);

        setWindowTitle("Hue Saturation Lightness");

        connect(ui->ok, SIGNAL(clicked()), this, SLOT(close()));
        connect(ui->anuluj, SIGNAL(clicked()), this, SLOT(cancel()));

        ui->horizontalSlider->setRange(0,360);
        ui->horizontalSlider->setValue(0);
        ui->label_4->setText("0");
        connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(HSL()) );
        connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), this->ui->label_4, SLOT(setNum(int)));

        ui->horizontalSlider_2->setRange(-100,100);
        ui->horizontalSlider_2->setValue(0);
        ui->label_5->setText("0");
        connect(ui->horizontalSlider_2, SIGNAL(valueChanged(int)), this, SLOT(HSL()) );
        connect(ui->horizontalSlider_2, SIGNAL(valueChanged(int)), this->ui->label_5, SLOT(setNum(int)));

        ui->horizontalSlider_3->setRange(-100,100);
        ui->horizontalSlider_3->setValue(0);
        ui->label_6->setText("0");
        connect(ui->horizontalSlider_3, SIGNAL(valueChanged(int)), this, SLOT(HSL()) );
        connect(ui->horizontalSlider_3, SIGNAL(valueChanged(int)), this->ui->label_6, SLOT(setNum(int)));

    }

    rgb_na_hsl::~rgb_na_hsl()
    {
        delete ui;
    }

    void rgb_na_hsl::changeEvent(QEvent *e)
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

    //----------------------------------------------------------------------------

    void rgb_na_hsl::setImage(QImage* im)
    {
        obrazek = im;
        tmpObrazek = *obrazek;
    }

    void rgb_na_hsl::cancel()
    {

        ui->horizontalSlider->setValue(0);
        ui->horizontalSlider_2->setValue(0);
        ui->horizontalSlider_3->setValue(0);
        *obrazek = tmpObrazek;

        emit sigUpdateImage();
    }


    double rgb_na_hsl::min(double a,double b)
    {
        if (a < b)
        {
            return a;
        }
        else
        {
            return b;
        }
    }



    double rgb_na_hsl::max(double a,double b)
    {
        if (a > b)
        {
            return a;
        }
        else
        {
            return b;
        }
    }

    double rgb_na_hsl::zakres1(double wartosc,double min,double max)
    {
        if(wartosc>max)
            return max;
        if(wartosc<min)
            return min;
        return wartosc;
    }

    double rgb_na_hsl::zakres2(double wartosc)
    {
        if(wartosc>1.0)
            return wartosc-1.0;
        if(wartosc<0.0)
            return wartosc+1.0;
        return wartosc;
    }

    double wartosc(double v,double a,double b)
    {
        if (v<(1.0/6.0))
           return a + (((b-a)*6.0) * v);
        if ((1.0/6.0) <= v and v < 0.5)
            return b;
        if (0.5 <= v and v <(2.0/3.0) )
            return a + (((b-a)*6.0) * ((2.0/3.0)-v));
        return a;
    }
    void rgb_na_hsl::HSL()
    {
        QColor pix;
        int hI;
        double r, g, b, MAX,MIN,dM;
        double h,s,l,p,q,rT,gT,bT;

        for(int x=0;x<obrazek->width();x++)
        {
            for(int y=0;y<obrazek->height();y++)
            {
                pix = tmpObrazek.pixel(x,y);
                r = pix.redF();
                g = pix.greenF();
                b = pix.blueF();
                MIN = min(r,min(g,b));
                MAX = max(r,max(g,b));
                dM = MAX - MIN;

                l = (MAX+MIN)/2.0;

                if(l==0 or MAX==MIN)
                    s = 0.0;
                else
                    {
                        if (0.0 < l and l <= 0.5)
                            s = dM/(2*l);
                        else
                            s = dM/(2-(2*l));
                     }

                 if(MAX==MIN)
                        hI = 0;
                 else
                   {
                        if(MAX==r)
                        {
                            if(g>=b)
                                hI = 60*((g-b)/dM);
                             else
                                hI = 60*((g-b)/dM)+360;
                        }
                        else
                        {
                            if(MAX==g)
                                hI = 60*((b-r)/dM)+120;
                            else
                                hI = 60*((r-g)/dM)+240;
                        }
                    }

                    hI = zakres1((int)(hI + ui->horizontalSlider->value())%360,0,360);
                    s = zakres1(s * (ui->horizontalSlider_2->value()/100.0 +1),0.0,1.0);
                    l = zakres1(l * (ui->horizontalSlider_3->value()/100.0 +1),0.0,1.0);

                    if (s==0)
                        r=g=b=l;
                     else
                     {
                        if(l<0.5)
                            q = l*(1.0+s);
                        else
                            q = l+s-(l*s);

                        h = hI /360.0;
                        p = 2.0*l-q;
                        rT = zakres2(h + 0.33334);
                        bT = zakres2(h - 0.33334);
                        gT = zakres2(h);

                        b = wartosc(bT,p,q);
                        r = wartosc(rT,p,q);
                        g = wartosc(gT,p,q);
                      }

                      pix.setRgbF(r,g,b);
                      obrazek->setPixel(x,y,pix.rgb());
                }
            }
            emit sigUpdateImage();
    }
