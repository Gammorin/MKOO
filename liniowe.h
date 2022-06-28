#ifndef FILTRY_LINIOWE_H
#define FILTRY_LINIOWE_H

#include <QtGui/QWidget>
#include <QSpinBox>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <iostream>

#include <QRadioButton>
#include<iostream>
using namespace std;

namespace Ui {
    class Filtry_Liniowe;
}

class Filtry_Liniowe : public QWidget
{
    Q_OBJECT

public:
    explicit Filtry_Liniowe(QWidget *parent = 0);
    ~Filtry_Liniowe();
    QColor wstawKolor(int, QColor**, int**, int);
    void setImage(QImage*);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::Filtry_Liniowe *ui;
    QSpinBox *spinBox_wartMaski;  
    QImage *image,tImage,tImage2;
    QTableWidget *maska;

public slots:
    void jakaMaska(int);
    void jakiFiltr();
    void mask();
    void cancel();
    void czysc();

signals:
    void sigUpdateImage();
};

#endif // FILTRY_LINIOWE_H
