#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include <QWidget>
#include <QLabel>
#include <QSlider>
#include <QImage>
#include <QPainter>
#include <QPushButton>


namespace Ui {
    class histogram;
}

class histogram : public QWidget
{
    Q_OBJECT

public:
    explicit histogram(QWidget *parent = 0);
    ~histogram();

    void setImage(QImage*);
    void paintEvent(QPaintEvent *);
     double max;

private:
    Ui::histogram *ui;

    int *tab_v, *tab_red, *tab_green, *tab_blue;


    QImage *obraz, tObraz, *image;

public slots:
    void zczytaj(QImage *image);


signals:
    void sigUpdateImage();
};

#endif // HISTOGRAM_H
