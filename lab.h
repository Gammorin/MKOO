#ifndef LAB_H
#define LAB_H

#include <QWidget>

namespace Ui {
    class Lab;
}

class Lab : public QWidget
{
    Q_OBJECT

public:
    explicit Lab(QWidget *parent = 0);
    ~Lab();
    void setImage(QImage*);
    float zakres(float,float,float);
    float *multiply(float,float,float,float*);
    float *tSqr,*tSqrt,*tL;


private:
    Ui::Lab *ui;
    QImage *Obraz, tObraz;

protected:
    void changeEvent(QEvent *e);

public slots:
    void zresetuj();
    double funkX(double);
    double funkY(double);
    double funkZ(double);
    float funkX2(float, float, float);
    float funkY2(float, float);
    float funkZ2(float, float, float);
    void glowna_funkcja();



signals:
    void sigUpdateImage();
};

#endif // LAB_H
