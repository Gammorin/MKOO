#ifndef RGB_NA_CMYK_H
#define RGB_NA_CMYK_H

#include <QWidget>


namespace Ui {
    class rgb_na_cmyk;
}

class rgb_na_cmyk : public QWidget
{
    Q_OBJECT


public:
    explicit rgb_na_cmyk(QWidget *parent = 0);
    ~rgb_na_cmyk();

    void setImage(QImage*);


private:
    Ui::rgb_na_cmyk *ui;
    QImage *obraz;
    QImage tObraz;
protected:
    void changeEvent(QEvent *e);

public slots:
    void cmyk();
    void zresetuj();
    double min(double, double);


signals:
    void sigUpdateImage();

};

#endif // RGB_NA_CMYK_H
