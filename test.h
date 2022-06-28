#ifndef TEST_H
#define TEST_H

#include <QWidget>
#include <QColor>
#include <QImage>
#include <QRgb>
#include <QImage>
#include <QRgb>
#include <QColor>


namespace Ui {
    class Test;
}

class Test : public QWidget
{
    Q_OBJECT

public:
    explicit Test(QWidget *parent = 0);
    ~Test();

    QImage *Obraz;
    QImage tObraz;

    QImage Obraz2;
    QImage *wObraz2;
    int zmienna;


    void setImage(QImage*);



private:
    Ui::Test *ui;

public slots:
    void k_czerwony();
    void k_niebieski();
    void k_zielony();


signals:
    void sigUpdateImage();
};

#endif // TEST_H
