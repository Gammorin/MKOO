#ifndef BCDKOREKCJA_H
#define BCDKOREKCJA_H

#include <QWidget>
#include <QLabel>
#include <QSlider>
#include <QPushButton>
#include <QImage>

namespace Ui {
    class bcdkorekcja;
}

class bcdkorekcja : public QWidget
{
    Q_OBJECT

public:
    explicit bcdkorekcja(QWidget *parent = 0);
    ~bcdkorekcja();
    void setImage(QImage*);

private:
    Ui::bcdkorekcja *ui;
    QImage *obraz, tObraz;
    QSlider *vslider1, *vslider2, *vslider3;
    QLabel *w1, *w2, *w3;

    double** tab;
    int zakres(int,int,int);

public slots:
    void wartGamma(int);
    void stworztablice();
    void wykonaj();
    void zresetuj();


signals:
    void sigUpdateImage();
};

#endif // BCDKOREKCJA_H
