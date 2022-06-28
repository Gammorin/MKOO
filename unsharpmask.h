#ifndef UNSHARPMASK_H
#define UNSHARPMASK_H

#include <QtGui/QWidget>
#include <QLabel>
#include <QSlider>
#include <QSpinBox>

namespace Ui {
class UnsharpMask;
}

class UnsharpMask : public QWidget
{
    Q_OBJECT
    
public:
    explicit UnsharpMask(QWidget *parent = 0);
    ~UnsharpMask();

    void setImage(QImage*);
    QImage *image,tmpImage,tmpImage2;
    double **tablica;
    
private:
    Ui::UnsharpMask *ui;
    QSlider *sigmaSlider, *alfaSlider;
    QLabel *sigmaLabel, *alfaLabel;
    QSpinBox *spinBox;

public slots:
    void cancel();
    void label1(int);
    void label2(int);
    void oblicz();

signals:
    void sigUpdateImage();
};

#endif // UNSHARPMASK_H
