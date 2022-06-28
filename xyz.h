#ifndef CIE_H
#define CIE_H

#include <QWidget>
#include <cmath>

namespace Ui {
    class CIE;
}

class CIE : public QWidget
{
    Q_OBJECT

public:
    explicit CIE(QWidget *parent = 0);
    ~CIE();

    void setImage(QImage*);
    float *tabSqr, *tabSqrt;

private:
    Ui::CIE *ui;
    QImage *Obraz, tObraz;


public slots:    
    void konwersja_sRGB();
    void konwersja_aRGB();
    void ustawX(int);
    void ustawY(int);
    void ustawZ(int);
    float od_do(float, float, float);
    void zresetuj();


signals:
    void sigUpdateImage();
};

#endif // CIE_H
